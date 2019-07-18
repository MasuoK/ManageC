/*
 *  simpleplayer.h
 *  PlayingCard
 *
 *  Created by 下薗 真一 on 09/04/12.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _GROUP08_H_
#define _GROUP08_H_

#include <random>

#include "player.h"
#include "gamestatus.h"

/*
 * すこしルールを覚えたプレイヤーのクラス．
 * Player クラスを基底クラスとする継承クラスの例である
 */
class Group08 : public Player{
	/*
	 * 変更不可の部分は，変更しないので定義せずそのまま引き継ぐ．
	 *
	 * その他の部分も引き継がれるが，follow などプレーヤーの挙動を変える
	 * のに必要な関数は，上書きして再定義する．
	 * 自分で新しく作成するデータ構造や関数も，定義する．
	 */
	int served[16];  // 今まで出された強さごとの枚数
	int remain[16];  // 他人が持っているカードの強さごとの枚数
	int tmplist[16]; // 手札の強さ別枚数の情報
	int oldRank;
	int myStrength;
	int leadRank;	 // リードのランク，pile がカラの場合 0
	int leadSize;	 // リードの組枚数
 //自分が持っているカードで最も強いカードの強さとその枚数
 	int strongestStrengthMy, strongestCountMy; //自分が持っているカードで最も強いカードの強さとその枚数
	int strongestStrength, strongestCount; //相手が持っているカードで最も強いカードの強さとその枚数

	int myMax;	//自分が持ってる中で最も枚数の多かったペアのスート
	int myMaxNum; //自分が持ってる中で最も枚数の多かったペアの枚数

	int otherMax;	//相手が持ってる中で最も枚数の多かったペアのスート
	int otherMaxNum; //相手が持ってる中で最も枚数の多かったペアの枚数
	

public:
	// 拡張した派生クラスでオーバーライドする／できる関数
	Group08(const char * myname = "Group08") : Player(myname) {}
    virtual ~Group08() { }

	virtual void ready(void);
	virtual bool follow(const GameStatus & gstat, CardSet & cards);
	virtual bool approve(const GameStatus & gstat);

	void   makeHistogram(int histo[Card::RANK_JOKER+1]);
	void   makeHandInfo();
	void   serveCard(CardSet & cards, int strong, int count); // ランクがrankのカードをcount枚出す
	void   serveCard(CardSet & cards, int command); // 指定の出し方をする
	void   strongestMy(int & strongestStrengthMy, int & strongestCountMy); 	/* 自分が所持しているカードで最も強いカードの強さと枚数 */
	void   strongestOt(int & strongestStrength, int & strongestCount); // 他人が所持しているカードで最も強いカードの強さと枚数
	void   weakest(int & weakestStrength, int & weakestCount); // 他人が所持しているカードで最も弱いカードの強さと枚数
	int    strengthTOrank(int strength); // strengthからrankへ変換
	void   myMaxCard(int & strength, int & count, int start, int end); // 自分の手札の中で最も多いペア数で一番弱いもの
	double canFlush(); // 評価関数
	int    myCardKind(); // 自分の手札のカードの種類の総数
	int    remainCount(); // 他人が持っている合計のこり枚数

};

#endif
