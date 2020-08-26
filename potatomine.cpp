#include "potatomine.h"

PotatoMine::PotatoMine(QPointF point)
{
    HP = 300; ATK = 1800; counter = 0; coolTime = 303;
    name = "PotatoMine"; atkStatus = 0;
    movie = new QMovie(":/graphics/Plants/" + name + "/1.gif");
    movie->start();
    posX = point.x()-32;
    posY = point.y()-35;
    setPos(posX-180, posY);
    qDebug() << x() <<y();
}

PotatoMine::~PotatoMine()
{
    Map::PlantMap[(posX-250)/80][(posY-100)/90] = nullptr;
    if(movie)
        delete movie;
}

void PotatoMine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(), movie->currentImage());
    //painter->drawRect(boundingRect());
}

void PotatoMine::advance(int phase)
{
    if (!phase)
        return;
    update();
    if(atkStatus == 0 && counter < coolTime)
        counter ++;
    if(counter == coolTime)
    {
        delete movie;
        movie = new QMovie(":/graphics/Plants/" + name + "/PotatoMine.gif");
        movie->start();
        counter = 0; atkStatus = 1;
    }
    if(atkStatus == 1)
    {
        QList<QGraphicsItem *> items = collidingItems();
        if (!items.isEmpty())
        {
            foreach (QGraphicsItem *item, items)
            {
                atkStatus = 2; counter = 0;
                Zombie *zombie = qgraphicsitem_cast<Zombie *>(item);
                zombie->HP -= ATK;
                delete movie;
                movie = new QMovie(":/graphics/Plants/" + name + "/PotatoMine_mashed.gif");
                movie->start();
                if (zombie->HP <= 0)
                    zombie->setStatus = -1;
            }
        }
    }
    if(atkStatus == 2)
    {
        counter ++;
        if(counter == 50)
            delete this;
    }
    if(HP <= 0)
        delete this;
}

bool PotatoMine::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type() == Zombie::Type && other->x()-x()>-75 && other->x()-x()<-14
            && other->y()-y()>-95 && other->y()-y()<0;
}
