#include "maingame.h"
#include "ui_maingame.h"

MainGame::MainGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainGame)
{
    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(180, 0, 900, 600);

    map_view = new QGraphicsView(scene, this);
    map_view->setBackgroundBrush(QPixmap(":/graphics/Map/map0.jpg"));

    map = new Map;
    scene->addItem(map);

    selectbox = new SelectBox;
    scene->addItem(selectbox);

    Shovel *shovel = new Shovel;
    scene->addItem(shovel);

    Cards *cards[PLANT_NUM]={new sunflower, new peaShooter, new wallnut,
                             new cherryBomb, new repeater, new snowpea, new potatomine};
    for(int i = 0; i < PLANT_NUM; ++i)
        scene->addItem(cards[i]);

    for(int i = 0; i < 5; i++)
    {
        Car *car = new Car(i);
        scene->addItem(car);
    }

    QCursor cursor;
    cursor.setShape(Qt::ArrowCursor);
    setCursor(cursor);

    timer->start(33);
    map_view->show();

    quit *q = new quit(this);
    q->setGeometry(QRect(40, 20, 100, 25));
    q->show();
    pause *p = new pause(this);
    p->setGeometry(QRect(40, 55, 100, 25));
    p->show();

    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainGame::check);
    connect(timer, &QTimer::timeout, this, &MainGame::createZombie);
    connect(q, SIGNAL(closeGame()), this, SLOT(endGame()) );
    connect(q, SIGNAL(clicked()), this, SLOT(pauseGame()) );
    connect(q, SIGNAL(uncloseGame()), this, SLOT(continueGame()));
    connect(p, SIGNAL(start()), this, SLOT(continueGame()) );
    connect(p, SIGNAL(clicked()), this, SLOT(pauseGame()) );
}

MainGame::~MainGame()
{
    delete timer;
    delete map_view;
    delete map;
    delete selectbox;
    delete scene;
    delete ui;
}

void MainGame::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void MainGame::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
         QPoint Pos = event ->pos();
         qDebug() << "Pos:" << Pos;
    }
    if(event->button()==Qt::RightButton)
    {
         //setCursor(Qt::OpenHandCursor);
         QApplication::restoreOverrideCursor();
         Map::PreparedPlant = nullptr;
    }
}

void MainGame::mouseReleaseEvent(QMouseEvent *event)//鼠标释放事件
{
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
    qDebug() << "releaseView";
}

void MainGame::createZombie()
{
    QPointF zombiePos;
    QTime _time= QTime::currentTime();
    qsrand(_time.msec()+_time.second()*1000);
    static int duringTime = 200;
    static int counter = 0;
     if (++counter >= 100)
    {
        if(counter % duringTime == 0)
        {
            int posRand =  qrand() % 5 - 1;
            if(posRand == -1)
                zombiePos = QPointF(800, 145-60);
            else
                zombiePos = QPointF(800, 145+105*posRand);
            int kind = qrand() % 100;
            Zombie *zombie;
            if (kind < 50)
                zombie = new CommonZombie(zombiePos);
            else if (kind < 60)
                zombie = new ConeZombie(zombiePos);
            else if (kind < 70)
                zombie = new PaperZombie(zombiePos);
            else if (kind < 90)
                zombie = new ScreenZombie(zombiePos);
            else
                zombie = new FootballZombie(zombiePos);
            zombie->setZValue(posRand + 1);
            scene->addItem(zombie);
        }
    }
}

void MainGame::check()
{
    QList<QGraphicsItem *> items = scene->items();
    foreach (QGraphicsItem *item, items)
    {
     if (item->type() == Zombie::Type && item->x() < -100)
     {
         qDebug() <<"loose";
         timer->stop();
         FinishTip *tip = new FinishTip(false, this);
         connect(tip, SIGNAL(clicked()), this, SLOT(endGame()) );
         tip->show();
     }
    }
    if(Cards::sunTotal == 2000)
    {
        qDebug() <<"win";
        timer->stop();
        FinishTip *tip = new FinishTip(true, this);
        connect(tip, SIGNAL(clicked()), this, SLOT(endGame()) );
        tip->show();
    }
}

void MainGame::continueGame()
{
    timer->start(33);
}

void MainGame::pauseGame()
{
    timer->stop();
}

void MainGame::endGame()
{
    delete this;
}

