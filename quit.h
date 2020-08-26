#ifndef QUIT_H
#define QUIT_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>
#include <QFont>

namespace Ui {
class quit;
}

class quit : public QWidget
{
    Q_OBJECT

public:
    explicit quit(QWidget *parent = 0);
    ~quit();
    bool _pressed;
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    Ui::quit *ui;

signals:
    clicked();
    void closeGame();
    void uncloseGame();
};

#endif // QUIT_H
