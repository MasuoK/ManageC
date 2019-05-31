#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "func.h"
	
	//マージソート
	//tempはDataと同じ型でなければならない
	
  /*
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
  */
	
	
	void Msort(int Data[ ], int temp[ ], int left, int right,char w[],int size) {
	
	  int mid, i, j, k,l;
	  if (left >= right)
	    return;
	  mid = (left + right) / 2;
	  Msort(Data, temp, left, mid,w,size);
	  Msort(Data, temp, mid + 1, right,w,size);
	  for (i = left; i <= mid; i++)
	    temp[i] = Data[i];
	  for (i = mid + 1, j = right; i <= right; i++, j--)
	    temp[i] = Data[j];
	  i = left;
	  j = right;
	
	  for (k = left; k <= right; k++){
	    //文字列の比較にはstrcmpを使う
	    if (strncmp(w+temp[i], w+temp[j],size) < 0){
	      Data[k] = temp[i];
	      i++;
	    }else{
	      Data[k] = temp[j];
	      j--;
	    }
	  }
	}

void bsort(char *string_array, int size) {
		//input your code here...
	  int *temp = (int*)malloc(sizeof(int) * size); // 大きいサイズの配列を確保
	  //printf("step1\n");
	  int i,k;
	  //string_arrayを連結させた配列
	  char  *w = (char*)malloc(sizeof(char)* (size *2) );
	
	  //ソートした配列の末尾を格納する配列
	  char *bws = (char*)malloc(sizeof(char) * (size+1));

    //配列の確保(整数)
	  int *shift;
	  shift = (int*)malloc(sizeof(int) * size);

	  for(i=0;i<size;i++)
	    shift[i] = i;
	
	  //string_arrayをwにコピー
	  strcpy(w,string_array);
	  //string_arrayをwに連結(w=ss)
	  strcat(w,string_array);	
	
	  Msort(shift,temp,0,size-1,w,size);
	
	  //配列の末尾を取り出す
	  for(i=0;i<size;i++)
	    bws[i] = w[shift[i]+size-1];
	
	  //マージソートとは無関係にbwsが末尾以降にも確保され、変な文字が入っている
	  //そのため、末尾の後ろに\0を代入
	  bws[size] = '\0';

	  strcpy(string_array,bws);
	  free(temp);
	}	
	