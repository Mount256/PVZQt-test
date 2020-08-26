#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include "cards.h"
#include "shovel.h"
#include "sun.h"
#include "plant.h"
#include "zombie.h"
#include "commonzombie.h"
#include "screenzombie.h"
#include "conezombie.h"
#include "paperzombie.h"
#include "footballzombie.h"
#include "cherrybomb.h"
#include "wallnut.h"
#include "repeater.h"
#include "sunflower.h"
#include "snowpea.h"
#include "peashooter.h"
#include "potatomine.h"

class Map: public QGraphicsItem
{
public:
    Map();
    ~Map();
    static Cards *PreparedPlant;
    static Plant *PlantMap[9][5];
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int counter, coolTime;

};

#endif // MAP_H
