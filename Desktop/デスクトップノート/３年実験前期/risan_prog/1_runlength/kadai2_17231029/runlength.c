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
  //stringが最初の位置からどれだけ進んだかを数える
  int stringcount = 0;
  //retが最初の位置からどれだけ進んだかを数える
  int retcount = 0;
  if (definecheck(968890)) {
    return 1;
  }
  // input your code here...
  //文字列の終端にたどり着くまで繰り返す
  while(*string != '\0'){
    //文字数を数える
    count++;
    //現在の文字と、一つ先の文字が異なる場合、または同じ文字が255文字きた場合
    if((*string != *(string+ 1)) || count == 255){
      //現在読んでいる文字をretの配列に格納
      *ret = *string;
      //retの一つ先に文字数を記憶させる
      *(ret + 1) = (char)count;

      //printf("ch=%c\n",*ret);
      //printf("cou=%d\n",count);

      count = 0;
      //2つ先に次の文字の情報を格納する
      ret = ret + 2;
      retcount = retcount+2;
    }
    //元の配列を１つ進める
    string++;
    stringcount++;
  }
  //retの終端に終端記号を格納する
  *ret = '\0';
  //strcpyを行うために、stringとretを元のいちに戻す
  string = string-stringcount;
  ret = ret - retcount;
  //main関数のstringの配列を書き換えるためにretをstringにコピーする(ここのstringと元々あったstring(main関数のstring)は別物なので、stringの参照先を変えるだけでは不十分)

  strcpy(string,ret);

  return 0;
}

