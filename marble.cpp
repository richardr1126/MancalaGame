#include "marble.h"

/**
  Marble constructor, generates random
    offsets so marbles aren't on top of each other

  @param pit The pit to add the marble to
  @param color The color of the marble
*/
Marble::Marble(Pit* pit, QColor color){
    curr_pit_ = pit;
    color_ = color;
    width_ = 20;

    int x_offset = (QRandomGenerator::global()->generate() % 61) - 30;
    int y_offset = (QRandomGenerator::global()->generate() % 61) - 30;

    x_ = curr_pit_->get_x()+35+x_offset;
    y_ = curr_pit_->get_y()+35+y_offset;

}

/**
  Set the marble's pit to a new pit

  @param pit New pit to place the marble in
*/
void Marble::SetPit(Pit *pit) {
    curr_pit_ = pit;
    int x_offset = (QRandomGenerator::global()->generate() % 61) - 30;
    int y_offset = (QRandomGenerator::global()->generate() % 61) - 30;

    x_ = curr_pit_->get_x()+35+x_offset;
    y_ = curr_pit_->get_y()+35+y_offset;
    update();
}

QRectF Marble::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

QPainterPath Marble::shape() const
{
    QPainterPath path;
    path.addEllipse(x_, y_, width_, width_);
    return path;
}

void Marble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawEllipse(QRect(x_, y_, width_, width_));
    painter->setBrush(b);
}

/**
  Marble factory, returns new child Marble objects

  @param pit Pit to place the marble in
  @param color Color for the marble
*/
Marble* MarbleFactory::GetMarble(Pit *pit, QColor color) {
  return new Marble(pit, color);
}
SpecialMarble* MarbleFactory::GetSpecialMarble(Pit *pit, QColor color) {
  return new SpecialMarble(pit, color);
}
