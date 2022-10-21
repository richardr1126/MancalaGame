#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QObject>
#include "tile.h"

class Board : public QGraphicsScene
{
    Q_OBJECT

public:
    Board();
    Tile* at(int x, int y) {return arr_graph_[9-y][x];};
    void SetTileAt(int x, int y, Tile* tile) {arr_graph_[9-y][x] = tile;};
    void MakeVector();
    std::vector<Tile*> get_tiles() {return tiles_;};

private:
    Tile* arr_graph_[10][10];
    std::vector<Tile*> tiles_;
};

#endif // BOARD_H
