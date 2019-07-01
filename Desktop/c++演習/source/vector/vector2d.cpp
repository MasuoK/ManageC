/*
 * vector2d.cpp
 * 2次元ベクトル型(C++版)
 *
 *
 */

#include <iostream>
#include <cstdlib>

#include "vector2d.h"

/* x, y を与えて自身を (x, y) にする */
void vector2d::set(double x, double y) {
  //std::cout << "vector2d::set(double x, double y)"<< std::endl;
  xval = x;
  yval = y;
}

/* v を与えて自身を (v.x, v.y) にする */
//3-3(3)引数にconstと&を追加
void vector2d::set(const vector2d v) {
  //std::cout << "vector2d::set(const vector2d &v)"<< std::endl;
  xval = v.xval;
  yval = v.yval;
}

/* 自身と v を加えたベクトルを返す */
vector2d vector2d::add(const vector2d v) {
  //std::cout << "vector2d::add(vector2d &v)"<< std::endl;
  vector2d r(xval + v.xval, yval + v.yval);
  // 上は r に対するコンストラクタ呼出し
  // 引数に加算の計算結果を与えている
  return r;
}

/* 自身と v を加えたベクトルを返す */
vector2d vector2d::sub(const vector2d v) {
  //std::cout << "vector2d::sub(vector2d &v)"<< std::endl;
  vector2d r(xval - v.xval, yval - v.yval);
  // 上は r に対するコンストラクタ呼出し
  // 引数に減算の計算結果を与えている
  return r;
}

/* 自身と 行列v をかけたベクトルを返す */
vector2d vector2d::times(const matrix22 &v){
  vector2d r(xval * v.x1y1() + yval * v.x1y2(), xval * v.x2y1() + yval * v.x2y2());
  return r;
}

/* 文字列から空白で区切られた浮動小数点数を 2 つ読み */
/* v の x, y 成分それぞれにセットする */
char *vector2d::readFrom(char *str) {
  xval = strtod(str, &str);
  yval = strtod(str, &str);
  
  return str;
}

/* ストリームから空白で区切られた浮動小数点数を 2 つ読み */
/* それぞれを成分の値としてセットする */
std::istream &vector2d::readFrom(std::istream &is) {
    is >> xval;
    is >> yval;
    return is;
}

/* ベクトル v の値をファイルストリームに出力する */
std::ostream &vector2d::printOn(std::ostream &os) const {
    os << "(" << xval << ", " << yval << ")";
    return os;
}
