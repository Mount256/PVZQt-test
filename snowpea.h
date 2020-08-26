#ifndef SNOWPEA_H
#define SNOWPEA_H
#include "plant.h"
#include "pea.h"
#include "map.h"

class SnowPea:public Plant
{
public:
    SnowPea(QPointF point);
    ~SnowPea();
    void advance(int phase);

private:
    Pea *pea;
    int peaCounter, peaCreateTime;
};

#endif // SNOWPEA_H
