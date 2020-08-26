#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "plant.h"
#include "sun.h"
#include "map.h"
#include <QGraphicsView>

class Sunflower : public Plant
{
public:
    Sunflower(QPointF point);
    ~Sunflower();
    void advance(int phase);

private:
    int sunCounter, sunCreateTime;
};

#endif // SUNFLOWER_H
