#include "car.h"

Car::Car(int i)
{
    isRun = 0; ATK = 10000;
    setPos(160, 110+100*i);
    setZValue(7);
}

Car::~Car()
{

}

QRectF Car::boundingRect() const
{
    return QRectF(0, 0, 70, 50);
}

void Car::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QImage image(":/graphics/Screen/car.png");
    painter->drawImage(boundingRect(), image);
   // painter->drawRect(boundingRect());
}

void Car::advance(int phase)
{
    if(!phase)
        return;
     QList <QGraphicsItem *> items = collidingItems();
     if(!items.isEmpty())
     {
         Zombie *zombie = qgraphicsitem_cast<Zombie *>(items[qrand() % items.size()]);
         zombie->HP -= ATK;
         qDebug() << "crash!" << x() << y();
         isRun = 1;
     }
     if(isRun)
         setPos(x()+20, y());
     if(x() >= 1000)
         delete this;
}

bool Car::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type() == Zombie::Type && x()-other->x()>190 && y()-other->y()>40 && y()-other->y()<105;
}
