//
// card.cpp - トランプカード型(C++版)
//  作者: (あなたの名前); 日付: (完成した日付)
//

#include <iostream>
#include <stdlib.h>

#include "card.h"

// クラス変数（定数）の初期化
//const char *Card::suitnames[] = { "Blank", "Spade", "Diamond", "Heart", "Club", "Joker", };
const char *Card::suitnames[] = { "_", "S", "D", "H", "C", "Jkr", };
const char *Card::ranknames[] = {
    "?", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "Jkr", "_",
};

//
// Card::isValid() - まともなカードか？
//
bool Card::isValid(void) const {
    if (((SUIT_SPADE <= suitval) && (suitval <= SUIT_CLUB))
         && (1 <= rankval && (rankval <= 13)) )
        return true;
    else if (suitval == SUIT_JOKER)
        return true;
    return false;
}

//
// Card::readFrom() - 文字列から値を得る (戻り値：残りの文字列)
//
const char *Card::readFrom(const char *str) {
    char *ptr;
    int s;

    suitval = SUIT_BLANK;
    rankval = 0;

  // 4組のいずれ？
  for (s = SUIT_SPADE; s <= SUIT_CLUB; s++) {
      if (tolower(*str) == tolower(Card::suitnames[s][0])) { // 一文字目だけで判定
          suitval = s;
          do { ++str; } while (isalpha(*str));
          break;
      }
  }
  if (SUIT_SPADE <= s && s <= SUIT_CLUB) {
      // なら番号も得る
      while (isspace(*str)) { ++str; }
      rankval = strtod(str, &ptr);
      if (0 < rankval && rankval <= 13) {
          return ptr;
      } else {
          if (rankval == 0) {
              switch (tolower(*str)) {
              case 'a':
              case 'A':
                  rankval = 1;
                  break;
              case 'j':
              case 'J':
                  rankval = 11;
                  break;
              case 'q':
              case 'Q':
                  rankval = 12;
                  break;
              case 'k':
              case 'K':
                  rankval = 13;
                  break;
              }
          }
          return str;
      }
  } else if (tolower(*str) == 'j') {
    suitval = SUIT_JOKER;
    rankval = RANK_JOKER; // joker は number を 15 としておく．
    do { ++str; } while (isalpha(*str));
    return str;
  }
  return str;
}

//
// Card::readFrom() - ストリームから値を得る
//
std::istream & Card::readFrom(std::istream & in) {
    std::string buf;
    std::getline(in, buf);
    readFrom(buf.c_str());
    return in;
}

//
// Card::printOn() - ファイルストリームに出力する
// 第二引数に false を与えると，カードを伏せて表示
//
std::ostream & Card::printOn(std::ostream& ostr, const bool faceup) const {
    ostr << '[';
    if (faceup) {
        ostr << suitnames[(int)suitval];
        if (suitval != SUIT_JOKER)
            ostr << " " << ranknames[rankval];
    } else {
        ostr << "###";
    }
    ostr << ']';
    return ostr;
}
