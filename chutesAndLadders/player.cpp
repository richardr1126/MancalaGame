#include <QTime>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include "player.h"


Player::Player(string username) {
    username_ = username;
    num_rerolls_ = 5;
    num_undos_ = 3;

    int r = QRandomGenerator::global()->generate() % 256;
    int g = QRandomGenerator::global()->generate() % 256;
    int b = QRandomGenerator::global()->generate() % 256;

    QColor c(r, g, b);
    color_ = c;

    pawn_ = new Pawn(color_);
    on_board_ = false;

}

void Player::UndoMove() {
    num_undos_--;
}

int Player::RollDice() {
    int die1 = (QRandomGenerator::global()->generate() % 6) + 1;
    int die2 = (QRandomGenerator::global()->generate() % 6) + 1;
    return die1 + die2;
}

int Player::RerollDice() {
    num_rerolls_--;
    int die1 = (QRandomGenerator::global()->generate() % 6) + 1;
    int die2 = (QRandomGenerator::global()->generate() % 6) + 1;
    return die1 + die2;
}

bool operator==(const Player &first, const Player &other) {
  return first.username_ == other.username_ && first.color_ == other.color_;
}

