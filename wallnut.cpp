#include "wallnut.h"

Wallnut::Wallnut(QPointF point)
{
    HP = 4000; setStatus = 0; nowStatus = 0;
    name = "WallNut";
    movie = new QMovie(":/graphics/Plants/" + name + "/1.gif");
    movie->start();
    posX = point.x()-32;
    posY = point.y()-35;
    setPos(posX-180, posY);
}

Wallnut::~Wallnut()
{
    Map::PlantMap[(posX-250)/80][(posY-100)/90] = nullptr;
    if(movie)
        delete movie;
}

void Wallnut::advance(int phase)
{
    if(!phase)
        return;
    update();

    if(HP >= 4000 * 2 / 3)
        setStatus = 0;
    else if(HP >= 4000 * 1 / 3)
        setStatus = 1;
    else if(HP > 0)
        setStatus = 2;
    else if(HP <= 0)
        delete this;
    if(setStatus != nowStatus)
        switch(setStatus)
        {
        case 1:
            delete movie;
            movie = new QMovie(":/graphics/Plants/" + name + "/Wallnut_cracked1.gif");
            movie->start();
            break;
        case 2:
            delete movie;
            movie = new QMovie(":/graphics/Plants/" + name + "/Wallnut_cracked2.gif");
            movie->start();
            break;
        default:
            break;
        }
    nowStatus = setStatus;
}
