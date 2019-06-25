//
// cardsetextra.cpp - トランプカードの集合型(C++版)テストプログラム
//  作者: (あなたの名前); 日付:2019/06/20 (完成した日付)
//
#include <iostream>
#include <string>

#include "cardset.h"
#include "card.h"

//
// main() - トランプカードの集合型テストプログラム
//

int main(int argc, char *const argv[]) {
        Card c;
        CardSet cset;

        int remove_num; //取り除く番号
        std::string buf;

        // カード入力がエラーになるまで指定したカードを入れる
        do {
            std::cout << cset << std::endl;
            std::cout << "Type 'suit number', or 'q' to quit : ";
            c.readFrom(std::cin);
            if (!c.isValid())
                break;       // 正しいカードをスキャンできなかったらループを終了
            std::cout << c << std::endl;
        } while (cset.insert(c));   // 挿入に失敗したらループを終了

        // カード入力がエラーになるまで指定したカードを消す
        do {
            std::cout << cset << std::endl;
            std::cout << "remove 'suit number', or 'q' to quit : ";
            c.readFrom(std::cin);
            if (!c.isValid())
                break;       // 正しいカードをスキャンできなかったらループを終了
            std::cout << c << std::endl;
        } while (cset.remove(c));   // 削除に失敗したらループを終了


        // カード入力がエラーになるまで指定したカードを消す(数字)  
        do {
            std::cout << cset << std::endl;
            std::cout << "remove 'number', or 'q' to quit : ";
            //c.readFrom(std::cin);
            std::
            cin >> remove_num;
        } while (cset.remove(remove_num));   // 削除に失敗したらループを終了
        
        //      std::cout << "Sorting.";
        //      cset.sort();
        //      std::cout << std::endl;

        std::cout << cset << std::endl;
        return 0;
}
