#ifndef TILE_H
#define TILE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsItem>

class Tile : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Tile(int x, int y);
    int get_x() {return x_;};
    int get_y() {return y_;};
    int get_width() {return width_;};
    int get_tile_num() {return tile_num_;};
    void SetTileNum(int tile_num) {tile_num_ = tile_num;};
    bool get_has_shortcut() {return has_shortcut_;};
    void SetHasShortcut(bool b) {has_shortcut_=b;};
    int get_shortcut_num() {return shortcut_num_;};
    void SetShortcutNum(int tile_num) {shortcut_num_ = tile_num;};

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;


    friend bool operator==(const Tile &first, const Tile &other);

private:
    int x_;
    int y_;
    int tile_num_;
    bool has_shortcut_;
    int shortcut_num_;
    int width_;

signals:

};

#endif // TILE_H
