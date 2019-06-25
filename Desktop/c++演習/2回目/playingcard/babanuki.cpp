//
// babanuki.cpp - ババ抜きプログラム(C++版)
//  作者: (あなたの名前); 日付: (完成した日付)
//
#include "babastate.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <getopt.h>

//
// main() - ババ抜きプログラム
//
int main(int argc, char * const argv[]) {
    char tmp[32];
    BabaState bstat;    // ババ抜きの状態
    int turn, next; // プレーヤーの番号用
    Card card;
    bool faceup = true;   // カード公開モード．false にすると，ゲームっぽいかもしれない
    int opt;

    // コマンドラインオプションの解析
    while ((opt = getopt(argc, argv, ":udh")) != -1) {
      switch(opt) {
      case 'u':
        faceup = true;
        break;
      case 'd':
        faceup = false;
        break;
      case 'h':
        std::cerr << "Usage: " << argv[0] << " [-u] [-d] [-h]" << std::endl;
        std::cerr << "        -u      ; face-up mode" << std::endl;
        std::cerr << "        -d      ; face-down mode" << std::endl;
        std::cerr << "        -h      ; show this message" << std::endl;
        exit(1);
        break;
      default:
        break;
      }
    }

    // 配り終えた状態の表示
    std::cout << "### カードを配り終えた状態" << std::endl; 
    bstat.printOn(std::cout, faceup);
    std::cout << std::endl;

    // ペアをすべて捨てる
    for(int pindex = 0; pindex < bstat.numplayer; ++pindex)
        bstat.wastePair(pindex);
    // 最初の手札を整理し終わった状態の表示
    std::cout << "### ペアをすべて捨てた後" << std::endl;   
    bstat.printOn(std::cout, faceup);
    std::cout << std::endl;

    // 終了条件になるまでカードを引き続ける
    // bstat.inTurn() 番のプレーヤーから次の bstat.nextTurn() 番のプレーヤーが
    // カードを引く
    while (bstat.countPlaying() > 1) {  // 最後の一人になるまで
        turn = bstat.inTurn();
        next = bstat.nextTurn();

        // turn 番のプレーヤから next 番のプレーヤがカードを一枚とる
        card = bstat.move(turn, next);
        std::cout << "## PLAYER " << turn
                << " から，PLAYER " << next << " が，カード ";
        if (turn == 0 || next == 0)
            card.printOn(std::cout, true); // 自分が取られたカード
        else
            card.printOn(std::cout, faceup);
        std::cout << " を取った" << std::endl << std::endl;
        if ( bstat.countCards(turn) == 0 ) {
            std::cout << "# プレーヤ " << turn << "あがり．" << std::endl;
        }
        if ( bstat.countCards(next) == 0 ) {
            std::cout << "# プレーヤ " << next << "あがり．" << std::endl;
        }

        bstat.printOn(std::cout, faceup);
        std::cout << std::endl;

        // ターンを次にまわす
        bstat.goNext();

        std::cin.getline(tmp, 32); // return/enter されるまで待つ
    }

    std::cout << std::endl << "### FINISHED ###" << std::endl;

    return 0;
}
