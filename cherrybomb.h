#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H
#include "plant.h"
#include "zombie.h"
#include "map.h"

class Cherrybomb : public Plant
{
public:
    Cherrybomb(QPointF point);
    ~Cherrybomb();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;

private:
    int prepareTime, counter;
    bool atkStatus;
};

#endif // CHERRYBOMB_H
