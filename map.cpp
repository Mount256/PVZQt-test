#include "map.h"

Cards* Map::PreparedPlant = nullptr;
Plant* Map::PlantMap[9][5];
Map::Map()
{
    counter = 0; coolTime = 313;
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 5; ++j)
            PlantMap[i][j] = nullptr;
    this->setAcceptedMouseButtons(Qt::AllButtons);
}

Map::~Map()
{
    PreparedPlant = nullptr;
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 5; ++j)
            delete PlantMap[i][j];
}

QRectF Map::boundingRect() const
{
    return QRectF(250, 100, 747, 460);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QColor(0, 0, 0, 0));
    //painter->drawRect(boundingRect());
}

void Map::advance(int phase)
{
    if (!phase)
              return;
        update();
        if(counter < coolTime)
            ++counter;
        if(counter == coolTime)
        {
           Sun *sun = new Sun;
           scene()->addItem(sun);
           counter = 0;
        }
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(PreparedPlant && event->button()==Qt::LeftButton)
    {
        Shovel::isMovePlant = 0;
        int i = ((int)event->scenePos().x() - 250) / 80;
        int j = ((int)event->scenePos().y() - 100) / 90;
        if(i == 9) --i;  if(j == 5) --j;
        qDebug()<< i << j;
        if(!PlantMap[i][j])
        {
            QPointF plantPos(290+80*i, 145+90*j);
            switch(PreparedPlant->No)
            {
            case 0: PlantMap[i][j] = new Sunflower(plantPos); break;
            case 1: PlantMap[i][j] = new Peashooter(plantPos); break;
            case 2: PlantMap[i][j] = new Wallnut(plantPos); break;
            case 3: PlantMap[i][j] = new Cherrybomb(plantPos); break;
            case 4: PlantMap[i][j] = new Repeater(plantPos); break;
            case 5: PlantMap[i][j] = new SnowPea(plantPos); break;
            case 6: PlantMap[i][j] = new PotatoMine(plantPos); break;
            default: break;
            }
            PlantMap[i][j]->setZValue(j);
            scene()->addItem(PlantMap[i][j]);
            PreparedPlant->isPlanted = 1;
            PreparedPlant->counter = 0; PreparedPlant->StartMode = 0;
            PreparedPlant->sunTotal -= PreparedPlant->sunNeed;
            PreparedPlant = nullptr;
            QApplication::restoreOverrideCursor();
        }    
    }

    if(Shovel::isMovePlant && event->button()==Qt::LeftButton)
    {
        int i = ((int)event->scenePos().x() - 250) / 80;
        int j = ((int)event->scenePos().y() - 100) / 90;
        if(i == 9) --i;  if(j == 5) --j;
        qDebug()<< i << j;
        delete PlantMap[i][j];
        PlantMap[i][j] = nullptr;
        Shovel::isMovePlant = 0;
        QApplication::restoreOverrideCursor();
    }
    if(event->button()==Qt::RightButton)
    {
         PreparedPlant = nullptr;
         QApplication::restoreOverrideCursor();
    }
}

void Map::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

}
