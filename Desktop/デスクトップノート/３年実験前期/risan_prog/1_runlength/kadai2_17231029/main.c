#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

int main(int argc, char *argv[]) {

  unsigned char *string;
  unsigned char *tmp_string;
  int index;
  int size;    //配列のサイズを保存
  clock_t start, end;
  char outname[100] = {};
  int i;
  
  
  // 引数のチェックと入出力ファイルのオープン
  FILE *file_in, *file_out;

  if (argc != 2) {
    printf("different number of arguments\n");
    exit(1);
  }

  if ((file_in=fopen (argv[1],"r")) == NULL ) {
    printf("input file not opened\n");
    exit(1);
  }
  i = 0;
  while((argv[1][i] != '.') && (argv[1][i] != '\0')) {
    // printf("argv[1][%d] = %c\n", i, argv[1][i]);
    outname[i] = argv[1][i];
    i++;
  }
  outname[i] = '\0';
  strcat(outname, ".rle");

  if ((file_out=fopen (outname,"w")) == NULL) {
    printf("output file not opened\n");
    exit(1);
  }

  if (definecheck(968890)) {
    printf("A copy of the file was detected\n");
  }

  // 領域の確保
  string = (char *)malloc(sizeof(char) * MAXSTR);
  tmp_string = (char *)malloc(sizeof(char) * MAXLEN);
  
  // fgetsで入力ファイルの文字列を一行ずつ読み込み配列stringに格納
  while (fgets(tmp_string, MAXLEN, file_in)) {
    strcat(string, tmp_string);
  }
  
  // 文字数を取得
  size = strlen(string);
  printf("size = %d\n", size);
  start = clock();
  
  // runlength の実行
  if(runlength(string,size)) {
    printf("A copy of the file was detected\n");
    exit(1);
  }
  end = clock();

  // fileに出力
  size = strlen(string);
  for (index = 0; index < size; index++) {
    putc(string[index], file_out);
  }

  printf("time: %.2f\n", (double)(end-start) / CLOCKS_PER_SEC);

  //メモリ領域の解放
  free(string);
  free(tmp_string);
  fclose(file_in);
  fclose(file_out);
  
  return 0;

}
