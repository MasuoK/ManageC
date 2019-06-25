//
// cardset.cpp - トランプカードの集合型(C++版)
//  作者: (あなたの名前); 日付: (完成した日付)
//

#include <iostream>
#include <random>

#include "card.h"
#include "cardset.h"

//
// CardSet::find() - target に等しいカードの位置(添字)を返す (not_found == -1: ない)
//
int CardSet::find(const Card &target) const {
    for (int i = 0; i < count; i++) {
        if (target.equals(cards[i]))
            return i;
    }
    return not_found;  // 見つからなかった
}

//
// CardSet::find() - 数字が num のカードの位置(添字)を返す (not_found == -1: ない)
//
int CardSet::find(int number) const {
    for (int i = 0; i < count; i++) {
        if (number == cards[i].rank())
            return i;
    }
    return not_found;  // 見つからなかった
}

//
// CardSet::setupDeck() - 自身に全部の(maxnumcard 枚の)カードを入れる
//
void CardSet::setupDeck(void) {
    Card c;
    int suit, num;

    for (suit = Card::SUIT_SPADE; suit <= Card::SUIT_CLUB; suit++)
        for (num = 1; num <= 13; num++) {
            c.set(suit, num);
            insert(c);
        }
    c.set(Card::SUIT_JOKER, Card::RANK_JOKER);
    insert(c);
}

// 自身から targetpos 枚目 (先頭は 0 枚目) のカードを除き，
// そのカードを引数 card で返す
// targetpos が -1 またはカード数以上のときはランダムに選ぶ
// 第2引数を省略した場合は -1 が指定されたものとみなす(デフォルト引数)
// (false: 要素数に変化なし，card の値は変更されない; true: 成功)
// remove() を実装した後でコメントを外して，draw を使えるようにせよ

bool CardSet::draw(Card & card, int targetpos) {
	std::random_device rand;

	if( targetpos == not_found )
		targetpos = rand() % count;
	else if( count == 0 || targetpos >= count )
		return false;

	card = cards[targetpos];
	return remove(card);
}


//
// CardSet::insert() - newcard を入れる (false: 失敗; true: 成功)
// 既にあるカードを挿入しようとしたか，または，満杯状態の場合は失敗
//
bool CardSet::insert(const Card &newcard) {
    int position = find(newcard);
    if (position >= 0)          // 既にある
        return false;
    if (count >= maxnumcard)    // もう入らない
        return false;
    // 最後に追加
    position = count;
    count++;
    cards[position] = newcard;

    return true;
}


// target に等しいカードを取り除く (false: 失敗; true: 成功)
// 該当するカードが無い場合は失敗
bool CardSet::remove(const Card &target){
    int i;
    int rem;
    rem = find(target);
    if(rem == not_found)
        return false;
    count--;
    for(i = rem; i < count; i++){
        cards[i] = cards[i+1];
    }
    return true;
}

// rank が num に等しいカードを1枚除く (false: 失敗; true: 成功)
// 該当するカードが複数枚あっても，除くのは1枚だけ
bool CardSet::remove(int num){
    int i;
    int rem;
    rem = find(num);
    if(rem == not_found)
        return false;
    count--;
    for(i = rem; i < count; i++){
        cards[i] = cards[i+1];
    }
    return true;
}

// シャフルする patched version
void CardSet::shuffle(void) {
    std::random_device rnd;
    int t, i, j;
    Card swap;

    for (t = 0; t < 106; t++) {
      i = rnd() % count;
      j = rnd() % (count - 1);
      if ( j >= i ) {
    	  ++j;
      }
	  swap = cards[i];
	  cards[i] = cards[j];
	  cards[j] = swap;
    }
}

// rank と suit で昇順にソートする
void CardSet::sort() {
    Card t;
    for(int i = 0; i < count - 1; ++i) {
        for(int j = i+1; j < count; ++j) {
            if (cards[i].rank() > cards[j].rank()
                    || (cards[i].rank() == cards[j].rank() && cards[i].suit() > cards[j].suit())) {
                t = cards[j];
                cards[j] = cards[i];
                cards[i] = t;
            }
        }
    }
}

//
// CardSet::printOn() - 自身を出力する
//
std::ostream & CardSet::printOn(std::ostream &out, const bool faceup) const {
    out << "CardSet: { ";
    for (int i = 0; i < count; i++) {
        cards[i].printOn(out, faceup);
        out << " ";
    }
    out << "}";
    return out;
}
