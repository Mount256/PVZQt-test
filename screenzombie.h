#ifndef SCREENZOMBIE_H
#define SCREENZOMBIE_H
#include "zombie.h"

class ScreenZombie : public Zombie
{
public:
    ScreenZombie(QPointF point);
    ~ScreenZombie();
    void advance(int phase);

};

#endif // SCREENZOMBIE_H
