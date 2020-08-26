#ifndef ZOMBIE_H
#define ZOMBIE_H
#include <QGraphicsItem>
#include <QPainter>
#include <QMovie>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include "plant.h"

class Zombie : public QGraphicsItem
{
public:
    enum { Type = UserType + 2};
    int HP, crHP, ATK, setStatus;
    int speedFactor;
    Zombie();
    ~Zombie();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase);
    bool collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const override;
    int type() const;
    void bodyMovie(QString pic);
    void headMovie(QString pic);

protected:
    int nowStatus, snowCounter;
    qreal speed;
    bool isHead;
    Plant *plant;
    int posX, posY;
    QString name;
    QMovie *movie, *head;

};

#endif // ZOMBIE_H
