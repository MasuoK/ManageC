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


void bsort(char **string_array, int size) {
  char **temp = (char**)malloc(sizeof(char*) * size); // 大きいサイズの配列を確保
  printf("bsort started\n");
  Msort(string_array,temp,0,size-1);
  printf("bsort finished\n");
}


/*
void bsort(char *string_array, int size) {
	//input your code here...
  int *temp = (int*)malloc(sizeof(int) * size); // 大きいサイズの配列を確保
  //printf("step1\n");
  int i,k;
  //string_arrayを連結させた配列
  char  *w = (char*)malloc(sizeof(char)* size *2 );

  //配列の確保(整数)
  int *shift;
  shift = (int*)malloc(sizeof(int) * size);

  //ソートした配列の末尾を格納する配列
  char *bws = (char*)malloc(sizeof(char) * size);

  //printf("step2\n");
  
  //string_arrayをwにコピー
  strcpy(w,string_array);
  //string_arrayをwに連結(w=ss)
  strcat(w,string_array);
  
  //printf("step2.5\n");
  
  for(i=0;i<size;i++)
    shift[i] = i;

  //printf("step3\n");
  
  Msort(shift,temp,0,size-1,w,size);
  
  //printf("step4\n");
  
  //配列の末尾を取り出す
  for(i=0;i<size;i++)
    bws[i] = w[shift[i]+size];

  //printf("step5\n");

  //マージソートとは無関係にbwsが1025文字以降にも確保され、変な文字が入っている
  //そのため、1025文字目に\0を代入
  //bws[i] = '\0';

  strcpy(string_array,bws);

}
*/
