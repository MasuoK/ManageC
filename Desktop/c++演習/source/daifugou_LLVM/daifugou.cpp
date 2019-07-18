#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>

#include "card.h"
#include "cardset.h"
#include "dealer.h"

#include "player.h"
#include "group08.h"
#include "simpleplayer.h"

#include "think_ta1.h"

/*
#include "gen2017/Group3.h"
#include "gen2017/Group4.h"

#include "gen2018/Group1.h"
#include "gen2018/Group2.h"
#include "gen2018/Group3.h"
#include "gen2018/Group4.h"
#include "gen2018/Group5.h"
#include "gen2018/Group6.h"
#include "gen2018/Group7.h"
#include "gen2018/Group8.h"
#include "gen2018/Group9.h"
*/

std::vector<Player *> players;
enum PROMPTLEVEL {
	BYACCEPT = 0,
	BYFLASH,
	BYGAME,
	NONE,
};

bool rankComp(std::pair<std::string,float> a, std::pair<std::string,float> b) {
	return (a.second < b.second);
}

void registerPlayers(Dealer & d) {
	players.clear();
	players.push_back(new ThinkTA1("TA"));
	players.push_back(new Group08("Group08"));
	players.push_back(new SimplePlayer("Sim 1"));
	players.push_back(new SimplePlayer("Sim 2"));
	players.push_back(new SimplePlayer("Sim 3"));
//	players.push_back(new gen2018::Group7("Group2018-7"));


  	int pid[] = {
	  0, 1, 2, 3, 4,
  	};
  	for(unsigned int i = 0; i < sizeof(pid)/sizeof(int) && i < players.size(); ++i) {
  		d.regist(players[i]);
  	}
}

void play1Game(Dealer & dealer, int & prompt) {
	CardSet opened;
	std::string tmpstr;
	int turnCount = 0;

	dealer.deal();

	while (true) {
		if ( turnCount == 0 ||
				(dealer.playerPassed() && dealer.playerInTurnIsLeader()) ) {
			dealer.flush();

			std::cout << std::endl << "flushed. " << std::endl;
			std::cout << "  -------- " << std::endl;
			dealer.show();
			std::cout << "  -------- " << std::endl;
		}
		if ( prompt <= PROMPTLEVEL::BYFLASH &&
				(turnCount == 0 || (dealer.playerPassed() && dealer.playerInTurnIsLeader()) ) )  {
			std::getline(std::cin, tmpstr);
			int t = std::atoi(tmpstr.c_str());
			if ( t != 0 )
			  prompt = ( t > 3 ? 3 : t);
		}
		std::cout << dealer.playerInTurn().playerName() << "'s turn: ";
		GameStatus state = dealer.gameStatus();
		opened.clear();

		if ( !dealer.checkPlayerInTurn() ) {
			std::cout << dealer.playerInTurn().playerName() << "がいかさましてます ikasama found." << std::endl;
		}
		dealer.playerInTurn().follow(state, opened);
		if ( opened.size() != 0 )
			std::cout << opened;
		if ( dealer.discardPile().size() == 0 && opened.size() == 0 && dealer.playerInTurnIsLeader() ) {
			// リーダーがパスした．．．
			std::cout << "leader passed." << std::endl;
			dealer.reject(opened);
			std::cout << dealer.playerInTurn().playerName() << " resigned. " << std::endl << std::endl;
			dealer.resignPlayerInTurn();
		} else {
			if ( dealer.acceptCheck(opened) ) {
				dealer.accept(opened);
				dealer.updateSignInTurn();
				std::cout << "accepted." << std::endl;
			} else {
				if ( !opened.isEmpty() )
					std::cout << "rejected, ";
				std::cout << "pass." << std::endl;
				dealer.reject(opened);
			}
			if ( !dealer.playerPassed() ) {
				dealer.setAsLeader();
				std::cout << "--- Lead by " << dealer.currentLeader().playerName() << ", "
						<< dealer.discardPile() << std::endl;
				if ( prompt <= PROMPTLEVEL::BYACCEPT )
					std::getline(std::cin, tmpstr);
			}
			std::cout <<  std::endl;

			dealer.showDiscardedToPlayers();

			if ( dealer.playerInTurn().isEmptyHanded() ) {
				// あがり
				std::cout << dealer.playerInTurn().playerName() << " finished. " << std::endl << std::endl;
				dealer.finishPlayerInTurn();

			} else {
				dealer.nextPlayer();
			}
		}
		if ( dealer.howManyPlayingPlayers() <= 1 ) {
			// どべ確定
			dealer.finishPlayerInTurn();
			std::cout << "  -------- " << std::endl;
			dealer.show();
			std::cout << "  -------- " << std::endl;
			break;
		}
		turnCount++;
	}
	return;
}

void commandargs(const int argc, char * const argv[],
		int & games, int & sets, int & prompt);

int main (int argc, char * const argv[]) {
	
	Dealer dealer;
	std::map<std::string,unsigned long> pointTable;
	std::string resp, tmpstr;
	int games = 5, sets = 1;
	int prompt = PROMPTLEVEL::BYACCEPT;

	commandargs(argc, argv, games, sets, prompt);
	std::cout << "games = " << games << " sets = " << sets << " prompt = " << prompt << std::endl;

	std::cout << "Registering players." << std::endl;

	registerPlayers(dealer);

	for (int gamecount = 0; gamecount < games * sets; ++gamecount) {
		std::cout << std::endl << "Game " << (gamecount + 1) << "." << std::endl;

		if ( !(gamecount % sets) ) {
			// shuffle the order per set
			std::cout << "Suffling the order of players..." << std::endl;
			dealer.shuffleOrder();
		}

		play1Game(dealer, prompt);

		std::cout << std::endl << "This game's result: " << std::endl;
		for (unsigned int i = 0; i < dealer.howManyParticipants() ; i++) {
			float rankpoint = 1;
			if ( i > 0 ) {
				if ( i < dealer.howManyParticipants() - 1 ) {
					rankpoint = i + 2;
				} else {
					rankpoint = i + 3;
				}
			}
			pointTable[dealer.finishedAt(i)] += rankpoint;
			//
			std::cout << i+1 << ": " << std::setw(10) << dealer.finishedAt(i) << "\t" << '+' << rankpoint << " " << std::endl;
		}
		if ( prompt <= PROMPTLEVEL::BYGAME ) {
			std::getline(std::cin, tmpstr);
			int t = std::atoi(tmpstr.c_str());
			if ( t != 0 )
			  prompt = ( t > 3 ? 3 : t);
		}

		dealer.reOrder();
	}

	std::vector<std::pair<std::string,float>> list(pointTable.begin(),pointTable.end());
	std::sort(list.begin(), list.end(), rankComp);
	std::cout << std::endl << "Final result: " << std::endl;
	for(std::vector<std::pair<std::string,float>>::iterator itr = list.begin();
			itr != list.end(); ++itr) {
		std::cout << std::setw(4) << itr->second << "\t: " << itr->first << std::endl;
	}
	std::cout << std::endl;

    return 0;
}


void commandargs(const int argc, char * const argv[],
		int & games, int & sets, int & prompt) {

	int tval;
	int i = 1;
	while ( i < argc) {
		if ( std::string("-p") == argv[i] ) {
			++i;
			tval = std::atoi(argv[i]);
			if ( tval != 0 )
				prompt = (tval > NONE ? NONE : tval);
		} else if ( std::string("-g") == argv[i] ) {
			++i;
			tval = std::atoi(argv[i]);
			if ( tval != 0 )
				games = tval;
		} else if ( std::string("-s") == argv[i] ) {
			++i;
			tval = std::atoi(argv[i]);
			if ( tval != 0 )
				sets = tval;
		}
		++i;
	}

}
