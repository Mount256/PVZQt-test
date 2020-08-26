#include "finishtip.h"
#include "ui_finishtip.h"

FinishTip::FinishTip(bool _isWin, QWidget *parent) :
    QWidget(parent), isWin(_isWin),
    ui(new Ui::FinishTip)
{
    this->setGeometry(0, 0, 900, 600);
    this->setCursor(Qt::PointingHandCursor);
    ui->setupUi(this);
}

FinishTip::~FinishTip()
{
    delete ui;
}

void FinishTip::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    setAttribute(Qt::WA_TranslucentBackground, true);
    p.fillRect(rect(), QColor(0, 0, 0, 150));
    if(!isWin)
        p.drawPixmap(135, 65, 605, 435, QPixmap(":/graphics/Screen/ZombiesWon.png"));
    else
         p.drawPixmap(135, 65, 605, 435, QPixmap(":/graphics/Screen/GameVictory.png"));
}

void FinishTip::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit clicked();
}
