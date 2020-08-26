#include "paperzombie.h"

PaperZombie::PaperZombie(QPointF point)
{
    HP = 300; paperHP = 250; crHP = 70; ATK = 5; speed = 0.40;
    name = "NewspaperZombie"; isPaper = 1;
    movie = new QMovie(":/graphics/Zombies/" + name + "/HeadWalk1.gif");
    movie->start();
    posX = (point.x()-32);
    posY = (point.y()-35);
    setPos(posX, posY);
}

PaperZombie::~PaperZombie()
{
    if(movie)
        delete movie;
}

QRectF PaperZombie::boundingRect() const
{
    return QRectF(180, 0, 170, 150);
}

void PaperZombie::advance(int phase)
{
    if(!phase)
        return;
    update();
    QList <QGraphicsItem *> items = collidingItems();
    if(setStatus != -1)
    {
     if(HP >= paperHP){           // 250-300 有报纸
        setStatus = 1;
        if(!items.isEmpty()){   // 如果碰到植物
            setStatus = 2;
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
        }
     }
     else if(HP >= crHP){  //70-250 无报纸
        setStatus = 3;
        if(!items.isEmpty()){   // 如果碰到植物
            setStatus = 4;
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
        }
     }
     else if(HP > 0){        // 0-70 到达临界值不再有攻击力，HP匀速减少
        HP--;
        setStatus = 5;
        if(!items.isEmpty()){
            setStatus = 6;   // 如果碰到植物
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
        }
    }
    else                    // <0 死亡
        setStatus = 0;
    }

    switch(setStatus)
    {
    case -1:
        speedFactor = 100;
        if(setStatus != nowStatus)
           bodyMovie(":/graphics/Zombies/" + name + "/BoomDie.gif");
        break;
    case 0:
        speedFactor = 100;
       if(setStatus != nowStatus)
       {
          bodyMovie(":/graphics/Zombies/" + name + "/Die.gif");
          if(isHead)
              headMovie(":/graphics/Zombies/" + name + "/Head.gif");
       }
       break;
    case 1:
       if(setStatus != nowStatus)
         bodyMovie(":/graphics/Zombies/" + name + "/HeadWalk1.gif");
       setX(x() - speed * speedFactor / 100);
       break;
    case 2:
       if(setStatus != nowStatus)
            bodyMovie(":/graphics/Zombies/" + name + "/HeadAttack1.gif");
       plant->HP -= ATK * speedFactor / 100;
       break;
    case 3:
       if(setStatus != nowStatus)
       {
           if(isPaper)
                bodyMovie(":/graphics/Zombies/" + name + "/LostNewspaper.gif");
           else
                bodyMovie(":/graphics/Zombies/" + name + "/HeadWalk0.gif");
       }
       if(!isPaper)
           setX(x() - speed * 2 * speedFactor / 100);
       break;
    case 4:
        if(setStatus != nowStatus)
        {
            if(isPaper)
                 bodyMovie(":/graphics/Zombies/" + name + "/LostNewspaper.gif");
            else
                 bodyMovie(":/graphics/Zombies/" + name + "/HeadAttack0.gif");
        }
        if(!isPaper)
            plant->HP -= ATK * 2 * speedFactor / 100;
       break;
    case 5:
       if(setStatus != nowStatus)
       {
          bodyMovie(":/graphics/Zombies/" + name + "/LostHeadWalk0.gif");
          if(isHead)
              headMovie(":/graphics/Zombies/" + name + "/Head.gif");
       }
       setX(x() - speed * speedFactor / 100);
       break;
    case 6:
       if(setStatus != nowStatus)
       {
            bodyMovie(":/graphics/Zombies/" + name + "/LostHeadAttack0.gif");
            if(isHead)
                headMovie(":/graphics/Zombies/" + name + "/Head.gif");
       }
        break;
    default:
        break;
    }
    nowStatus = setStatus;
    if(nowStatus == 0 || nowStatus == -1)
        if (movie->currentFrameNumber() == movie->frameCount() - 1)
           delete this;
    if(head)
         if (head->currentFrameNumber() == head->frameCount() - 1)
         {
             delete head;
             head = nullptr;
         }
    if(isPaper && (nowStatus == 3 || nowStatus == 4) )
    {
        if (movie->currentFrameNumber() == movie->frameCount() - 1)
        {
            isPaper = 0;
            nowStatus = 2;
        }
    }
    if(!items.empty())
        items.clear();
}
