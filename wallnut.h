#ifndef WALLNUT_H
#define WALLNUT_H
#include "plant.h"
#include "map.h"

class Wallnut : public Plant
{
public:
    Wallnut(QPointF point);
    ~Wallnut();
    void advance(int phase);

private:
    int setStatus, nowStatus;
};

#endif // WALLNUT_H
