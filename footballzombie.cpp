#include "footballzombie.h"

FootballZombie::FootballZombie(QPointF point)
{
    HP = 350; ornHP = 270; crHP = 70; ATK = 5; speed = 0.80;
    name = "FootballZombie";
    movie = new QMovie(":/graphics/Zombies/" + name + "/" + name + ".gif");
    movie->start();
    posX = (point.x()-32);
    posY = (point.y()-35);
    setPos(posX, posY);
}

FootballZombie::~FootballZombie()
{
    if(movie)
        delete movie;
}

void FootballZombie::advance(int phase)
{
    if(!phase)
        return;
    update();
    QList <QGraphicsItem *> items = collidingItems();
    if(setStatus != -1)
    {
     if(HP >= ornHP){           // 270-350 有头盔
        setStatus = 1;
        if(!items.isEmpty()){   // 如果碰到植物
            setStatus = 2;
            plant = qgraphicsitem_cast<Plant *> (items[qrand() % items.size()]);
        }
     }
     else if(HP >= crHP){  //70-270 无头盔
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
            bodyMovie(":/graphics/Zombies/" + name + "/" + name + "OrnLost.gif");
       setX(x() - speed * speedFactor / 100);
       break;
    case 4:
        if(setStatus != nowStatus)
            bodyMovie(":/graphics/Zombies/" + name + "/" + name + "OrnLostAttack.gif");
        plant->HP -= ATK * speedFactor / 100;
       break;
    case 5:
       if(setStatus != nowStatus)
       {
          bodyMovie(":/graphics/Zombies/" + name + "/LostHead.gif");
          if(isHead)
              headMovie(":/graphics/Zombies/Zombie/ZombieHead.gif");
       }
       setX(x() - speed * speedFactor / 100);
       break;
    case 6:
       if(setStatus != nowStatus)
       {
            bodyMovie(":/graphics/Zombies/" + name + "/LostHeadAttack.gif");
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




