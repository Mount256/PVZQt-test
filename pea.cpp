#include "pea.h"

Pea::Pea(QPointF point, bool _isSnow):isSnow(_isSnow)
{
    ATK = 20;
    posX = point.x();
    posY = point.y();
    setPos(posX-180, posY);
    setZValue((posY-100)/90);
}

Pea::~Pea()
{

}

QRectF Pea::boundingRect() const
{
    return QRectF(180, 0, 30, 30);
}

void Pea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(!isSnow)
        painter->drawImage(boundingRect(), QImage(":/graphics/Bullets/PeaNormal/PeaNormal_0.png"));
    else
        painter->drawImage(boundingRect(), QImage(":/graphics/Bullets/PeaIce/PeaIce_0.png"));
   // painter->drawRect(boundingRect());
}

void Pea::advance(int phase)
{
    if(!phase)
        return;
    update();
    QList <QGraphicsItem *> items = collidingItems();
    if(!items.isEmpty())
    {
        Zombie *zombie = qgraphicsitem_cast<Zombie *> (items[qrand() % items.size()]);
        zombie->HP -= ATK;
        if(isSnow)
            zombie->speedFactor = 20;
        if(zombie->HP > 0)
            delete this;
    }
    setX(x() + 5);
    if(x() >= 1000)
        delete this;
}

bool Pea::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type() == Zombie::Type && x()-other->x()>50 && x()-other->x()<90
            && y()-other->y()>0 && y()-other->y()<100 ;
}

int Pea::type() const
{
    return Type;
}
