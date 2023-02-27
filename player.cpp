#include "player.h"

/**
  Player constructor

  @param name Name for the product
  @param condition The condition of the product
  @param price The base price of the product
*/
Player::Player(int num) {
    score_ = 0;
    player_num_ = num;
    if (num == 1) {
        color_ = QColor(0,255,60);
    } else {
        color_ = QColor(0,150,255);
    }
}

bool operator==(const Player &first, const Player &other) {
  return first.player_num_ == other.player_num_ && first.score_ == other.score_;
}


