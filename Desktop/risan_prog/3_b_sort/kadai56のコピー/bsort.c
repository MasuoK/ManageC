#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "func.h"

//マージソート
//tempはDataと同じ型でなければならない
void Msort(char *Data[], char *temp[] , int left, int right)
{
  int mid, i, j, k;
  if (left >= right)
    return;
  mid = (left + right) / 2;
  Msort(Data, temp, left, mid);
  Msort(Data, temp, mid + 1, right);
  for (i = left; i <= mid; i++)
    temp[i] = Data[i];
  for (i = mid + 1, j = right; i <= right; i++, j--)
    temp[i] = Data[j];
  i = left;
  j = right;
  for (k = left; k <= right; k++){
    //文字列の比較にはstrcmpを使う
    if (strcmp(temp[i], temp[j]) < 0){
      Data[k] = temp[i];
      i++;
    }else{
      Data[k] = temp[j];
      j--;
    }
  }
}



//string_arrayの入力の形式に注意
//今回は一次元で渡される（main側でそうなっている）
//mainで二次元にしてこっちにわたすか、1次元で受け取って2次元になおすか
//今回は後者
void bsort(char *string_array, int size) {
	//input your code here...
  char **temp = (char**)malloc(sizeof(char*) * size); // 大きいサイズの配列を確保
  //printf("step1\n");
  int i;
  //string_arrayを連結させた配列
  char  *w = (char*)malloc(sizeof(char)* size *2 );

  //printf("step2\n");
  
  //string_arrayをwにコピー
  strcpy(w,string_array);
  //string_arrayをwに連結(w=ss)
  strcat(w,string_array);
  
  // printf("step2.5\n");
  
  //2次元配列の確保
  char **shift;
  shift = (char**)malloc(sizeof(char*) * size);

  //printf("step3\n");

  //格納する文字列
  char *bws;
  bws = (char*)malloc(sizeof(char)   * size);

  //printf("step4\n");
  
  //2次配列の作成
  
  for(i=0;i<size;i++){
    //printf("NO:%d\n",i);
    //shift[i]の領域を確保
    shift[i] = (char*)malloc(sizeof(char) * size);
    strncpy(shift[i],(w+i),size);
  }
  
  //printf("step5\n");
  
  Msort(shift,temp,0,size-1);
  
  //printf("step6\n");
  
  //2次配列の末尾を取り出す
  for(i=0;i<size;i++){
    bws[i] = shift[i][size-1];
  }

  //printf("step7\n");
  
  /*
  for(i=0;i<size;i++){
    printf("bws=%c\n",bws[i]);
  }
  */
  
  strcpy(string_array,bws);
  
}
