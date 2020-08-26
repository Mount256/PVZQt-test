#ifndef SHOVEL_H
#define SHOVEL_H
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QApplication>

class Shovel : public QGraphicsItem
{
public:
    Shovel();
    ~Shovel();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    static bool isMovePlant;
};

#endif // SHOVEL_H
