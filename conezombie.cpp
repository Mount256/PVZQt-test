#include "conezombie.h"

ConeZombie::ConeZombie(QPointF point)
{
    HP = 300; coneHP = 200; crHP = 70; ATK = 5; speed = 0.40;
    if(qrand() % 2 == 0)
        name = "ConeheadZombie";
    else
        name = "BucketheadZombie";
    movie = new QMovie(":/graphics/Zombies/" + name + "/" + name + ".gif");
    movie->start();
    posX = (point.x()-32);
    posY = (point.y()-35);
    setPos(posX, posY);
}

ConeZombie::~ConeZombie()
{
    if(movie)
        delete movie;
}

void ConeZombie::advance(int phase)
{
    if(!phase)
        return;
    update();
    QList <QGraphicsItem *> items = collidingItems();
    if(setStatus != -1)
    {
     if(HP >= coneHP){           // 200-300 有帽子
        setStatus = 1;
        if(!items.isEmpty()){   // 如果碰到植物
            setStatus = 2;
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
        }
     }
     else if(HP >= crHP){  //70-200 无帽子（普通僵尸）
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
           bodyMovie(":/graphics/Zombies/Zombie/BoomDie.gif");
        break;
    case 0:
        speedFactor = 100;
       if(setStatus != nowStatus)
       {
          bodyMovie(":/graphics/Zombies/Zombie/ZombieDie.gif");
          if(isHead)
              headMovie(":/graphics/Zombies/Zombie/ZombieHead.gif");
       }
       break;
    case 1:
       if(setStatus != nowStatus)
         bodyMovie(":/graphics/Zombies/" + name + "/" + name + ".gif");
       setX(x() - speed * speedFactor / 100);
       break;
    case 2:
       if(setStatus != nowStatus)
            bodyMovie(":/graphics/Zombies/" + name + "/" + name + "Attack.gif");
       plant->HP -= ATK * speedFactor / 100;
       break;
    case 3:
       if(setStatus != nowStatus)
         bodyMovie(":/graphics/Zombies/Zombie/Zombie3.gif");
       setX(x() - speed * speedFactor / 100);
       break;
    case 4:
       if(setStatus != nowStatus)
            bodyMovie(":/graphics/Zombies/Zombie/ZombieAttack.gif");
       plant->HP -= ATK * speedFactor / 100;
       break;
    case 5:
       if(setStatus != nowStatus)
       {
          bodyMovie(":/graphics/Zombies/Zombie/ZombieLostHead.gif");
          if(isHead)
              headMovie(":/graphics/Zombies/Zombie/ZombieHead.gif");
       }
       setX(x() - speed / 2 * speedFactor / 100);
       break;
    case 6:
       if(setStatus != nowStatus)
       {
            bodyMovie(":/graphics/Zombies/Zombie/ZombieLostHeadAttack.gif");
            if(isHead)
                headMovie(":/graphics/Zombies/Zombie/ZombieHead.gif");
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
