#ifndef CONEZOMBIE_H
#define CONEZOMBIE_H
#include "zombie.h"

class ConeZombie : public Zombie
{
public:
    ConeZombie(QPointF point);
    ~ConeZombie();
    void advance(int phase);

private:
    int coneHP;
};

#endif // CONEZOMBIE_H
