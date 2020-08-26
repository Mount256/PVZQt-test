#ifndef SUN_H
#define SUN_H

#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QPointF>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QTime>
#include "cards.h"

class Sun : public QGraphicsItem
{
public:
    Sun();
    Sun(QPointF point);
    ~Sun();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int type() const;

private:
    QMovie *movie;
    int counter, existTime;
    int posX, posY;
    bool isFlower;
};

#endif // SUN_H
