#include "board.h"
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTime>

Board::Board() {

}

void Board::MakeVector() {
    //row 1
    int tile_num = 0;
    for (int i = 0; i < 10; i++) {
        Tile* t = at(i,0);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
    //row 2
    for (int i = 9; i >= 0; i--) {
        Tile* t = at(i,1);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
    //row 3
    for (int i = 0; i < 10; i++) {
        Tile* t = at(i,2);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
    //row 4
    for (int i = 9; i >= 0; i--) {
        Tile* t = at(i,3);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
    //row 5
    for (int i = 0; i < 10; i++) {
        Tile* t = at(i,4);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
    //row 6
    for (int i = 9; i >= 0; i--) {
        Tile* t = at(i,5);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
    //row 7
    for (int i = 0; i < 10; i++) {
        Tile* t = at(i,6);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
    //row 8
    for (int i = 9; i >= 0; i--) {
        Tile* t = at(i,7);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
    //row 9
    for (int i = 0; i < 10; i++) {
        Tile* t = at(i,8);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
    //row 10
    for (int i = 9; i >= 0; i--) {
        Tile* t = at(i,9);
        t->SetTileNum(tile_num);
        tiles_.push_back(t);
        tile_num++;
    }
}
