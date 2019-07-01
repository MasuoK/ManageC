/*
 * vector2d.h
 * 2次元ベクトル型(C++版)
 *
 */

#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <iostream>
#include"matrix22.h"

/* 2次元ベクトル型 */
class vector2d {

private:
    double xval, yval; /* x座標値, y座標値 */

public:
    /* デフォルトコンストラクタ(引数なしのコンストラクタ) */
    vector2d() {
      //xval = 1.0;  //演習3(1)これがあるときとないとき(初期値の確認)の両方が必要
      //yval = 1.0;  //
      //std::cout << "vector2d()" << ", xval: " << xval << ", yval: " << yval << std::endl;  //演習3(2)

    }

    /* 初期化引数つきコンストラクタ */
    vector2d(double x, double y) {
        //std::cout << "vector2d(double x, double y)" << ", x: " << x << ", y: " << y << std::endl;  //演習3(2)
        //xval = x;
        //yval = y;
    }

    /* コピーコンストラクタ  */ //演習3
    /*
    vector2d(const vector2d &v){
      std::cout << "vector2d(const vector2d &v)" << ", v.xval: " << v.xval << ", v.yval: " << v.yval << std::endl;
      xval=v.xval;
      yval=v.yval;
    }
    */

    /* x座標値，y座標値の(get)アクセサ */
    double x() const { return xval; }
    double y() const { return yval; }

    /* x座標値，y座標値の(set)アクセサ */
    double x(double x) { return xval = x; }
    double y(double y) { return yval = y; }

    /* x, y を与えて自身 = (x, y) にする */
    void set(double x, double y);

    /* x, y を与えて自身 = (v.x, v.y) にする */
    void set(const vector2d v);

    /* 自身と v を加えたベクトルを返す */
    vector2d add(const vector2d v);

    /* 自身から v を引いたベクトルを返す */
    vector2d sub(const vector2d v);

    /* 自身と 行列v をかけたベクトルを返す */
    vector2d times(const matrix22 &v);

    /* 文字列から空白で区切られた浮動小数点数を 2 つ読み */
    /* v の x, y 成分それぞれにセットする */
    char *readFrom(char *);

    /* ストリームから空白で区切られた浮動小数点数を 2 つ読み */
    /* それぞれを成分の値としてセットする */
    std::istream &readFrom(std::istream &);

    /* ベクトル v の値をファイルストリームに出力する */
    std::ostream &printOn(std::ostream &) const;

    /* ベクトル v の値を標準出力に出力する */
    void print() const { printOn(std::cout); }

    /* ストリーム出力演算子 */
    friend std::ostream &operator<<(std::ostream &os, const vector2d &v) {
        return v.printOn(os);
    }
};

#endif /* _VECTOR2D_H_ */
