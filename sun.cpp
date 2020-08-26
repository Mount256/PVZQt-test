#include "sun.h"

Sun::Sun()
{
    counter = 0; existTime = 187; isFlower = 0;
    movie = new QMovie(":/graphics/Screen/Sun.gif");
    movie->start();
    QTime time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    posX = qrand() % (900 - 250) + 250;
    posY = 87;
    setZValue(7);
    setCursor(Qt::PointingHandCursor);
    qDebug() <<"sun "<<posX<<posY;
}

Sun::Sun(QPointF point)
{
    counter = 0; existTime = 200; isFlower = 1;
    movie = new QMovie(":/graphics/Screen/Sun.gif");
    movie->start();
    posX = point.x();
    posY = point.y();
    setCursor(Qt::PointingHandCursor);
    setZValue(7);
}

Sun::~Sun()
{

}

QRectF Sun::boundingRect() const
{
    return QRectF(posX, posY, 70, 70);
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawImage(boundingRect(), movie->currentImage());
}

void Sun::advance(int phase)
{
    if(!phase)
        return;
    update();
    QTime time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    if(counter < existTime)
        ++counter;
    if(!isFlower && (qreal)counter < (qreal)existTime * (qrand() % (3 - 1) + 1) * 0.1 )
        setY(y() + 2);
    if(counter == existTime)
        delete this;
}

int Sun::type() const
{
    return Type;
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug()<<"clicksun!";
        Cards::sunTotal += 25;
        delete this;
    }
}
