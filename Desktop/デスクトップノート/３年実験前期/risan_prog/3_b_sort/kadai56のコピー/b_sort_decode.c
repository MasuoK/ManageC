#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
 
typedef unsigned char byte;
#define MAXSTR 100000000 // WBT変換する文字列の最大長さ
#define MAXL   1000000      //ファイルに書き込まれた1行の最大長


void bwt_decode(byte *buf_in, byte *buf_out, int size, int primary_index)
{
    byte F[size];
    int buckets[256];
    int i,j,k;
    int indices[size];
 
    for (i=0; i<256; ++i)
        buckets[i] = 0;
    for (i=0; i<size; ++i)
        buckets[buf_in[i]] ++;
    for (i=0,k=0; i<256; i++)
        for (j=0; j<buckets[i]; ++j)
            F[k++] = i;
    assert (k==size);
    for (i=0,j=0; i<256; ++i)
    {
        while (i>F[j] && j<size)
            ++j;
        buckets[i] = j; // it will get fake values if there is no i in F, but
                        // that won't bring us any problems
    }
    for(i=0; i<size; ++i)
        indices[buckets[buf_in[i]]++] = i;
    for(i=0,j=primary_index; i<size; ++i)
    {
        buf_out[i] = buf_in[j];
        j=indices[j];
    }
}
 
int main(int argc, char *argv[])
{
  byte *string;
  int size;
  byte *buf;
	byte *tmp_string;
  int primary_index;
	int i, j;
  char outname[100] = {};
	
	 // 引数のチェックと入出力ファイルのオープン
  FILE *file_in, *file_out;

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
  strcat(outname, ".dec");

  if ((file_out=fopen (outname,"w")) == NULL){
    printf("output file not opened\n");
    exit(1);
  }
	//領域の確保
  string = (byte *)malloc(sizeof(byte)*MAXSTR);
  tmp_string = (byte *)malloc(sizeof(byte)*MAXL);
  buf = (byte *)malloc(sizeof(byte)*MAXSTR);
  
  //Primary indexを取得(一行目版)
  /*fgets(tmp_string, MAXL, file_in);
  primary_index = atoi(tmp_string);
  printf("Primary index: %d\n", primary_index);
  */
  //BWTの文字列を取得
  while (fgets(tmp_string, MAXL, file_in)) {
    strcat(string,tmp_string);
    //printf("[check]\n");
  }
  size = strlen(string);
  //Primary indexを取得("$"版)
  for(i = 0; i < size; i++)
	if(string[i] == '$')
  primary_index = i;
	
  //printf("primary_index: %d\n", primary_index);
  //printf("string: %s\n", string);
  bwt_decode (string, buf, size, primary_index);
  //printf("   buf: %s\n", buf);
  
  //fileに出力
  fputs(buf, file_out);
  
  return 0;
}
