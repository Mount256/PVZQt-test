#include "zombie.h"

Zombie::Zombie()
{
    head = nullptr; speedFactor = 100;
    isHead = 1;  snowCounter = 0;
    setStatus = 1; nowStatus = 1;
}

Zombie::~Zombie()
{

}

QRectF Zombie::boundingRect() const
{
    return QRectF(180, 0, 150, 150);
}

void Zombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(), movie->currentImage());
    if(head)
        painter->drawImage(QRectF(220, 0, 140, 155), head->currentImage());
   // painter->drawRect(boundingRect());
}

void Zombie::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(x() <= 150)
        delete this;
    if(speedFactor != 100 && snowCounter < 200)
    {
        snowCounter++;
        if(snowCounter == 200)
        {
            speedFactor = 100;
            snowCounter = 0;
        }
    }
}

bool Zombie::collidesWithItem(const QGraphicsItem *other, Qt::ItemSelectionMode mode) const
{
    Q_UNUSED(mode);
    return other->type() == Plant::Type && other->x()-x()<80 && other->x()-x()>15
            && other->y()-y()>0 && other->y()-y()<100;
}

int Zombie::type() const
{
    return Type;
}

void Zombie::bodyMovie(QString pic)
{
    if (movie)
        delete movie;
    movie = new QMovie(pic);
    movie->setSpeed(speedFactor);
    movie->start();
}

void Zombie::headMovie(QString pic)
{
     if (head)
         delete head;
     head = new QMovie(pic);
     head->setSpeed(70);
     head->start();
     isHead = 0;
}
