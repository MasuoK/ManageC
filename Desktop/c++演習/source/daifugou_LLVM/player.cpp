/*
 *  Player.cpp
 *  PlayingCard
 *
 *  Created by 下薗 真一 on 09/04/12.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>

#include "player.h"

#include "card.h"
#include "cardset.h"
#include "gamestatus.h"

/* 変更不可 */
void Player::clearHand() {
	hand.clear();
}

/* 変更不可 */
bool Player::isEmptyHanded() const {
	return hand.isEmpty();
}

/* 変更不可 */
bool Player::takeCards(Card & c) {
	return hand.insert(c);
}

/* 変更不可 */
bool Player::takeCards(CardSet & s) {
	if (!s.isEmpty())
		for (int i = 0; i < s.size(); ++i)
			hand.insert(s[i]);
	return true;
}

/* 変更不可 */
std::ostream & Player::printOn(std::ostream & out) const {
	out << name << ": ";
	hand.printOn(out);
	return out;
}


int Player::strength(const int rank) {
	switch(rank) {
	case 0:
	case Card::RANK_JOKER:
		return rank;
	case 1:
	case 2:
		return rank + 11;
	default:
		return rank - 2;
	}
}

Player::Player(char const * given) {
	hand.clear();
	name = given; // convert into std::string
	return;
}

void Player::ready(void) {
	// 新しいゲームがはじまるので，とりあえず手札を昇順にならべてみる
	hand.sort(daifugouAscending);
}

bool Player::approve(const GameStatus & gstat) {
	// どんなカードも見過ごす
  return true;
}

bool Player::follow(const GameStatus & gstat, CardSet & cards) {
	Card tmp;

	/*
	 *  cards はカラの状態で渡される．
	 */
	CardSet pile(gstat.pile); // 場札（リード）を pile に取り出す
	// ルールがまだよくわかっていない初心者

	/* 出すカードは draw でランダムに取り出す．*/
	hand.draw(tmp, -1);
	cards.insert(tmp);
	/*
	 * 出したカードは手札からなくなる．
	 * reject された場合は，Dealer により手札にもどされる．
	 * その場合，後ろに入れられるので hand は昇順でなくなってしまう
	 */
	return true;
}

