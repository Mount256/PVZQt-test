#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPainter>
#include <QDialog>
#include <QMouseEvent>
#include <QPushButton>
#include "startbutton.h"
#include "battletip.h"
#include "widgettest.h"
#include "maingame.h"

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
    StartButton *button;
    BattleTip *tip;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void showTip();

private slots:
    void slotButtonClicked();
    void startGame();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
