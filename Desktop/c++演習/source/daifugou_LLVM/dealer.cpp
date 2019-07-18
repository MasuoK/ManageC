/*
 *  dealer.cpp
 *  PlayingCard
 *
 *  Created by 下薗 真一 on 09/04/12.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <iostream> 
#include <iomanip>
#include <string>
#include <random>
#include <algorithm>

#include <cstdlib>
#include <ctime>

#include "player.h"
#include "dealer.h"

#include "card.h"
#include "cardset.h"
#include "gamestatus.h"


const uint64_t Dealer::cardsetsign(const CardSet & cs) {
	uint64_t sig = 0;
	unsigned int bpos;
	for(int i = 0; i < cs.size(); ++i) {
		if ( cs[i].suit() == Card::SUIT_BLANK ) {
			sig |= ((uint64_t)1 << 63);
		} else if ( cs[i].isJoker() ) {
			sig |= ((uint64_t)1 << 62);
		} else {
			bpos = (cs[i].suit() - Card::SUIT_SPADE)<<4;
			bpos += cs[i].rank() - 1;
			sig |= (uint64_t)1 << bpos;
		}
	}
	return sig;
}

// class methods.

Dealer::Dealer() {
	finishedOrder.clear();
	resignedOrder.clear();
	turnIndex = 0;
	turnPassed = false;
	numParticipants = 0;
	leaderIndex = 0;
	// set rules
	noMillionaire = true;
	noMiyakoOchi = true;
	//
	stats.clear();

	std::random_device randev;
	mtrand = std::mt19937(randev());

	return;
}

Dealer::~Dealer(void) {
	for(unsigned int i = 0; i < numParticipants; i++) {
		delete(participant[i]);
	}
}


Player & Dealer::player(const int ith) const {
	return * participant[ith];
}


Player & Dealer::player(const std::string & name) {
	for(unsigned int i = 0; i < numParticipants; ++i) {
		if ( participant[i]->playerName() == name )
			return *participant[i];
	}
	return *participant[numParticipants];
}
/*
Player * Dealer::player(const int id) {
	for(unsigned int i = 0; i < numParticipants; ++i) {
		if ( participant[i].entryID == id )
			return participant[i].player;
	}
	return NULL;
}
*/
// the number of playing, not finished, players
unsigned int Dealer::howManyPlayingPlayers() const {
	unsigned int count = 0;
	for(unsigned int i = 0; i < numParticipants; ++i) {
		if ( !participant[i]->isEmptyHanded() )
			count++;
	}
	return count;
}


bool Dealer::checkRankUniqueness(const CardSet & cs) {
	int rank = 0;

	if (cs.size() == 0)
		return false;

	if ( cs.size() == 1 && cs.at(0).isJoker() )
		return true;

	for (int i = 0; i < cs.size(); i++) {
	  if (cs.at(i).isJoker() )
		  continue;  // Jkrをスキップ
	  if ( rank == 0 ) {
		  rank = cs.at(i).rank();
	  } else if ( rank != cs.at(i).rank() ) {
	    return false;
	  }
	}
	return true;
}


// instance methods.
bool Dealer::regist(Player * pl) {
	if ( !(numParticipants < NUM_OF_MAX_PLAYERS) ) {
		std::cerr << "Error: tried player registration exceeding the limit." << std::endl;
		return false;
	}
	participant[numParticipants] = pl;

	stats[pl] = 0.0;
	numParticipants++;
	return true;
}

const Player & Dealer::currentLeader() const {
	return * participant[leaderIndex];
}

bool Dealer::playerInTurnIsLeader() const {
	return leaderIndex == turnIndex;
}

/*
void Dealer::newGame() {
	for (unsigned int i = 0; i < numParticipants; i++) {
		participant[i]->clearHand();
		participant[i]->ready();
	}
}
*/

void Dealer::shuffleOrder(void) {
	unsigned int dst;
	Player * t;

	for(int i = 0; i < 7; i++) {
		for (unsigned int src = 0; src < numParticipants; ++src) {
			dst = mtrand() % numParticipants;
			if ( src == dst ) continue;
			t = participant[src];
			participant[src] = participant[dst];
			participant[dst] = t;
		}
	}
	return;
}

void Dealer::reOrder(void) {
	Player * newplayorder[NUM_OF_MAX_PLAYERS];
	if ( finishedOrder.size() + resignedOrder.size() != numParticipants ) {
		shuffleOrder();
		return;
	}
	for(unsigned int i = 0; i < finishedOrder.size(); ++i) {
		newplayorder[i] = participant[finishedOrder[i]];
	}
	for(unsigned int i = 0; i < resignedOrder.size(); ++i) {
		newplayorder[numParticipants - i - 1] = participant[resignedOrder[i]];
	}
	for(unsigned int i = 0; i < numParticipants; ++i)
		participant[i] = newplayorder[numParticipants - 1 - i]; // どべから順に
	return;
}

void Dealer::setAsLeader(void) {
	leaderIndex = turnIndex;
}

bool Dealer::deal(void) {
	Card top;

	for (unsigned int i = 0; i < numParticipants ; i++) {
		player(i).clearHand();
	}
	theDeck.setupDeck();
	theDeck.shuffle();
	int index = 0;
	while ( !theDeck.isEmpty() ) {
		theDeck.draw(top, 0);
		player(index).takeCards(top);
		index = (index + 1) % numParticipants;
	}

	for(unsigned int i = 0; i < numParticipants; i++) {
		updateSign(i);
		player(i).ready();
	}

	discarded.clear();
	turnIndex = 0;
	leaderIndex = 0;
	turnPassed = false;
	finishedOrder.clear();
	resignedOrder.clear();
	cardbin.clear();

	return true;
}

void Dealer::flush() {
	discarded.clear();
}

const CardSet & Dealer::discardPile() const {
	return discarded;
}

const bool Dealer::acceptCheck(const CardSet & opened) const {
	int openedRank, discardedRank;

	if (opened.isEmpty() )
		return false;  // regard the empty open set as "pass"

	if (!checkRankUniqueness(opened))
		return false;
	if ( opened.size() >= 5 )
		return false;

	if ( discarded.isEmpty() )
		return true;

	if ( discarded.size() != opened.size() )  // the number of cards must be match. no five cards w/ Jkr allowed.
	  return false;
	
	openedRank = getCardStrength(opened);
	discardedRank = getCardStrength(discarded);

	if ( openedRank > discardedRank )
	    return true;
	return false;
}

void Dealer::updateSign(const int i) {
	cardscode[i] = cardsetsign(player(i).inHand());
}

bool Dealer::checkPlayerInTurn(void) const {
	return cardscode[turnIndex] == cardsetsign(player(turnIndex).inHand());
}

void Dealer::accept(CardSet & opened) {
	// passed all the checks.
	discarded.clear();
	discarded.insert(opened);
	cardbin.insert(opened);
	turnPassed = false;
}

void Dealer::reject(CardSet & opened) {
	if ( !opened.isEmpty() )
		playerInTurn().takeCards(opened);
	turnPassed = true;
	// leave as untouched the shadow set
}

int Dealer::getCardStrength(const CardSet & cs) {
	int i;
	if ( cs.isEmpty() )
		return 0;

	if ( cs.size() == 1 && cs.at(0).isJoker() ) {
		return 53;
	}
  	for (i = 0; i < cs.size(); i++) {
	  if (!cs.at(i).isJoker()) {
		  break;
	  }
	}
  	if ( cs.at(i).rank() < 3 )
  		return cs.at(i).rank() + 13;
	return cs.at(i).rank();
}

void Dealer::showDiscardedToPlayers() {
	GameStatus gstat = gameStatus();
	if ( turnPassed )
		gstat.pile.clear();
	for (unsigned int i = 1; i < numParticipants; i++) {
		if ( participant[ (turnIndex + i) % numParticipants ]->size() > 0 )
			participant[ (turnIndex + i) % numParticipants ]->approve(gstat);
	}
	return;
}

Player & Dealer::finishPlayerInTurn() {
	Player & p = playerInTurn();
	const unsigned int finishedIndex = turnIndex;
	// finished leader leaves the game,
	// thus the next player is considered as temporarily the leader

	cardbin.insert(participant[finishedIndex]->inHand());
	participant[finishedIndex]->clearHand(); // ensure that leaving player holding no cards
	finishedOrder.push_back(finishedIndex);
	if ( howManyPlayingPlayers() > 0 ) {
		nextPlayer();
		setAsLeader();
	}

	return p;
}

Player & Dealer::resignPlayerInTurn() {
	Player & p = playerInTurn();
	const unsigned int finishedIndex = turnIndex;
	// finished leader leaves the game,
	// thus the next player is considered as temporarily the leader

	cardbin.insert(participant[finishedIndex]->inHand());
	participant[finishedIndex]->clearHand(); // ensure that leaving player holding no cards
	resignedOrder.push_back(finishedIndex);
	if ( howManyPlayingPlayers() > 0 ) {
		nextPlayer();
		setAsLeader();
	}

	return p;
}

unsigned int Dealer::howManyFinishedPlayers() const {
	return finishedOrder.size() + resignedOrder.size();
}

Player & Dealer::playerInTurn(void) {
	return *participant[turnIndex];
}

Player & Dealer::nextPlayer() {
//	std::cout << "searching for the next player..." << std::endl;
	do {
		turnIndex = (turnIndex+1) % numParticipants;
	} while ( playerInTurn().size() == 0);
	return playerInTurn();
}

const std::string & Dealer::finishedAt(unsigned int place) const {
	std::vector<int> resignedReversed;
	if ( place < finishedOrder.size() ) {
		return participant[finishedOrder[place]]->playerName();
	} else {
		resignedReversed.resize(resignedOrder.size());
		std::reverse_copy(resignedOrder.begin(), resignedOrder.end(), resignedReversed.begin() );
		return participant[resignedReversed[place - finishedOrder.size()]]->playerName();
		// return participant[resignedOrder[ resignedOrder.size() - 1 - (place - finishedOrder.size() ) ]]->playerName();
	}
}

void Dealer::show() {
	for (unsigned int i = 0; i < numParticipants ; i++) {
		if ( i == (unsigned int) leaderIndex )
			std::cout << "* ";
		else std::cout << "  ";
		std::cout << std::left << std::setw(8) << participant[i]->playerName()
				<< " " << participant[i]->inHand() << std::endl;
	}
}


GameStatus Dealer::gameStatus(void) const {
	GameStatus gstat;
	gstat.pile = discarded;
	gstat.turnIndex = turnIndex;
	gstat.leaderIndex = leaderIndex;
	gstat.numPlayers = howManyPlayingPlayers();
	for (int i = 0; i < gstat.numPlayers; i++)
		gstat.playerName[i] = participant[i]->playerName();
	for (int i = 0; i < gstat.numPlayers; i++) {
		gstat.numCards[i] = player(i).size();
		gstat.playingOn[i] = (player(i).size() != 0);
	}
	gstat.numCards[gstat.numPlayers] = GameStatus::NO_MORE_PLAYERS; // for backward compatibility
	return gstat;
}
