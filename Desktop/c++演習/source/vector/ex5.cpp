// ex5.cpp - 2次元ベクトル型(C++版)テストプログラム
//  作者: (あなたの名前); 日付:2019/06/20 (完成した日付)
//

#include <iostream>
#include <cstdlib>
#include <stdio.h>

#include "vector2d.h"
#include "matrix22.h"

#define BUFSIZE 256

//
// main() - テストプログラム
//
int main(int argc, char *argv[]) {
    matrix22 a, b, t;
    vector2d c, d, s;
    char buf[BUFSIZE];

    // ベクトル c, d の入力
    printf("ベクトルの2つの要素を空白で区切って入力して下さい\n");
    printf("c = ? ");
    std::cin.getline(buf, BUFSIZE);
    c.readFrom(buf);
    printf("c = ");
    c.print();
    printf("\n");

    std::cout << "d = ? ";
    d.readFrom(std::cin);
    std::cout << "d = " << d << std::endl << std::endl;

    // c + d を出力
    std::cout << "c + d = " << c.add(d) << std::endl;

    // c - d を出力
    std::cout << "c - d = " << c.sub(d) << std::endl;

    // c + (2, 1) を出力
    d.set(2,1);
    s.set(c);
    std::cout << "c + (2,1) = " << s.add(d) << std::endl;

    // c - (2, 1) を出力
    d.set(2,1);
    s.set(c);
    std::cout << "c - (2,1) = " << s.sub(d) << std::endl;

    // x1y1, x2y1, x1y2, x2y2の入力
    printf("行列の4つの要素を空白で区切って入力して下さい\n");
    printf("a = ? ");
    a.readFrom(std::cin);
    printf("a = ");
    a.print();
    printf("\n");

    // C++ での入出力の標準的なやり方
    // std は標準ライブラリ，std::cout は，標準出力のこと．
    // << は，ファイルへの出力演算子．std::endl は，改行記号．
    std::cout << "b = ? ";
    b.readFrom(std::cin);
    std::cout << "b = " << b << std::endl << std::endl;

    // a + b を出力
    std::cout << "a + b = " << a.add(b) << std::endl;

    // a - b を出力
    std::cout << "a - b = " << a.sub(b) << std::endl;

    // a * b を出力
    std::cout << "a * b = " << a.times(b) << std::endl;

    // a + (2, 1, 3, 2) を出力
    b.set(2,1,3,2);
    t.set(a);
    std::cout << "a + (2,1,3,2) = " << t.add(b) << std::endl;

    // a - (2, 1, 3, 2) を出力
    b.set(2,1,3,2);
    t.set(a);
    std::cout << "a - (2,1,3,2) = " << t.sub(b) << std::endl;

    // a * (2, 1, 3, 2) を出力
    b.set(2,1,3,2);
    t.set(a);
    std::cout << "a * (2,1,3,2) = " << t.times(b) << std::endl;


    // c * a を出力
    std::cout << "c * a = " << c.times(a) << std::endl;


    return EXIT_SUCCESS;
}
