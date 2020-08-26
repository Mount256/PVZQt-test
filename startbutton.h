#ifndef STARTBUTTON_H
#define STARTBUTTON_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>

class StartButton : public QWidget
{
    Q_OBJECT
public:
    explicit StartButton(QWidget *parent = nullptr);
    QRect _rect;
    bool _pressed;
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

signals:
    clicked();

public slots:
};

#endif // STARTBUTTON_H
