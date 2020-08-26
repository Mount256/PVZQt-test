#include "battletip.h"

BattleTip::BattleTip(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(0, 0, 900, 600);
    this->setCursor(Qt::PointingHandCursor);
}

BattleTip::~BattleTip()
{

}

void BattleTip::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    setAttribute(Qt::WA_TranslucentBackground, true);
    p.fillRect(rect(), QColor(0, 0, 0, 150));
    p.drawPixmap(135, 65, 605, 435, QPixmap(":/graphics/Screen/ZombieNote1.png"));
}

void BattleTip::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
        delete this;
    }
}
