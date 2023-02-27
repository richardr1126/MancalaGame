#include "board.h"

/**
  Board constructor, sets up board with pits and stores
*/
Board::Board() {
    pits_ = {};

    int store_height = 250;
    int pit_width = 90;
    int x = 70-pit_width/2;
    int y = 196-store_height/2;

    store2 = new Store(x, y, -2, QColor(0,150,255));
    addItem(store2);

    int x_adj = x;
    int y_adj = y+(store_height)-pit_width;

    for (int i = 0; i < 6; i++) {
        x_adj += pit_width+10;
        Pit* p = nullptr;
        if (i == 4) {
            p = new Pit(x_adj, y_adj, i+1, QColor(255, 80, 80));
            p->SetIsSpecial(true);
        } else {
            p = new Pit(x_adj, y_adj, i+1, QColor(0,255,60));
        }
        pits_.push_back(p);
        player1_pits_.push_back(p);
        addItem(p);
    }
    x_adj += pit_width+10;
    store1 = new Store(x_adj, y, -1, QColor(0,255,60));
    pits_.push_back(store1);
    addItem(store1);

    y_adj = y;

    for (int i = 6; i < 12; i++) {
        x_adj -= pit_width+10;
        Pit* p = nullptr;
        if (i == 10) {
            p = new Pit(x_adj, y_adj, i+1, QColor(255, 80, 80));
            p->SetIsSpecial(true);
        } else {
            p = new Pit(x_adj, y_adj, i+1, QColor(0,150,255));
        }
        pits_.push_back(p);
        addItem(p);
    }
    pits_.push_back(store2);

    for (int i = 12; i >= 7; i--) {
        player2_pits_.push_back(pits_[i]);
    }
}
