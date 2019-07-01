/*
 * matrix2.h
 * 2次元配列型(C++)
 *
 */

#ifndef _MATRIX2_H_
#define _MATRIX2_H_

#include <iostream>

/* 2次元ベクトル型 */
class matrix22 {

    private:
        double x1y1val,x2y1val,x1y2val,x2y2val; //行列の要素

    public:
    /* デフォルトコンストラクタ(引数なしのコンストラクタ) */
    matrix22(){
        x1y1val = 0.0;
        x2y1val = 0.0;
        x1y2val = 0.0;
        x2y2val = 0.0;
    }

    /* 初期化引数つきコンストラクタ */
    matrix22(double x1y1, double x2y1, double x1y2, double x2y2) {
        x1y1val = x1y1;
        x2y1val = x2y1;
        x1y2val = x1y2;
        x2y2val = x2y2;
    }

    /* コピーコンストラクタ */
    matrix22(const matrix22 &v) {
        x1y1val = v.x1y1val;
        x2y1val = v.x2y1val;
        x1y2val = v.x1y2val;
        x2y2val = v.x2y2val;
    }

    /* 行列の要素の(get)アクセサ  */
    double x1y1() const { return x1y1val; }
    double x2y1() const { return x2y1val; }
    double x1y2() const { return x1y2val; }
    double x2y2() const { return x2y2val; }

    /* 行列の要素の(set)アクセサ  */
    double x1y1(double x1y1) { return x1y1val = x1y1; }
    double x2y1(double x2y1) { return x2y1val = x2y1; }
    double x1y2(double x1y2) { return x1y2val = x1y2; }
    double x2y2(double x2y2) { return x2y2val = x2y2; }


    /* 要素を与えて自身 = (x1y1, x2y1,x1y2,x2y2) にする */
    void set(double x1y1, double x2y1, double x1y2, double x2y2);

    /* 要素を与えて自身 = (v.x1y1, v.x2y1, v.x1y2, v.x2y2) にする */
    void set(const matrix22 &v);

    /* 自身と v を加えた行列を返す */
    matrix22 add(const matrix22 &v);

    /* 自身から v を引いた行列を返す */
    matrix22 sub(const matrix22 &v);

    /* 自身と v をかけた行列を返す */
    matrix22 times(const matrix22 &v);


    /* 文字列から空白で区切られた浮動小数点数を 2 つ読み */
    /* v の 要素それぞれにセットする */
    char *readFrom(char *);

    /* ストリームから空白で区切られた浮動小数点数を 2 つ読み */
    /* それぞれを成分の値としてセットする */
    std::istream &readFrom(std::istream &);

    /* ベクトル v の値をファイルストリームに出力する */
    std::ostream &printOn(std::ostream &) const;

    /* ベクトル v の値を標準出力に出力する */
    void print() const { printOn(std::cout); }

    /* ストリーム出力演算子 */
    friend std::ostream &operator<<(std::ostream &os, const matrix22 &v) {
        return v.printOn(os);
    }
};

#endif /* # _MATRIX2_H_*/
