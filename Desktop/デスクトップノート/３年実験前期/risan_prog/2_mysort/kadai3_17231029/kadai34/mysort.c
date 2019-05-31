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


int mysort(char *string_array[], int size) {
  int ret;
  int i,j;
  //input your code here...
  //*tmp: 課題3 **temp: 課題4
  
  //char  *tmp = (char*)malloc(sizeof(char) * MAXLINE); // 大きいサイズの配列を確保
  char **temp = (char**)malloc(sizeof(char*)*MAXLINE); // 大きいサイズの配列を確保
  
  
  //バブルソート
  //strcpyよりも代入の方が早い（ポインタをつなぎ変えるだけだから）
  /*
  for(i=0;i<size-1;i++)
    for(j=size-1;j>i;j--){
      if(strcmp(string_array[j-1],string_array[j]) > 0){
	tmp = string_array[j-1];
	string_array[j-1] = string_array[j];
	string_array[j] = tmp;
      }
    }
  */

  //マージソート
  Msort(string_array,temp,0,size-1);
  
  //出力の確認
  /*
  for(i=0;i<size;i++)
    printf("moji=%s\n",string_array[i]);
  */
    

  ret = definecheck(567710);
  return ret;
}

