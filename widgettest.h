#ifndef WIDGETTEST_H
#define WIDGETTEST_H

#include <QWidget>
#include <QPainter>
#include <QMessageBox>

namespace Ui {
class WidgetTest;
}

class WidgetTest : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetTest(QWidget *parent = 0);
    ~WidgetTest();
     void paintEvent(QPaintEvent *);

private slots:


     void on_pushButton_clicked();

private:
    Ui::WidgetTest *ui;
};

#endif // WIDGETTEST_H
