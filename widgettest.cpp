#include "widgettest.h"
#include "ui_widgettest.h"

WidgetTest::WidgetTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetTest)
{
    ui->setupUi(this);
}

WidgetTest::~WidgetTest()
{
    delete ui;
}

void WidgetTest::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    setAttribute(Qt::WA_TranslucentBackground, true);
    p.fillRect(rect(), QColor(100, 0, 0, 200));
}


void WidgetTest::on_pushButton_clicked()
{
    QMessageBox::StandardButton q = QMessageBox::question(NULL, "question", "确定返回菜单吗？不会保存游戏哦",
                                                          QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(q == QMessageBox::Yes)
        delete this;
}
