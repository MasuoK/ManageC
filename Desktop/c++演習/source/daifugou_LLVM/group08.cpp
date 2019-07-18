/*
 *  Group08.cpp
 *  PlayingCard
 *
 *  Created by 下薗 真一 on 09/04/12.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include <random>
#include <cstdlib>

#include "player.h"
#include "gamestatus.h"

#include "group08.h"
#include "card.h"
#include "cardset.h"

void Group08::ready(void) {
	/* 手札を昇順にならべかえ */
	hand.sort(daifugouAscending);

	/* 初期化 */
	oldRank = 0;
	for (int i = 0; i < 16; i++) {
		served[i] = 0;
		remain[i] = 4;
	}
	remain[0]  = 0;
	remain[14] = 0;
	remain[15] = 1;

	/* 自分の手札を元にremainを構築 */
	for(int i = 0; i < hand.size(); i++) {
		remain[strength(hand.at(i).rank())] -= 1;
	}
}

bool Group08::follow(const GameStatus & gstat, CardSet & cards) {
	CardSet pile(gstat.pile); 		// リード（場札）を pile に取り出す
	leadSize = pile.size();
	leadRank = 0;
	int histo[Card::RANK_JOKER+1];
	std::random_device rdev;

	// リードの rank を得る
	if ( leadSize > 0 ) {
		pile.sort(daifugouAscending); // strength の昇順にする
		leadRank = pile.at(0).rank(); // リードの（あれば Joker 以外のカードの）rank
	}

	std::srand(rdev());
	makeHistogram(histo); // strength ごとに数える
	for(myStrength = strength(leadRank) + 1 ; myStrength < Card::RANK_JOKER + 1 ; ++myStrength) {
		if ( histo[myStrength] == 0 ) continue;
		if ( leadSize == 0 ) break;
		if ( histo[myStrength] < leadSize ) continue;
		if ( (histo[myStrength] >= leadSize) ) break;
	}

	// myStrength == 16 はパス
	if ( myStrength < Card::RANK_JOKER + 1 ) {
		/* 手札情報を構築し，最大値とその組を求める */
		makeHandInfo();
        if(leadRank == 0) { // 自分がリーダーの時
			bool conti = true;
			/* Jkr + 1種類の時は必ず上がれるのでJkrを出す */
			if (tmplist[15] && myCardKind() == 1) {
				serveCard(cards, 15, 1);
				conti = false;
			}
			/* 実質Jkr + 1種類の時は必ず上がれるので実質Jkrを出す */
			else if (myCardKind() == 2 && tmplist[15] == 0) {
				serveCard(cards, 4);
				if (cards.size()) { conti = false; }
			}
			else {
				/* 自分の持っているカードのペアの枚数が相手の持っているカードのペアの枚数より多いかつ相手のペアのスート以下の強さのスートの場合
				(相手のペアの方が強い場合は勝てないので親限定の手) */
				/* 上の条件の時にカードを自分が1種類のカードを持っている時
				は必ず上がれるので上の条件を満たすカードのペアをだす */

				//1~13で相手より枚数が多いペアを調べる
				//自分の最も枚数の多い(かつ最も弱い)ペアを調べる
				myMax = 0; myMaxNum = 0;
				for(int i = 1; i < 14; i++){
					if(myMaxNum < tmplist[i]){
						myMax = i;
						myMaxNum = tmplist[i];
					}
				}

				//相手の最も枚数の多い(かつ最も強い)ペアを調べる
				otherMax = 0; otherMaxNum = 0;
				for(int i = 1; i < 14; i++){
					if(otherMaxNum <= remain[i]){
						otherMax = i;
						otherMaxNum = remain[i];
					}
				}

				if(myMaxNum > otherMaxNum && myMax <= otherMax && myCardKind() == 2){
					serveCard(cards, 5);
					//std::cout << "pattern5" << std::endl;
					conti = false;
				}

				/* または、ペアの枚数が自分の持っているペアが相手の持っているペアよりも強くてかつ、枚数が相手のペア以上の時も絶対に勝てる(親でも子でも成立) */
				/* 上の条件の時にカードを自分が1種類のカードを持っている時
				は必ず上がれるので上の条件を満たすカードのペアをだす */
			
				/* 自分が持っているカードで強さ1~13で最もつよいペアを調べる*/
				strongestStrengthMy = 0; strongestCountMy = 0;
				strongestMy(strongestStrengthMy,strongestCountMy);

				/* 相手が持っているカードで強さ1~13で最もつよいペアを調べる*/
				strongestStrength = 0; strongestCount = 0;
				strongestOt(strongestStrength, strongestCount);

				if(conti && strongestStrengthMy > strongestStrength && strongestCountMy >= strongestCount && myCardKind() == 2){
					serveCard(cards, 6);
					//std::cout << "pattern6" << std::endl;
					conti = false;
				}
			}
			/* 強さ1~9で3枚以上で一番多いペア数のうち最も小さいrankを出す */
			int maxStrength, maxCount;
			myMaxCard(maxStrength, maxCount, 1, 9);
			if (maxCount > 2 && conti) {
				serveCard(cards, maxStrength, maxCount);
			}
			/* 何も出していない場合一番小さいrankを出す */
			if (cards.size() == 0) { serveCard(cards, 0); }
        } else { // 自分がリーダーでない時
			if (remainCount() > 20) { // 前半
				serveCard(cards, 2);
				// if (cards.size() == 0) { serveCard(cards, 3); }
			}
			else { // 後半
				/* ペア1で来て，Jkr + 1種類の時，Jkrを出してリーダーになり上がる */
				if (leadSize == 1 && tmplist[15] && myCardKind() == 1) {
					serveCard(cards, 15, 1);
				/* ペア1で来て，実質Jkr + 1種類の時，実質Jkrを出してリーダーになり上がる*/
				} else if (leadSize == 1 && myCardKind() == 2 && tmplist[15] == 0) {
					serveCard(cards, 4);
					if (!cards.size()) { serveCard(cards, 3); }
				} else {
					serveCard(cards, 3);
				}
			}

			// if (cards.size() == 0) { serveCard(cards, 0); }
		}
	}

	/* すでに出たランクの総数に加算（自分が出した時用） */
	served[strength(cards.at(0).rank())] += cards.size();

	return true;
}

// strength 値でヒストグラムを作る
void Group08::makeHistogram(int h[Card::RANK_JOKER+1]) {
	for(int i = 0; i <= Card::RANK_JOKER; ++i)
		h[i] = 0;
	for(int i = 0; i < hand.size(); ++i) {
		h[strength(hand.at(i))]++;
	}
}

bool Group08::approve(const GameStatus & gstat) {
	/* すでに出た強さの総数に加算（他人が出した時用） */
	int nowRank = gstat.pile.at(0).rank();
	if (nowRank != oldRank) {
		int count = gstat.pile.size();
		served[strength(nowRank)] += count; // すでに出たランクごとカード総数
		remain[strength(nowRank)] -= count; // 他人が所持しているランクごとカード総数
		oldRank = nowRank;
	}

  	return true;
}

/* 強さがstrongのカードをcount枚出す関数 */
void Group08::serveCard(CardSet & cards, int strength, int count) {
	Card tmp;
	int tmpCount = 0;
	for (int i = 0; i < hand.size(); ) {
		if (hand.at(i).rank() == strengthTOrank(strength)) {
			if(hand.draw(tmp, i)) {
				tmpCount++;
                cards.insert(tmp);
        	} else {
				std::cout << "serveCardの引数に対して出せるカードがありません" << std::endl;
			}
			if (tmpCount == count) {
				return;
			}
        } else { i++; }
	}

	return;
}

/* 指定の出し方をする関数 */
void Group08::serveCard(CardSet & cards, int command) {
	Card tmp;
	switch (command)
	{
	case 0: // 出せるカードの内最小Rankで出す
		for (int i = myStrength; i < 16;) {
			if (tmplist[i] == leadSize - 1 && tmplist[15]) {
				serveCard(cards, i, leadSize - 1);
				serveCard(cards, 15, 1);
				break;
			} else if (tmplist[i] >= leadSize) {
				serveCard(cards, i, leadSize);
				break;
			} else {
				i++;
			}
		}
		break;

	case 1: // 出せるカードの内最小Rankで出す（ただしJkrは出さない）
		for(int i = 0; i < hand.size(); ) {
			if (hand.at(i).isJoker()) {
				break;
			}
			if ( strength(hand.at(i).rank()) == myStrength ) {
				if (tmplist[i] >= leadSize) {
				//1や2の1枚出しでなければ、普通に出す
				if((i != 13 && i != 12) || leadSize != 1){
					serveCard(cards, i, leadSize);
				}
				//1を1枚で出すのは、Jkrと、2が合計5枚確認できてから
				else if(( leadSize == 1  && (i == 12)) && (served[i] + tmplist[i] +served[15] + tmplist[15])== 5){
					serveCard(cards, i, leadSize);
				}
				//2を1枚で出すのは、Jkrを見てから
				else if(( leadSize == 1 && (i == 13)) && (served[15] == 1 || tmplist[15] == 1)){
					serveCard(cards, i, leadSize);
				}
				break;
			}
			} else { ++i; }
			if ( (leadSize > 0) && cards.size() == leadSize ) {
				break;
			}
		}
		break;
	case 2: // 強さ11以下はペアを崩さずに出す
		for (int i = myStrength; i < 15; ) {
			if (tmplist[i] > leadSize && i < 12) {
				i++;
			} else if (tmplist[i] >= leadSize) {
				/* 元のプログラム */
				//1や2の1枚出しでなければ、普通に出す
				if((i != 13 && i != 12) || leadSize != 1){
					serveCard(cards, i, leadSize);
				}
				//1を1枚で出すのは、Jkrと、2が合計5枚確認できてから
				else if(( leadSize == 1  && (i == 12)) && (served[i] + tmplist[i] + served[15] + tmplist[15]) == 5){
					serveCard(cards, i, leadSize);
				}
				//2を1枚で出すのは、Jkrを見てから
				else if(( leadSize == 1 && (i == 13)) && (served[15] == 1 || tmplist[15] == 1)){
					serveCard(cards, i, leadSize);
				}
				break;
				
				/* 改良に失敗したプログラム(ペアを出し惜しみする->弱くなる) */
				/* 				 	bool cont2 = true;
				// 前半はなるべくペアを出さない
				if(remainCount() > 25){
					// ペアしかなければこのループでは何もしない
					for(int j = 1; j < 14; j++){
						// カードを出すのは今読んでるカードと同じかそれより強いもの
						if(i <= j){
							// 1や2でなくてかつ、ペア出ないカードを出す
							if(tmplist[j] == 1 && (j != 13 && j != 12)){
								serveCard(cards,j,1);
								cont2 = false;
								break;	//このbreakではfor(int j = 1; j < 14; j++)のループを抜ける
							}
							//1を1枚で出すのは、Jkrと、2が合計5枚確認できてから
							else if(( leadSize == 1  && (j == 12)) && (served[j] + tmplist[j] +served[15] + tmplist[15]) == 5){
								serveCard(cards, j, leadSize);
								cont2 = false;
								break;
							}
							//2を1枚で出すのは、Jkrを見てから
							else if(( leadSize == 1 && (j == 13)) && (served[15] == 1 || tmplist[15] == 1)){
								serveCard(cards, j, leadSize);
								cont2 = false;
								break;
							}
						}
					}
					// 前半でペアしかなかった場合
					if(cont2){
						//普通に出す
						serveCard(cards, i, leadSize);
					}
					break; // for (int i = myStrength; i < 15; )  を抜ける
				}
				// 後半
				else{
					//1や2の1枚出しでなければ、普通に出す
					if((i != 13 && i != 12) || leadSize != 1){
						serveCard(cards, i, leadSize);
					}
					//1を1枚で出すのは、Jkrと、2が合計5枚確認できてから
					else if(( leadSize == 1  && (i == 12)) && (served[i] + tmplist[i] +served[15] + tmplist[15]) == 5){
						serveCard(cards, i, leadSize);
					}
					//2を1枚で出すのは、Jkrを見てから
					else if(( leadSize == 1 && (i == 13)) && (served[15] == 1 || tmplist[15] == 1)){
						serveCard(cards, i, leadSize);
					}
					break; // for (int i = myStrength; i < 15; )  を抜ける
				} */
			} else {
				i++;
			}
		}
		break;
	case 3: // Jkrをワイルドカードとして出す
		for (int i = myStrength; i < 16;) {
			if (tmplist[i] >= leadSize) {
				serveCard(cards, i, leadSize);
				break;
			} 
			else if (tmplist[i] == leadSize - 1 && tmplist[15]) {
				serveCard(cards, i, leadSize - 1);
				serveCard(cards, 15, 1);
				break;
			}  
			//1や2の1枚出しでなければ、普通に出す
			else if((i != 13 && i != 12) || leadSize != 1){
					serveCard(cards, i, leadSize);
				}
			//1を1枚で出すのは、Jkrと、2が合計5枚確認できてから
			else if(( leadSize == 1  && (i == 12)) && (served[i] + tmplist[i] + served[15] + tmplist[15]) == 5){
				serveCard(cards, i, leadSize);
			}
				//2を1枚で出すのは、Jkrを見てから
			else if(( leadSize == 1 && (i == 13)) && (served[15] == 1 || tmplist[15] == 1)){
				serveCard(cards, i, leadSize);
			} 
			else {
				i++;
			}
		}
		break;
	case 4: // 実質Jkrを出す(つまり絶対勝てる1枚)

		strongestStrength = 0; strongestCount = 0;
		strongestOt(strongestStrength, strongestCount);
		for (int i = strongestStrength; i < 16; i++) {
			if (tmplist[i]) {
				//std::cout<< "zissituserve" << std::endl;
				serveCard(cards, i, 1);
				return;
			}
		}
		break;
	case 5: // 自分が親の際に相手より枚数が多いカードをだす
			if (tmplist[myMax]) {
				//std::cout<< "zissituserve" << std::endl;
				serveCard(cards, myMax,myMaxNum );
				return;
			}
		
		break;
	case 6: // 相手より強いペアを出す
			if (tmplist[strongestStrengthMy]) {
				//std::cout<< "zissituserve" << std::endl;
				serveCard(cards, strongestStrengthMy, strongestCountMy);
				return;
			}
		
		break;
	default:
		break;
	}
}

/* 手札情報配列を構築する関数 */
void Group08::makeHandInfo() {
	/* 手札情報配列の初期化 */
	for (int i = 0; i < 16; i++) {
		tmplist[i] = 0;
	}
	/* 強さ別で枚数を保持 */
	for (int i = 0; i < hand.size(); i++) {
		tmplist[strength(hand.at(i).rank())] ++;
	}
}

/* 自分が所持しているカードで最も強いカードの強さと枚数 */
void Group08::strongestMy(int & strongestStrengthMy, int & strongestCountMy) {
	for (int i = 15; i > 0 ; i--) {
		if (tmplist[i] > 0) {
			strongestStrengthMy = i;
			strongestCountMy = tmplist[i];
			break;
		}
	}
}

/* 他人が所持しているカードで最も強いカードの強さと枚数 */
void Group08::strongestOt(int & strongestStrength, int & strongestCount){
	for (int i = 15; i > 0 ; i--) {
		if (remain[i] > 0) {
			strongestStrength = i;
			strongestCount = remain[i];
			break;
		}
	}
}

/* 他人が所持しているカードで最も弱いカードの強さと枚数 */
void Group08::weakest(int & weakestStrength, int & weakestCount) {
	for (int i = 0; i < 16 ; i++) {
		if (remain[i] > 0) {
			weakestStrength = i;
			weakestCount = remain[i];
			break;
		}
	}
}

/* strengthからrankへ変換 */
int  Group08::strengthTOrank(int strength) {
	switch (strength)
	{
	case 0:
	case 15:
		return strength;
	case 12:
		return 1;
	case 13:
		return 2;
	default:
		return strength + 2;
	}
}

/* 自分の手札の中で最も多いペア数で一番弱いもの */
void Group08::myMaxCard(int & strength, int & count, int start, int end) {
	int maxCount = 0;
	for (int i = start; i < end + 1; i++) {
		if (tmplist[i] > maxCount) {
			strength = i;
			maxCount = tmplist[i];
		}
	}
	count = maxCount;
}

/* 評価関数 */
double Group08::canFlush() {
	return 0;
}

/* 自分の手札のカードの種類の総数 */
int Group08::myCardKind() {
	int count = 0;
	for (int i = 1; i < 14; i++) {
		if (tmplist[i]) { count++; }
	}
	return count;
}

/* 他人が持っている合計のこり枚数 */
int Group08::remainCount() {
	int count = 0;
	for (int i = 1; i < 16; i++) {
		count += remain[i];
	}
	return count;
}
