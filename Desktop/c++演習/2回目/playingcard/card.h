//
// card.h - トランプカードの型
//  作者: (あなたの名前); 日付: (完成した日付)
//

#ifndef _CARD_H_
#define _CARD_H_

#include <cstdio>
#include <iostream>

//
// Card - トランプカード型
//
class Card {
 public:
    // クラス定数
    // トランプの組(suit)のコード
    enum {
        SUIT_BLANK = 0,
        SUIT_SPADE = 1,
        SUIT_DIAMOND, // 以下，自動的に 2, 3, ... と割当てられる
        SUIT_HEART,
        SUIT_CLUB,
        SUIT_JOKER,
        RANK_JOKER = 15, // Joker の rank 用のダミー値
    };

 private:
    ////////////////////////////////////////////////////////////
    // メンバ変数
    ////////////////////////////////////////////////////////////

    //  インスタンスメンバ変数．Card 型データ（オブジェクト）がそれぞれ持っているデータ．
    int suitval;    // 組
    int rankval;    // 番号

    ////////////////////////////////////////////////////////////
    // クラス変数
    ////////////////////////////////////////////////////////////

    //  static は，クラスメンバのこと．Card クラスの中で共通の定数として
    //  Card::suitnames で参照できる．
    //  クラス変数（定数）．値の初期化は .cpp で main の外に書いて行う
    static const char *suitnames[];
    static const char *ranknames[];

 public:
    ////////////////////////////////////////////////////////////
    // メンバ関数
    ////////////////////////////////////////////////////////////

    // デフォルトコンストラクタ（初期値はブランクカード）
    Card(void) : suitval(SUIT_BLANK), rankval(0) { }

    // 組と番号を与えるコンストラクタ
    Card(const int st, const int num) : suitval(st), rankval(num) { }

    // カードを与えるコンストラクタ
    Card(const Card &org) : suitval(org.suitval), rankval(org.rankval) { }

    // 組と番号を設定する
    void set(int st, int num) { suitval = st; rankval = num; }

    // アクセサ
    int rank(void) const { return rankval; }
    int suit(void) const { return suitval; }

    // まともなカードか？
    bool isValid(void) const;

    // 自身と tgt のカードの組，番号が等しいか判定 (true: 同; false: 異)
    // 同じアドレスにあるデータかどうか，ではない．
    bool equals(const Card &tgt) const {
        return (suitval == tgt.suitval) && (rankval == tgt.rankval || suitval == SUIT_JOKER);
    }

    // 文字列から自身の値をセット
    const char *readFrom(const char *);

    // ストリームから自身の値をセット
    std::istream &readFrom(std::istream &);

    // ファイルストリームに出力する
    // 第二引数に false を与えると，カードを伏せて表示
    std::ostream &printOn(std::ostream &, const bool faceup = true) const;

    // ストリーム出力演算子
    friend std::ostream &operator<<(std::ostream &os, const Card &c) {
        return c.printOn(os);
    }
};
#endif
