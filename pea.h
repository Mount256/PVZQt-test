#ifndef PEA_H
#define PEA_H
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QPointF>
#include <QDebug>
#include <QTime>
#include "zombie.h"

class Pea : public QGraphicsItem
{
public:
    enum { Type = UserType + 3};
    Pea(QPointF point, bool _isSnow = false);
    ~Pea();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const;
    int type() const;

private:
    int posX, posY;
    int ATK;
     bool isSnow;
};

#endif // PEA_H
