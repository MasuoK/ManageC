#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char *argv[])
{

  // 入力ファイルから順次文字列を読み込んでstring_arrayに格納していく
  char **string_array = (char**)malloc(sizeof(char*)*MAXLINE); // 大きいサイズの配列を確保
  char tmp_string[MAXLEN];
  int index=0; //配列の添え字
  int size;    //配列のサイズを保存
  clock_t start,end;
  char outname[100] = {};
  int i;

  
  FILE *file_in, *file_out;

  // 引数のチェックと入出力ファイルのオープン
  if (argc != 2){
    printf("different number of arguments\n");
    exit(1);
  }

  if ((file_in=fopen (argv[1],"r")) == NULL ){
    printf("input file not opened\n");
    exit(1);
  }
  i = 0;
  while((argv[1][i] != '.') && (argv[1][i] != '\0')){
    //printf("argv[1][%d] = %c\n", i, argv[1][i]);
    outname[i] = argv[1][i];
    i++;
  }
  outname[i] = '\0';
  strcat(outname, "_sorted.txt");

  if ((file_out=fopen (outname,"w")) == NULL){
    printf("output file not opened\n");
    exit(1);
  }

  if (definecheck(567710)) {
    printf("A copy of the file was detected\n");
    exit(1);
  }

  // fgetsで入力から一行ずつ文字列を読み込みながら配列のindex番目に格納
  while (fgets(tmp_string, MAXLEN, file_in)) {
    string_array[index] = strdup(tmp_string);
    string_array[index][strlen(string_array[index])] = '\0';     //各文字列の終わりを示す'\0'を詰める
    index++;
  }

  size = index; //文字列の総数をsizeで覚えてindexは以下で再利用
  
  start = clock();
  // 作成したソートの実行
  if(mysort(string_array, size)){
    printf("A copy of the file was detected\n");
    exit(1);
  }
  end = clock();
  //計算時間の表示
  printf("%.2f sec\n",(double)(end-start)/CLOCKS_PER_SEC);
  
  //fileに出力
  for (index = 0; index < size; index++) {
    fputs(string_array[index], file_out);
  }

  free(string_array);
  fclose(file_in);
  fclose(file_out);
  
  return 0;
}
