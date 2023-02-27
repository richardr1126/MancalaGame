#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QtWidgets>

class Player {

public:
    Player(int num);

    int get_score() {return score_;};
    void SetScore(int score) {score_ = score;};
    QColor get_color() {return color_;};
    int get_player_num() {return player_num_;};

    friend bool operator==(const Player &first, const Player &other);
private:
    int score_;
    int player_num_;
    QColor color_;


};

#endif // PLAYER_H
