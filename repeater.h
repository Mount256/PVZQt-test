#ifndef REPEATER_H
#define REPEATER_H
#include "plant.h"
#include "pea.h"
#include "map.h"

class Repeater : public Plant
{
public:
    Repeater(QPointF point);
    ~Repeater();
    void advance(int phase);

private:
    Pea *pea;
    int peaCounter, peaCreateTime;
};

#endif // REPEATER_H
