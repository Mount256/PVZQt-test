#ifndef CARD_H
#define CARD_H

#include <QGraphicsItem>
#include <QRect>
#include <QBrush>
#include <QPainter>
#include <QCursor>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>

class Cards : public QGraphicsItem
{
public:
    int No, sunNeed, counter;
    QString name;
    bool isPlanted, StartMode;
    static int sunTotal;
    Cards();
    ~Cards();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

protected:
    int coolTime;
    QString tip;
};

class sunflower : public Cards
{
public:
    sunflower();
};

class peaShooter : public Cards
{
public:
    peaShooter ();
};

class wallnut : public Cards
{
public:
    wallnut ();
};

class cherryBomb : public Cards
{
public:
    cherryBomb ();
};

class repeater : public Cards
{
public:
    repeater();
};

class snowpea : public Cards
{
public:
    snowpea();
};

class potatomine: public Cards
{
public:
    potatomine();
};

#endif // CARD_H
