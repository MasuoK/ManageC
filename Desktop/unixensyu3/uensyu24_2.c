/*
* redsmpl1.c - 標準出力のリダイレクトのあるシェルプログラム(引数なし) */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#define COMBUFSIZ 128 /* コマンド名のバッファのサイズ */
#define FNBUFSIZ 128 /* ファイル名のバッファのサイズ */
int main(void) {
  char combuf[COMBUFSIZ];  /* コマンド名のバッファ */
  char infnbuf[FNBUFSIZ];  /* 入力ファイル名のバッファ  */
  char outfnbuf[FNBUFSIZ]; /* 出力ファイル名のバッファ */
  int infd;                /* 入力ファイル記述子 */
  int outfd;               /* 出力ファイル記述子 */
  int status;              /* 子プロセスの終了状態: 使用しない */


  while(1) {
    /* コマンド名とファイル名の入力 */ 
    /* コマンド名の入力と exit の処理 */ 
    printf("command: ");
    fgets(combuf, COMBUFSIZ, stdin); 
    combuf[strlen(combuf) - 1] = '\0'; 
    if(!strcmp(combuf, "exit"))
        exit(0);
    /* 入力ファイル名の入力  */
    printf("redirect from: ");
    fgets(infnbuf, FNBUFSIZ, stdin);
    infnbuf[strlen(infnbuf) - 1] = '\0';
    if(fork() == 0){
    /* 子プロセス側  */
    /* 入力リダイレクト  */
        if((infd = open(infnbuf,0644)) < 0){
            fprintf(stderr, "cannot open %s\n",infnbuf);
            exit(1);
        }
        close(0);
        dup(infd);
        /* コマンドの実行  */
        execlp(combuf,combuf,NULL);
        /* 以下はexec()失敗時  */
        fprintf(stderr,"cannot execute command\n");
        /* exec() 失敗時はすぐに終了  */
        exit(1);
    }
    /* 出力ファイル名の入力 */ 
    printf("redirect to: "); 
    fgets(outfnbuf, FNBUFSIZ, stdin);
    outfnbuf[strlen(outfnbuf) - 1] = '\0';
    if(fork() == 0) {
    /* 子プロセス側 */
    /* 出力リダイレクト */
        if((outfd = creat(outfnbuf, 0644)) < 0) {
            fprintf(stderr, "cannot open %s\n", outfnbuf);
            exit(1);
        }
        close(1);
        dup(outfd);
        /* コマンドの実行 */
        execlp(combuf, combuf, NULL);
        /* 以下は exec() 失敗時用 */
        fprintf(stderr, "cannot execute command\n"); 
        /* exec() 失敗時はすぐ終了する */
        exit(1);
    } 
    else {
        /* 親プロセス側 */ 
        wait(&status);
    }
  }
}