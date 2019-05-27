#include <stdio.h>  //scanf,printf
#include <unistd.h> //sleep,fork
int main(void) {
  pid_t pid; /* fork()からの返り値 */
  int i;
  /* 子プロセスを作る. forkが呼ばれると,
     このプログラムの新しいプロセスがコピーされ作られる. */
  pid = fork();
  /* 返り値によって，自分が親か子かを判断する */
  if(pid == -1)  /* forkに失敗 */
    fprintf(stderr, "fork has failed.\n");
  else if(pid == 0){  /* 子プロセス */
    printf("I am a child process ID is:%d\n",getpid());  //子自身のプロセスIDを取得
    printf("My parent process ID is:%d\n\n",getppid());  //親のプロセスIDを取得
    sleep(2);
  }
  else{
    /* 親プロセス */
    printf("My child process ID is:%d\n",pid);    //forkの返り値が子供の値
    printf("I am a parent process ID is%d\n\n",getpid());   //親自身のプロセスIDを取得
    sleep(3);
  }
  return 0;
}
