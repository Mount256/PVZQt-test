#ifndef BATTLETIP_H
#define BATTLETIP_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>


class BattleTip : public QWidget
{
    Q_OBJECT

public:
    explicit BattleTip(QWidget *parent = 0);
    ~BattleTip();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:


signals:
    clicked();
};

#endif // BATTLETIP_H
