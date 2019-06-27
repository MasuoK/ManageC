//
// babastate.cpp - ババ抜きの状態型(C++版)
//  作者: (あなたの名前); 日付: (完成した日付)
//

#include <iostream>

#include "babastate.h"

//
// BabaState::reset() - リセット(最初にカードを配った直後の状態にする)
//
void BabaState::reset(void) {
    // 各プレーヤの持ち手を空にする
    for (int i = 0; i < numplayer; i++) {
        hand[i].clear();
    }
    turnIndex = 0;
    // デッキ(1セット)のカードを deck に入れる
    CardSet deck;
    deck.setupDeck();
    deck.shuffle();

    // 無くなるまでカードをとり pindex 番のプレーヤに配る
    // 配る順番は pindex が減る（ターンがまわるのと逆）向き
    int pindex = 0; // 配る相手のプレーヤ
    Card c;         // 配るカード
    while (!deck.isEmpty()) {
        deck.draw(c, 0);
        // deck から一枚抜いてプレーヤーに渡す
        hand[pindex].insert(c);
        // pindex を次のプレーヤにする．カードをくばる対象は全員
        pindex = (pindex + 1) % numplayer;
    }
}

// 次にターンが回ってくる（カードを取らせる）プレーヤー
int BabaState::nextTurn(void) {
    int next = turnIndex;
    do {
        next = (next + 1) % numplayer;
    } while (isFinished(next) && next != turnIndex);
    return next;
}

// ターンを次のプレーヤーに回す
bool BabaState::goNext() {
    int next = nextTurn();
    if ( next != turnIndex ) {
        turnIndex = next;
        return true;
    }
    return false; // 失敗
}


// to 番のプレーヤが from 番のプレーヤからカードを取る
// ペアができれば捨てる
// 渡ったカード（のコピー）を返す

Card BabaState::move(int from, int to){
    //from番目のプレイヤーの持ち手からカードをランダムにとる
    //draw(Card & card, int targetpos): targetposが-1または、手札の上限を超えた場合ランダムにカードが取られる
    //hand[]はcardset型
    //drawとinsertはcardset型のメソッド
    
    Card c;
    if(hand[from].draw(c,-1)){
        if(hand[to].insert(c)){
            wastePair(to); //to番のプレーヤーでペアになったカードを捨てる
        }
    }
    
    return c;
}


void BabaState::wastePair(int pindex) {
    Card c, d;
    int reps;
    int hand_size = hand[pindex].size();
    for(reps = 0; reps < hand_size; ++reps) {
        // 人間風にペアを見つけるのを繰り返す
        for(int i = 0; i < hand[pindex].size() - 1; ++i) {
            c = hand[pindex].at(i);
            for(int j = i + 1; j < hand[pindex].size(); ++j) {
                d = hand[pindex].at(j);
                if ( c.rank() == d.rank() ) {
                    hand[pindex].remove(c);
                    hand[pindex].remove(d);
                    break;
                }
            }
            if ( c.rank() == d.rank() )
                break;
        }
    }
    return;
}

// まだ手札を持っているプレーヤーの数
int BabaState::countPlaying() const {
    int count = 0;
    for (int i = 0; i < numplayer; ++i) {
        if (!isFinished(i))
            ++count;
    }
    return count;
}

// 状態をストリームに出力する
std::ostream & BabaState::printOn(std::ostream & out, const bool faceup) const {
    for (int i = 0; i < numplayer; i++) {
        out << "PLAYER " << i << ": ";
        if (i == 0)
            hand[i].printOn(out, true); // PLAYER 0 は「自分」
        else
            hand[i].printOn(out, faceup);
        out << ", " << std::endl;
    }
    return out;
}
