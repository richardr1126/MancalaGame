#include "pit.h"
#include "marble.h"

/**
  Adds a marble to this pit

  @param marble The marble you want to add to this pit
*/
void Pit::AddMarble(Marble *marble) {
    marbles_.push_back(marble);
    marble->SetPit(this);
}

/**
  Clears marbles from the pits marble vector
*/
void Pit::ClearMarbles() {
    marbles_.clear();
}

QRectF Pit::boundingRect() const {
    return QRectF(x_, y_, width_, width_);
}

QPainterPath Pit::shape() const {
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

void Pit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(x_, y_, width_, width_));
    painter->setBrush(b);
}

void Pit::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit PitSelected(this);
}

bool operator==(const Pit &first, const Pit &other) {
  return first.x_ == other.x_ && first.y_ == other.y_;
}

QRectF Store::boundingRect() const {
    return QRectF(get_x(), get_y(), get_width(), height_);
}

QPainterPath Store::shape() const {
    QPainterPath path;
    path.addRect(get_x(), get_y(), get_width(), height_);
    return path;
}

void Store::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(get_color()));

    painter->drawRect(get_x(), get_y(), get_width(), height_);
    painter->setBrush(b);
}
