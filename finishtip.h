#ifndef FINISHTIP_H
#define FINISHTIP_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class FinishTip;
}

class FinishTip : public QWidget
{
    Q_OBJECT

public:
    explicit FinishTip(bool _isWin = true, QWidget *parent = 0);
    ~FinishTip();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    Ui::FinishTip *ui;
    bool isWin;

signals:
    clicked();
};

#endif // FINISHTIP_H
