#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QObject>
#include <vector>
#include "pit.h"

using namespace std;

class Board : public QGraphicsScene
{
    Q_OBJECT

public:
    Board();
    Pit* get_pit_at(int i) {return pits_[i];};
    Pit* get_player1_pit_at(int i) {return player1_pits_[i];};
    Pit* get_player2_pit_at(int i) {return player2_pits_[i];};
    Store* get_store1() {return store1;};
    Store* get_store2() {return store2;};

private:
    vector<Pit*> pits_;
    vector<Pit*> player1_pits_;
    vector<Pit*> player2_pits_;


    Store* store1;
    Store* store2;
};

#endif // BOARD_H
