#include "cherrybomb.h"

Cherrybomb::Cherrybomb(QPointF point)
{
    HP = 500; ATK = 1800; prepareTime = 50; counter = 0;
    name = "CherryBomb"; atkStatus = 0;
    movie = new QMovie(":/graphics/Plants/" + name + "/1.gif");
    movie->setSpeed(25);
    movie->start();
    posX = point.x()-32;
    posY = point.y()-35;
    setPos(posX-180, posY);
}

Cherrybomb::~Cherrybomb()
{
    Map::PlantMap[(posX-250)/80][(posY-100)/90] = nullptr;
    if(movie)
        delete movie;
}

QRectF Cherrybomb::boundingRect() const
{
     return QRectF(180, 0, 100, 70);
}

void Cherrybomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(!atkStatus)
        painter->drawImage(boundingRect(), movie->currentImage());
    else
        painter->drawImage(QRectF(140, -50, 188, 204), movie->currentImage());
   // painter->drawRect(boundingRect());
}

void Cherrybomb::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(!atkStatus && counter == prepareTime)
    {
        delete movie;
        movie = new QMovie(":/graphics/Plants/" + name + "/Boom.gif");
        movie->start();
        atkStatus = 1;
    }
    if(atkStatus)
    {
        QList<QGraphicsItem *> items = collidingItems();
        foreach(QGraphicsItem *item, items)
        {
            Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
            zombie->HP -= ATK;
            if(zombie->HP <= 0)
                zombie->setStatus = -1;
        }
        if(movie->currentFrameNumber() == movie->frameCount() - 1)
           delete this;
    }
    else
        counter++;
    if(HP <= 0)
       delete this;
}

bool Cherrybomb::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type() == Zombie::Type && other->x()-x()<130 && x()-other->x()<170
            && y()-other->y()<200 && other->y()-y()<130;
}
