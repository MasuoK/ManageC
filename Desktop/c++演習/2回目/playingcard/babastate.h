//
// babastate.h - ババ抜きの状態型(C++版)
//  作者: (あなたの名前); 日付: (完成した日付)
//
#ifndef _BABASTATE_H_
#define _BABASTATE_H_

#include "card.h"
#include "cardset.h"

//
// BabaState - ババ抜きの状態型
//
class BabaState {
// 定義・宣言
public:
    static const int numplayer = 4; // 総プレーヤ数

// メンバ変数
private:
    CardSet hand[numplayer];  // 各プレーヤの持ち手
    CardSet pile; // 最後に場に捨てられた札

    int turnIndex;

// メンバ関数
public:
    // デフォルトコンストラクタ(初期値はカードを配った状態)
    BabaState(void) { reset(); }

    // リセット(はじめにカードを配りおえた状態にする)
    // 0 番プレーヤーは最初にカードを引く
    void reset(void);

    // pindex 番のプレーヤが上がった(終了した)か否かの判定
    // (true: 上がった; false: まだ上がっていない)
    bool isFinished(int pindex) const { return hand[pindex].isEmpty(); }

    // ターンが回ってきた（カードを引く）プレーヤー
    int inTurn() const { return turnIndex; }

    // 次にターンが回ってくる（カードを取らせる）プレーヤー
    int nextTurn(void);

    // ターンを次のプレーヤーに回す
    bool goNext(void);

    // まだ手札を持っているプレーヤーの数
    int countPlaying(void) const;

    // pindex 番のプレーヤが持っているカード枚数
    int countCards(const int pindex) const { return hand[pindex].size(); }

    // to 番のプレーヤが from 番のプレーヤからカードを取る
    // ペアができれば捨てる
    // 渡ったカード（のコピー）を返す
    Card move(int from, int to);

    // pindex 番のプレーヤーの手札のペアをすべて捨てる
    void wastePair(int pindex);

    // 状態をストリームに出力する
    // player 0 以外のカードを伏せるには，第二引数に false を渡す．
    std::ostream &printOn(std::ostream &out, const bool faceup = true) const;

    friend std::ostream &operator<<(std::ostream &out, const BabaState &bs) {
        return bs.printOn(out);
    }
};

#endif
