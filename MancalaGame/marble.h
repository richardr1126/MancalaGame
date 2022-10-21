#ifndef MARBLE_H
#define MARBLE_H

#include <QObject>
#include <QMainWindow>
#include <QObject>
#include <QGraphicsItem>
#include <QtWidgets>
#include "pit.h"

class Marble : public QGraphicsObject
{
    Q_OBJECT

public:
    Marble(Pit* pit, QColor color);
    virtual int get_points_value() {return 1;};
    int get_width() {return width_;};
    Pit* get_pit() {return curr_pit_;};
    int get_x() {return x_;};
    int get_y() {return y_;};
    void SetColor(QColor color) {color_ = color;};
    void SetPit(Pit* pit);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    Pit *curr_pit_;
    int x_;
    int y_;
    int width_;
    QColor color_;
};

class SpecialMarble : public Marble {
public:
    SpecialMarble(Pit *pit, QColor color): Marble(pit, color) {};

    int get_points_value() {return 5;};
};

class MarbleFactory {
public:
  static Marble* GetMarble(Pit* pit, QColor color);
  static SpecialMarble* GetSpecialMarble(Pit *pit, QColor color);
};

#endif // MARBLE_H
