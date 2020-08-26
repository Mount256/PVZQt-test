#include "quit.h"
#include "ui_quit.h"

quit::quit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quit)
{
    setCursor(Qt::PointingHandCursor);
    ui->setupUi(this);
}

quit::~quit()
{
    delete ui;
}

void quit::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
        QMessageBox::StandardButton q = QMessageBox::information(NULL, "返回游戏菜单", "确定返回游戏菜单吗？不会保存游戏哦",
                                                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(q == QMessageBox::Yes)
            emit closeGame();
        if(q == QMessageBox::No)
            emit uncloseGame();
    }
}

void quit::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QFont font;
    font.setPointSize(12);
    p.setBrush(QColor(128, 128, 0, 250));
    p.drawRect(rect());
    p.setFont(font);
    p.drawText(rect(), Qt::AlignHCenter | Qt::AlignBottom, "返回菜单");
}


