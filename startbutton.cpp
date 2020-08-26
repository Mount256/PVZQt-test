#include "startbutton.h"

StartButton::StartButton(QWidget *parent) : QWidget(parent)
{
    _pressed = false;
    this->setGeometry(470, 150, 300, 180);
    this->setCursor(Qt::PointingHandCursor);
}

void StartButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QCursor cursor;
    cursor.setShape(Qt::ClosedHandCursor);
    QApplication::setOverrideCursor(cursor);
    _pressed = true;
    update();
}

void StartButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QApplication::restoreOverrideCursor();
    _pressed = false;
    emit clicked();
    update();
}

void StartButton::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if(_pressed)
      p.drawPixmap(rect(), QPixmap(":/graphics/Screen/Adventure_1.png"), QRect());
    else
      p.drawPixmap(rect(), QPixmap(":/graphics/Screen/Adventure_0.png"), QRect());
}
