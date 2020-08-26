#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    QCursor cursor;
    cursor.setShape(Qt::OpenHandCursor);
    setCursor(cursor);
    button = new StartButton(this);
    connect( button, SIGNAL(clicked()), this, SLOT(slotButtonClicked()) );
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(":/graphics/Screen/MainMenu.png"), QRect());
}

void Menu::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
        qDebug() << event->pos();
    }
}

void Menu::mouseReleaseEvent(QMouseEvent *event)//鼠标释放事件
{
    Q_UNUSED(event);
    QApplication::restoreOverrideCursor();//恢复鼠标指针形状
}

void Menu::slotButtonClicked()
{
    tip = new BattleTip(this);
    connect( tip, SIGNAL(clicked()), this, SLOT(startGame()) );
    tip->show();
    qDebug() <<"clicked!";
}

void Menu::startGame()
{
    MainGame *mg = new MainGame(this);
    mg->show();
    qDebug() <<"startGame!";
}

