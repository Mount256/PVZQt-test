#include "commonzombie.h"

CommonZombie::CommonZombie(QPointF point)
{
    HP = 200; crHP = 70; ATK = 5; speed = 0.40;
    name = "Zombie";
    if(qrand() % 2)
        movie = new QMovie(":/graphics/Zombies/" + name + "/Zombie1.gif");
    else
        movie = new QMovie(":/graphics/Zombies/" + name + "/Zombie3.gif");
    movie->start();
    posX = (point.x()-32);
    posY = (point.y()-35);
    setPos(posX, posY);
}

CommonZombie::~CommonZombie()
{
    if(movie)
        delete movie;
}

void CommonZombie::advance(int phase)
{
    if(!phase)
        return;
    update();
    QList <QGraphicsItem *> items = collidingItems();
    if(setStatus != -1)
    {
     if(HP >= crHP){           // 70-200 正常有攻击力
        setStatus = 1;
        if(!items.isEmpty()){   // 如果碰到植物
            setStatus = 2;
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
            stackBefore(plant);
        }
     }
     else if(HP > 0){        // 0-70 到达临界值不再有攻击力，HP匀速减少
        HP--;
        setStatus = 3;
        if(!items.isEmpty()){
            setStatus = 4;   // 如果碰到植物
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
            stackBefore(plant);
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
           bodyMovie("/graphics/Zombies/" + name + "/BoomDie.gif");
        break;
    case 0:
        speedFactor = 100;
       if(setStatus != nowStatus)
       {
          bodyMovie(":/graphics/Zombies/" + name + "/ZombieDie.gif");
          if(isHead)
              headMovie(":/graphics/Zombies/" + name + "/ZombieHead.gif");
       }
       break;
    case 1:
       if(setStatus != nowStatus)
         bodyMovie(":/graphics/Zombies/" + name + "/Zombie3.gif");
       setX(x() - speed  * speedFactor / 100);
       break;
    case 2:
       if(setStatus != nowStatus)
            bodyMovie(":/graphics/Zombies/" + name + "/ZombieAttack.gif");
       plant->HP -= ATK  * speedFactor / 100;
       break;
    case 3:
       if(setStatus != nowStatus)
       {
          bodyMovie(":/graphics/Zombies/" + name + "/ZombieLostHead.gif");
          if(isHead)
              headMovie(":/graphics/Zombies/" + name + "/ZombieHead.gif");
       }
       setX(x() - speed / 2);
       break;
    case 4:
       if(setStatus != nowStatus)
       {
            bodyMovie(":/graphics/Zombies/" + name + "/ZombieLostHeadAttack.gif");
            if(isHead)
                headMovie(":/graphics/Zombies/" + name + "/ZombieHead.gif");
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
    if(!items.empty())
        items.clear();
}
