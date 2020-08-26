#include "cards.h"
#include "map.h"
#include "maingame.h"

int Cards::sunTotal = 50;

Cards::Cards()
{
    counter = 0; StartMode = 1;
    sunNeed = -1; isPlanted = 0;
    setCursor(Qt::PointingHandCursor);
    setToolTip(tip);
    setZValue(0);
}

Cards::~Cards()
{
    sunTotal = 50;
}

void Cards::advance(int phase)
{
    if(!phase)
        return;
    update();
    if(counter < coolTime)
        ++counter;
    if(counter == coolTime)
        isPlanted = 0;
}

QRectF Cards::boundingRect() const
{
    return QRectF(425+60*No, 10, 50, 70);
}

void Cards::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QImage image(":/graphics/Cards/card_" + name.toLower() + ".png");
    painter->drawImage(boundingRect(), image);
    if(sunTotal < sunNeed)
    {
        painter->setBrush(QColor(128, 128, 0, 200));
        painter->drawRect(boundingRect());
    }
    if(counter < coolTime && !StartMode && isPlanted)
    {
        painter->setBrush(QColor(0, 0, 0, 200));
        painter->drawRect(QRectF(425+60*No, 10, 50, 70*(1-qreal(counter)/coolTime)));
    }
}

void Cards::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(sunTotal >= sunNeed && (counter == coolTime || StartMode)){
            QCursor cursor(QPixmap(":/graphics/Plants/" + name + "/0.gif"));
            QApplication::setOverrideCursor(cursor);
            Map::PreparedPlant = this;
            qDebug() << "CardClicked!" ;
        }
    }
}

void Cards::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

//================================================
sunflower::sunflower()
{
    name = "SunFlower"; coolTime = 227; No = 0;
    sunNeed = 50; tip = "向日葵(50)";
}

peaShooter::peaShooter ()
{
    name = "Peashooter"; coolTime = 227;  No = 1;
    sunNeed = 100; tip = "豌豆射手(100)";
}

wallnut::wallnut ()
{
    name = "WallNut"; coolTime = 606;  No = 2;
    sunNeed = 50; tip = "坚果(50)";
}

cherryBomb::cherryBomb ()
{
    name = "CherryBomb"; coolTime = 606;  No = 3;
    sunNeed = 150; tip = "樱桃炸弹(150)";
}

repeater::repeater()
{
    name = "Repeater"; coolTime = 454;  No = 4;
    sunNeed = 200; tip = "双重射手(200)";
}

snowpea::snowpea()
{
    name = "SnowPea"; coolTime = 454;  No = 5;
    sunNeed = 175; tip = "冰寒射手(175)";
}

potatomine::potatomine()
{
    name = "PotatoMine"; coolTime = 909; No = 6;
    sunNeed = 25; tip = "土豆地雷(25)";
}
