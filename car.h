#ifndef CAR_H
#define CAR_H
#include <QGraphicsItem>
#include <QPainter>
#include "zombie.h"
#include <QDebug>

class Car : public QGraphicsItem
{
public:
    Car(int i);
    ~Car();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;

private:
    bool isRun;
    int ATK;
};

#endif // CAR_H
