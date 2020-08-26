#include "sunflower.h"

Sunflower::Sunflower(QPointF point)
{
    HP = 300; sunCounter = 0; sunCreateTime = 454;
    name = "SunFlower";
    movie = new QMovie(":/graphics/Plants/" + name + "/1.gif");
    movie->start();
    posX = point.x()-32;
    posY = point.y()-35;
    setPos(posX-180, posY);
}

Sunflower::~Sunflower()
{
    Map::PlantMap[(posX-250)/80][(posY-100)/90] = nullptr;
    if(movie)
        delete movie;
}

void Sunflower::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(sunCounter < sunCreateTime)
        ++sunCounter;
    if(sunCounter == sunCreateTime)
    {
        Sun *sun = new Sun(QPointF(posX, posY-40));
        scene()->addItem(sun);
        sunCounter = 0;
    }
    if(HP <= 0)
        delete this;
}
