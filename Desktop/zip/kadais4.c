//0~MAX_CLIENTの数値、あるいはユーザ名(または e) "message"と入力されればその相手にメッセージを送る
//ユーザ名を最初に入力させ、それをそのユーザの名前として他のユーザに出す。
//とりあえず、空白と改行は\0に置換される
//あとは、送信先にユーザ名まで指定できればok

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT        8889  //ポート番号
#define MAX_CLIENT  5
#define FREE        100
#define NAMELEN     20    //ユーザ名の長さ

//読み込んだ1文字が数字かどうか判定する関数(真：１ 偽：０)
int isdigit(char c){
    int digit;

    digit = c - '0';
    return ((0 <= digit) && (digit <= 9));
}

//二つの文字列が同じかどうか判定する関数(真：１ 偽：０)
//こいつを見直す必要がある
int issame(char a[], char b[]){
  int x;
  for(x=0; x < NAMELEN && a[x] != '\0' && b[x] != '\0'; x++){
    if(a[x] != b[x])
      return 0;
  }
  if(((a[x] == '\0') && (b[x] != '\0')) || ((a[x] != '\0') && (b[x] == '\0')))
    return 0;
  else
    return 1;
}

main()
{
  int i, j,n, *server, *clients, sockets[MAX_CLIENT+2], len, z;
  fd_set fds;
  int cli=-1,x=0;        //送信先クライアント番号,何文字目まで数字を読んだか

  int k;
  int nameflag[MAX_CLIENT];   //名前が入力されたかどうかのフラグ
  char name[MAX_CLIENT * NAMELEN];  //クライアントの名前管理
  char message[100];
  int status;
  struct sockaddr_in saddr;
  struct sockaddr_in caddr;
  static char   buf[100];
  static char   buf2[100];
  static char   temp[NAMELEN];      //ユーザ名を一時的に保存しておく配列

  /* Intalize a socket ------------------------------------------ */
  server  = sockets;
  clients = sockets+1;
  if ((*server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    exit(1);
  }
  /* Bind the socket -------------------------------------------- */
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = INADDR_ANY;
  saddr.sin_port = htons(PORT);
  if (bind(*server,(struct sockaddr *)&saddr,sizeof(struct sockaddr_in))<0) {
    perror("bind");  exit(1);
  }
  /* Wait to someone connect to this server --------------------- */
  if (listen(*server, MAX_CLIENT) < 0) {
    perror("listen"); exit(2);
  }
  /* Clear all clients ------------------------------------------ */
  for (i=0; i <= MAX_CLIENT; i++){ 
    clients[i]=FREE;
    nameflag[i]=0;  //名前が入力されたフラグを初期化
  }
  /* Main loop -------------------------------------------------- */
  for (;;) {
    /* Initalize fd_set ----------------------------------------- */
    FD_ZERO(&fds);
    for (i=0; i < MAX_CLIENT+1; i++) {
      if (sockets[i] != FREE) FD_SET(sockets[i], &fds);
      printf("sokects[%d]=%d\n", i, sockets[i]);
    }
    /* Check message arrivals ----------------------------------- */
    if ((n = select(FD_SETSIZE, &fds, NULL, NULL, NULL)) == -1) { //これ(select)によってどのソケットから通信きたか判別してるらしい
       perror("select"); exit(3);
    } 
    /* Processing Loop ------------------------------------------ */
    for (i=0; i < MAX_CLIENT; i++) {
      if (clients[i] != FREE) {
	    if (FD_ISSET(clients[i], &fds)) { /* A Message is exist */
	     if ((len = read(clients[i], buf, 100)) == -1) {
	         perror("read"); exit(4);
	     } 
       else if (len != 0) {
	      if (strncmp(buf, "quit", 4) != 0) {
            if(!nameflag[i]){
                /*  同じユーザ名が入力されないように、一度入力されたユーザ名がすでに使われているかを判定する必要がある */
                /* 新しく入力された文字列と、nameflag[i]が立っている所全ての文字列をstrncmpで比較すれば良い  */
                for(j=0; j< NAMELEN && buf[j] != '\0'; j++){
                      if(buf[j] == '\n'){              //入力+?+改行となってる->buf[j-1]に\0を入れるべきか
                        buf[j-1] = '\0'; 
                        break;
                      }
                      if(buf[j] == ' '){                     //入力+空白
                        buf[j] = '\0';
                        break;
                      }
                }
                for(z=0; z < MAX_CLIENT; z++){
                  if(nameflag[z]){
                    for(j=0; j < NAMELEN; j++){
                      buf2[j] = name[(z*NAMELEN) + j];
                      if(buf2[j] == '\0'){    //nameには\0が入っている
                        break;                //この処理をしないとbufには\0が入っているのにbuf2に\0が入っていないのでissameの判定がおかしくなる
                      }
                    }
                    if(issame(buf,buf2)){
                      sprintf(buf2,"The name is already used.\n");    //すでに名前が使われていた場合
                      write(clients[i],buf2,100);
                      bzero(buf2,100);
                      bzero(buf,100);
                      break;
                    }
                    bzero(buf2,100);
                  }
                } 
                if(strncmp(buf,"everyone",8) == 0){
                  sprintf(buf2,"other name please.\n");
                  write(clients[i],buf2,100);
                  bzero(buf2,100);
                  bzero(buf,100);
                }
                else if(z == MAX_CLIENT){    //名前が使われていなかったらzはMAX_CLIENTと同じ数になるはず
                nameflag[i] = 1;  //nameflagを立てる
                //もし、ユーザ側が長い文字列を入力したら強制終了してしまう
                //改行もユーザ名として認識されてしまう、しかし、for文で条件を除こうとすると出力がおかしくなる
                for(j=0; j < NAMELEN; j++){
                  message[j] = buf[j];             //クライアント側や、ユーザ側へユーザ名を出力しやすくするため一時的に保存
                  name[(i*NAMELEN)+j] = buf[j];    //ユーザ名を登録
                  if(buf[j] == '\0'){
                    break;
                  }
                }
                bzero(buf,100);
                printf("client(%d) name is %s\n",i,message);
                sprintf(buf2,"Your number is (%d) Your name is %s\n",i,message); //この出力だと、ユーザ名がきっちり管理されているという証拠にはなり得ない。
                write(clients[i],buf2,100);
                bzero(buf2,100);
                }
            }
            else{
              sscanf(buf,"%s",message);
              if(!isdigit(message[0])) cli = -1;
              else{
                  cli = 0;
                  for(x=0; isdigit(message[x]) && message[x] != '\0'; x++)
                    cli = cli * 10 + (message[x] - '0');
              }
              
            /* ここで,配列の先頭から文字を読んでいき数字以外がでるまで読み続ける
              数字を読んだ場合 cli = cli*10 + 読んだ数字 で計算する  */

              if(strncmp(buf,"everyone",8) == 0){      //eが入力されたら自分以外のみんなに送る
                printf("From %d to every one\n",i);
                for(j=0; j < NAMELEN && name[(i*NAMELEN)+j] != '\0'; j++)
                  temp[j] = name[(i*NAMELEN)+j];
                sprintf(buf2," (%d) (e) > ",i);
                for(z=0; z<MAX_CLIENT; z++){
                    if(z != i){
                        write(clients[z],temp,NAMELEN);
                        write(clients[z],buf2,100);
                        write(clients[z],buf+(x+8),100);    //messageの部分だけを送信する
                        sprintf(buf2,"\n");
                        write(clients[z],buf2,1);
                    }
                }
              }
              else if(cli == -1 || (MAX_CLIENT <= cli)){      //最初の文字が数字以外、または送信先番号がクライアントの上限を超えている場合
                  sprintf(buf2,"\nformat: ClientNumber(0~%d) Message\n",MAX_CLIENT-1);
                  write(clients[i],buf2,100);
              }
              else if((cli < MAX_CLIENT)){ //送信先番号がクライアントの上限数を超えてない
                  printf("From %d to %d\n",i,cli);
                  for(j=0; j < NAMELEN && name[(i*NAMELEN)+j] != '\0'; j++)
                    temp[j] = name[(i*NAMELEN)+j];           
                  sprintf(buf2," (%d) > ",i);
                  write(clients[cli],temp,NAMELEN);
                  write(clients[cli],buf2,100);
                  write(clients[cli],buf+(x+1),100);    //messageの部分だけ送信する
                  sprintf(buf2,"\n");
                  write(clients[cli],buf2,1);
              }
              write(clients[i],buf2,1);
              bzero(buf,100);
              bzero(buf2,100);
              bzero(temp,NAMELEN);
            }//(else):nameglag[i]==1
          }//if (strncmp(buf, "quit", 4) != 0)
          else{
	          printf("A client (%d) leaved.\n", i);
	          close(clients[i]); clients[i] = FREE;
            nameflag[i] = 0;
            for(j=0; (j<NAMELEN) && (name[(i*NAMELEN)+j] != '\0'); j++) 
              name[(i*NAMELEN)+j] = '\0'; //名前を初期化
          }
	     }//else if (len != 0)
         else {
	        close(clients[i]); clients[i] = FREE;
	        printf("A client (%d) leaved.\n", i);
          nameflag[i] = 0;
          for(j=0; (j<NAMELEN) && (name[(i*NAMELEN)+j] != '\0'); j++) 
            name[(i*NAMELEN)+j] = '\0'; //名前を初期化
	     }
	    }//if (FD_ISSET(clients[i], &fds))
      }
    }
    /* New connection -------------------------------------------*/
    if (FD_ISSET(*server, &fds) != 0) {
      len = sizeof(caddr);
      for (i=0; i < MAX_CLIENT; i++) {
	    if (clients[i] == FREE) break;
      }
      clients[i] = accept(*server, (struct sockaddr*)&caddr, &len);
      if (clients[i] == -1) {
	      perror("accept"); exit(5);
      }
      if (i < MAX_CLIENT) {
	      printf("A new client (%d) is accepted.\n", i);
        sprintf(buf2,"What your name?\n");
        write(clients[i],buf2,100);
        bzero(buf2,100);
      } 
      else {
	      printf("A client is refused.\n");
	      write(clients[i], "Server is too busy.\n", 20);
	      close(clients[i]);
	      clients[i]=FREE;
      }
    }
  }
}