#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char *argv[]){

  char *string = (char*)malloc(sizeof(char)*MAXSTR);

  char *tmp_string = (char*)malloc(sizeof(char)*MAXLEN);

  char outname[100] = {};
  int index=0; //配列の添え字
  int size=0;    //配列のサイズ(文字の長さ)を保存
  int i, j;
  // 引数のチェックと入出力ファイルのオープン
  FILE *file_in, *file_out;
  clock_t start,end;

  if(definecheck(943620)){
    printf("Detect incorrect file change\n");
	  exit(1);
  }
 
  if (argc != 2){
    printf("different number of arguments\n");
    exit(1);
  }

  if ((file_in=fopen (argv[1],"r")) == NULL ){
    printf("input file not opened\n");
    exit(1);
  }
  
  j = 0;
  while((argv[1][j] != '.') && (argv[1][j] != '\0')){
    //printf("argv[1][%d] = %c\n", j, argv[1][j]);
    outname[j] = argv[1][j];
    j++;
  }
  outname[j] = '\0';
  strcat(outname, ".bwt");

  if ((file_out=fopen (outname,"w")) == NULL){
    printf("output file not opened\n");
    exit(1);
  }
  
 // input your code here...

  printf("main1\n");
  i=0;
  // fgetsで入力ファイルの文字列を一行ずつ読み込み配列stringに格納
  while (fgets(tmp_string, MAXLEN, file_in)) {  
    strcat(string,tmp_string);
  }
  size = i;

  printf("main1.75\n");

  //ポインタへのポインタを作成
  char **string_array = (char**)malloc(sizeof(char*) * size);

  //元の文字列stringを連結した文字列w
  char  *w = (char*)malloc(sizeof(char)* (size * 2));

  //stringをwにコピー
  strcpy(w,string);
  //stringをwに連結(w=ss)
  strcat(w,string);

  printf("main1.5\n");
  
  printf("main2\n");
  start = clock();

  for(i=0;i<size;i++){
    //printf("NO:%d\n",i);
    string_array[i] = (char*)malloc(sizeof(char*) * size);
    string_array[i] = &w[i];
  }

  printf("main3\n");
  

  bsort(string_array,size);

  // mysort()

  end = clock();
  
  //計算時間の表示
  printf("%fsec\n",(double)(end -start)/CLOCKS_PER_SEC);

  for(i=0;i<size;i++){
  //fileに出力(fputs:1行書き込む)
    fputs(string_array[i], file_out);
  }

  /*
  for(i=0;i<size;i++){
    free(string_array[i]);
  }

  free(w);
  free(string);
  */
  fclose(file_in);
  fclose(file_out);
  
  return 0;
}
