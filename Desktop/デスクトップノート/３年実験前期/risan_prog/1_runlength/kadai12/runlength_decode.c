#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSTR 100000000 // 文字列の最大長さ
#define MAXLEN   100000      //ファイルに書き込まれた1行の最大長

char *decode(char * string, int size);
int main(int argc, char *argv[]);

char *decode(char *string, int size){
	unsigned char *ret, prev, num;
	int i, j=0;
	
	ret = (char *)malloc(sizeof(char)*MAXSTR);
	
	for(i = 0; i < size; i++){
		prev = string[i];
		i++;
		for(num = string[i]; num>0; num--)
			ret[j++] = prev;
	}
	
	return ret;

}

int main(int argc, char *argv[]){

  char *string;
  char *tmp_string;
  char *ret;
  int index;
  int size;    //配列のサイズを保存
  clock_t start, end;
  char outname[100] = {};
  int i;
  
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
  i = 0;
  while((argv[1][i] != '.') && (argv[1][i] != '\0')){
    //printf("argv[1][%d] = %c\n", i, argv[1][i]);
    outname[i] = argv[1][i];
    i++;
  }
  outname[i] = '\0';
  strcat(outname, ".dec");


  if ((file_out=fopen (outname,"w")) == NULL){
    printf("output file not opened\n");
    exit(1);
  }


  //領域の確保
  string = (char *)malloc(sizeof(char)*MAXSTR);
  tmp_string = (char *)malloc(sizeof(char)*MAXLEN);
  
  // fgetsで入力ファイルの文字列を一行ずつ読み込み配列stringに格納
  while (fgets(tmp_string, MAXLEN, file_in)) {
    strcat(string,tmp_string);
  }
  
  size = strlen(string);
  printf("size = %d\n", size);
  start = clock();
  ret = decode(string, size);
  end = clock();
  
  //fileに出力
  size = strlen(ret);
  for (index=0; index<size; index++)
	putc(ret[index], file_out);

  printf("time: %.2f\n",(double)(end-start)/CLOCKS_PER_SEC);
  
  //メモリ領域の解放
  free(string);
  free(tmp_string);
  free(ret);
  fclose(file_in);
  fclose(file_out);
  
  return 0;
}

