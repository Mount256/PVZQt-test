#include "pause.h"
#include "ui_pause.h"

pause::pause(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pause)
{
    setCursor(Qt::PointingHandCursor);
    ui->setupUi(this);
}

pause::~pause()
{
    delete ui;
}

void pause::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
        QMessageBox::StandardButton q = QMessageBox::information(NULL, "游戏暂停", "游戏暂停中，点击OK继续游戏");
        if(q == QMessageBox::Ok)
            emit start();
    }
    update();
}

void pause::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QFont font;
    font.setPointSize(12);
    p.setBrush(QColor(128, 128, 0, 250));
    p.drawRect(rect());
    p.setFont(font);
    p.drawText(rect(), Qt::AlignHCenter | Qt::AlignBottom, "游戏暂停");
}
