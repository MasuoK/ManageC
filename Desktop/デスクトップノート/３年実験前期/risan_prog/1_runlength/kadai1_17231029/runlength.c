#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "func.h"


//*string: 入力される文字列へのポインタ
int runlength(unsigned char *string, int size) {
  
  //*ret:保存される文字列へのポインタ
  unsigned char *ret;
  //retのさす配列の領域の確保
  ret = (char *)malloc(sizeof(char) * MAXSTR);
  //文字数のカウント
  int count = 0;
  int stringcount = 0;
  int retcount = 0;
  if (definecheck(968890)) {
    return 1;
  }
  // input your code here...
  while(*string != '\0'){
    count++;
    if(*string != *(string+ 1)){
      *ret = *string;
      *(ret + 1) = (char)count;

      printf("ch=%c\n",*ret);
      printf("cou=%d\n",count);

      count = 0;
      ret = ret + 2;
      retcount = retcount+2;
    }
    string++;
    stringcount++;
  }
  *ret = '\0';
  string = string-stringcount;
  ret = ret - retcount;
  strcpy(string,ret);

  return 0;
}

