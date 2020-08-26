#ifndef PLANT_H
#define PLANT_H
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>

class Plant : public QGraphicsItem
{
public:
    enum { Type = UserType + 1};
    int HP;
    Plant();
    ~Plant();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    int type() const;

protected:
    int ATK, posX, posY;
    QString name;
    QMovie *movie;

};

#endif // PLANT_H
