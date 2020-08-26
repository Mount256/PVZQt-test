#ifndef PAUSE_H
#define PAUSE_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>
#include <QFont>

namespace Ui {
class pause;
}

class pause : public QWidget
{
    Q_OBJECT

public:
    explicit pause(QWidget *parent = 0);
    ~pause();
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    Ui::pause *ui;

signals:
    clicked();
    void start();
};

#endif // PAUSE_H
