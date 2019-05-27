#include <stdio.h> //scanf,printf
#include <stdlib.h> //exit
#include <unistd.h> //sleep,fork
int main(void) {
  pid_t pid[3]; /* fork()からの返り値 */
  int i=0;
  /* 子プロセスを作る. forkが呼ばれると,
     このプログラムの新しいプロセスがコピーされ作られる. */
  /* 返り値によって，自分が親か子かを判断する */
  for(i=0;i<3;i++){
      pid[i] = fork();
      if(pid[i] == -1)    /* forkに失敗 */
        fprintf(stderr, "fork has failed.\n");
      else if(pid[i] == 0){  /* 子プロセス */
        printf("I am a child process ID is:%d\n",getpid());
        printf("My parent process ID is:%d\n\n",getppid());
        sleep(5);
        exit(1);
      }
    else{
      /* 親プロセス */
      printf("My child process ID is:%d\n",pid[i]);
      printf("I am a parent process ID is%d\n\n",getpid());
      sleep(5);
    }
  }
  return 0;
}

/*  実行結果  */
/*
ps lf
0 30288  7015  6084  20   0   1868   396 -      S+   pts/0      0:00  \_ ./a.out
1 30288  7016  7015  20   0      0     0 ?      Z+   pts/0      0:00      \_ 
1 30288  7018  7015  20   0      0     0 ?      Z+   pts/0      0:00      \_ 
1 30288  7019  7015  20   0   1868   208 -      S+   pts/0      0:00      \_ ./a



 */
