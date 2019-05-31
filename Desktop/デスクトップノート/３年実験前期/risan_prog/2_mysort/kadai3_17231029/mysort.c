#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "func.h"

int mysort(char *string_array[], int size) {
  int ret;
  int i,j;
  
  char  *tmp = (char*)malloc(sizeof(char) * MAXLINE); // 大きいサイズの配列を確保
  //input your code here...
  
  for(i=0;i<size-1;i++)
    for(j=size-1;j>i;j--){
      if(strcmp(string_array[j-1],string_array[j]) > 0){
	tmp = string_array[j-1];
	string_array[j-1] = string_array[j];
	string_array[j] = tmp;
      }
    }

  for(i=0;i<size;i++)
    printf("moji=%s\n",string_array[i]);

  ret = definecheck(567710);
  return ret;
}
