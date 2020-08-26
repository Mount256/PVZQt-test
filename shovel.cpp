#include "shovel.h"

bool Shovel::isMovePlant = 0;
Shovel::Shovel()
{
    this->setCursor(Qt::PointingHandCursor);
    isMovePlant = 0;
}

Shovel::~Shovel()
{

}

QRectF Shovel::boundingRect() const
{
    return QRectF(950, 0, 70, 70);
}

void Shovel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QImage image(":/graphics/Screen/shovel.png");
    painter->drawImage(boundingRect(), image);
}

void Shovel::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QCursor cursor(QPixmap(":/graphics/Screen/shovel.png"));
        QApplication::setOverrideCursor(cursor);
        isMovePlant = 1;
    }
}
