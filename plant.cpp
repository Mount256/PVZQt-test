#include "plant.h"
#include "maingame.h"

Plant::Plant()
{

}

Plant::~Plant()
{

}

QRectF Plant::boundingRect() const
{
    return QRectF(180, 0, 64, 70);
}

void Plant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(), movie->currentImage());
   // painter->drawRect (boundingRect());
}

void Plant::advance(int phase)
{
    if(!phase)
        return;
    update();
}

int Plant::type() const
{
    return Type;
}







