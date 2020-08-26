#include "peashooter.h"

Peashooter::Peashooter(QPointF point)
{
    HP = 300; peaCounter = 0; peaCreateTime = 42;
    name = "Peashooter";
    movie = new QMovie(":/graphics/Plants/" + name + "/1.gif");
    movie->start();
    posX = point.x()-32;
    posY = point.y()-35;
    setPos(posX-180, posY);
}

Peashooter::~Peashooter()
{
    Map::PlantMap[(posX-250)/80][(posY-100)/90] = nullptr;
    if(movie)
        delete movie;
}

void Peashooter::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(peaCounter < peaCreateTime)
        ++peaCounter;
    if(peaCounter == peaCreateTime)
    {
        pea = new Pea(QPointF(posX+50, posY));
        scene()->addItem(pea);
        peaCounter = 0;
    }
    if(HP <= 0)
        delete this;
}

