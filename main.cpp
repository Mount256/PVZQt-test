#include "menu.h"
#include "startbutton.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    Menu w;
    w.setWindowTitle("植物大战僵尸Qt版   by Mount256");
    w.show();
    return a.exec();
}
