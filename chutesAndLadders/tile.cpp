#include "pawn.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include "tile.h"

Tile::Tile(int x, int y)
{
    x_ = x;
    y_ = y;
    width_ = 50;
    tile_num_ = 999;
    shortcut_num_ = -999;
}

QRectF Tile::boundingRect() const {
    return QRectF(x_, y_, width_, width_);
}

QPainterPath Tile::shape() const {
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(QColor(40,40,40)));

    painter->drawRect(QRect(x_, y_, width_, width_));
    painter->setBrush(b);
}

bool operator==(const Tile &first, const Tile &other) {
  return first.x_ == other.x_ && first.y_ == other.y_;
}
