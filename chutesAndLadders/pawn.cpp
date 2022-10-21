#include "pawn.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

Pawn::Pawn(QColor color)
{
    curr_tile_ = nullptr;
    width_ = 30;
    color_ = color;

}

QRectF Pawn::boundingRect() const
{
    return QRectF(curr_tile_->get_x(), curr_tile_->get_y(), width_, width_);
}

QPainterPath Pawn::shape() const
{
    QPainterPath path;
    path.addEllipse(curr_tile_->get_x(), curr_tile_->get_y(), width_, width_);
    return path;
}

void Pawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawEllipse(QRect(curr_tile_->get_x()+12.5, curr_tile_->get_y()+12.5, width_, width_));
    painter->setBrush(b);
}

