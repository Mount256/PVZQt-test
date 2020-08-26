#ifndef POTATOMINE_H
#define POTATOMINE_H
#include "plant.h"
#include "zombie.h"
#include "map.h"

class PotatoMine : public Plant
{
public:
    PotatoMine(QPointF point);
    ~PotatoMine();
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;

private:
    int counter, coolTime;
    int atkStatus;
};

#endif // POTATOMINE_H
