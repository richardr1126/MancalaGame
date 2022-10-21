#ifndef PIT_H
#define PIT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QtWidgets>

using namespace std;

class Marble;

class Pit : public QGraphicsObject
{
    Q_OBJECT
public:
    Pit(const int x, const int y, const int pit_num, const QColor color):
        x_(x), y_(y), width_(90), pit_num_(pit_num), color_(color) {
        if (pit_num >= 1 && pit_num <= 6) {
            belongs_to_player_ = 1;
        } else if (pit_num >= 6 && pit_num <= 12) {
            belongs_to_player_ = 2;
        }
    };

    int get_x() const {return x_;};
    int get_y() const {return y_;};
    int get_width() const {return width_;};
    int get_pit_num() const {return pit_num_;};
    QColor get_color() const {return color_;};

    int get_player_num() {return belongs_to_player_;};

    bool get_is_special() {return is_special_;};
    void SetIsSpecial(bool special) {is_special_ = special;};

    int get_num_marbles() {return marbles_.size();};
    Marble* get_marble_at(int i) {return marbles_[i];};
    void AddMarble(Marble* marble);
    void ClearMarbles();

    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    friend bool operator==(const Pit &first, const Pit &other);

signals:
    void PitSelected(Pit *p);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    const int x_;
    const int y_;
    const int width_;
    const int pit_num_;
    const QColor color_;
    bool is_special_;
    int belongs_to_player_;

    vector<Marble*> marbles_;

};

class Store : public Pit
{
public:
    Store(int x, int y, int num, QColor color): Pit(x, y, num, color) {
        height_ = 250;
    };
    int get_height() {return height_;};

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    int height_;
};



#endif // PIT_H
