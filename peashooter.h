#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "plant.h"
#include "pea.h"
#include "map.h"

class Peashooter : public Plant
{
public:
    Peashooter(QPointF point);
    ~Peashooter();
    void advance(int phase);

private:
    Pea *pea;
    int peaCounter, peaCreateTime;
};

#endif // PEASHOOTER_H
