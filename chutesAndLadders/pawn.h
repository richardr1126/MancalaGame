#ifndef PAWN_H
#define PAWN_H

#include <QMainWindow>
#include <QObject>
#include <QGraphicsItem>
#include "tile.h"

class Pawn : public QGraphicsObject
{
    Q_OBJECT

public:
    Pawn(QColor color);
    Tile* get_curr_tile() {return curr_tile_;};
    void SetTile(Tile* tile) {curr_tile_ = tile;};
    int get_width() {return width_;};

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    friend bool operator==(const Tile &first, const Tile &other);

private:
    Tile* curr_tile_;
    int width_;
    QColor color_;
};

#endif // PAWN_H
