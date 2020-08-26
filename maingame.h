#ifndef MAINGAME_H
#define MAINGAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include "zombie.h"
#include "quit.h"
#include "pause.h"
#include "selectbox.h"
#include "map.h"
#include "shovel.h"
#include "car.h"
#include "finishtip.h"

namespace Ui {
class MainGame;
}

const int PLANT_NUM = 7;

class MainGame : public QWidget
{
    Q_OBJECT

public:
    explicit MainGame(QWidget *parent = 0);
    ~MainGame();
    QGraphicsScene* scene;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void createZombie();
    void check();

private:
    QTimer *timer;
    QGraphicsView *map_view;
    Ui::MainGame *ui;
    Map *map;
    SelectBox *selectbox;

public slots:
    void pauseGame();
    void continueGame();
    void endGame();
};

#endif // MAINGAME_H
