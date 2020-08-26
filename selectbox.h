#ifndef SELECTBOX_H
#define SELECTBOX_H

#include <QGraphicsItem>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "cards.h"

class SelectBox:public QGraphicsItem
{
public:
    SelectBox();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
};

#endif // SELECTBOX_H
