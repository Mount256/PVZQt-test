#ifndef FOOTBALLZOMBIE_H
#define FOOTBALLZOMBIE_H
#include "zombie.h"

class FootballZombie : public Zombie
{
public:
    FootballZombie(QPointF point);
    ~FootballZombie();
    void advance(int phase);

private:
    int ornHP;
};

#endif // FOOTBALLZOMBIE_H
