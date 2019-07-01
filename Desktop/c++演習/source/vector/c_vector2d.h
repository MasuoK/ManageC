/*
 * c_vector2d.h
 * 2次元ベクトル型(C版)
 *
 *  Created on: 2017/02/23
 *      Author: sin
 */

#ifndef _C_VECTOR2D_H_
#define _C_VECTOR2D_H_

#include <stdio.h>

/* 2次元ベクトル型 */
struct vector2d {
    double x, y;
};
typedef struct vector2d vector2d;

/* プロトタイプ宣言 */

/* 値 x, y を与えて v = (x, y) にする */
void set(vector2d *v, double x, double y);

/* ベクトル u の各成分の値を v と同じにする */
void copy(vector2d *u, vector2d *v);

/* ベクトル u + v を作成して返す，u と v は変更しない */
vector2d add(vector2d *u, vector2d *v);

/* ベクトル u - v を作成して返す, u と v は変更しない*/
vector2d sub(vector2d *u, vector2d *v);

/* 文字列から空白で区切られた浮動小数点数を 2 つ読み */
/* v の x, y 成分それぞれにセットする */
char *readFrom(vector2d *v, char *str);

/* ベクトル v の値をファイルストリームに出力する */
size_t printOn(FILE *fp, vector2d *v);

/* ベクトル v の値を標準出力に出力する */
void print(vector2d *v);


#endif /* _C_VECTOR2D_H_ */
