#ifndef COMMONZOMBIE_H
#define COMMONZOMBIE_H
#include "zombie.h"
#include "plant.h"

class CommonZombie : public Zombie
{
public:
    CommonZombie(QPointF point);
    ~CommonZombie();
    void advance(int phase);

};

#endif // COMMONZOMBIE_H
