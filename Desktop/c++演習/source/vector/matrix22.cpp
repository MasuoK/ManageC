#include <iostream>
#include <cstdlib>

#include "matrix22.h"

/* 要素を与えて自身 = (x1y1, x2y1,x1y2,x2y2) にする */
void matrix22::set(double x1y1, double x2y1, double x1y2, double x2y2){
    x1y1val = x1y1;
    x2y1val = x2y1;
    x1y2val = x1y2;
    x2y2val = x2y2;
}

/* 要素を与えて自身 = (v.x1y1, v.x2y1, v.x1y2, v.x2y2) にする */
void matrix22::set(const matrix22 &v){
    x1y1val = v.x1y1val;
    x2y1val = v.x2y1val;
    x1y2val = v.x1y2val;
    x2y2val = v.x2y2val;
}

/* 自身と v を加えた行列を返す */
matrix22 matrix22::add(const matrix22 &v){
  matrix22 r(x1y1val + v.x1y1val, x2y1val + v.x2y1val, x1y2val + v.x1y2val, x2y2val + v.x2y2val);
  // 上は r に対するコンストラクタ呼出し
  // 引数に加算の計算結果を与えている
  return r;
}

/* 自身から v を引いた行列を返す */
matrix22 matrix22::sub(const matrix22 &v){
  matrix22 r(x1y1val - v.x1y1val, x2y1val - v.x2y1val, x1y2val - v.x1y2val, x2y2val - v.x2y2val);
  // 上は r に対するコンストラクタ呼出し
  // 引数に減算の計算結果を与えている
  return r;
}

/* 自身と v をかけた行列を返す */
matrix22 matrix22::times(const matrix22 &v){
  matrix22 r(x1y1val * v.x1y1val + x2y1val * v.x1y2val, x1y1val * v.x2y1val + x2y1val * v.x2y2val, x1y2val * v.x1y1val + x2y2val * v.x1y2val, x1y2val * v.x2y1val + x2y2val * v.x2y2val);
  // 上は r に対するコンストラクタ呼出し
  // 引数に乗算の計算結果を与えている
  return r;
}


/* 文字列から空白で区切られた浮動小数点数を 2 つ読み */
/* v の x, y 成分それぞれにセットする */
char *matrix22::readFrom(char *str) {
  x1y1val = strtod(str, &str);
  x2y1val = strtod(str, &str);
  x1y2val = strtod(str, &str);
  x2y2val = strtod(str, &str);
  
  return str;
}

/* ストリームから空白で区切られた浮動小数点数を 2 つ読み */
/* それぞれを成分の値としてセットする */
std::istream &matrix22::readFrom(std::istream &is) {
    is >> x1y1val;
    is >> x2y1val;
    is >> x1y2val;
    is >> x2y2val;

    return is;
}

/* ベクトル v の値をファイルストリームに出力する */
std::ostream &matrix22::printOn(std::ostream &os) const {
    os << "(" << x1y1val << ", " << x2y1val << ", " << x1y2val << ", " << x2y2val << ")";
    return os;
}
