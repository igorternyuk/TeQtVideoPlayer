#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow w;
    QRect desktop = QApplication::desktop()->geometry();
    int dx = (desktop.width() - w.width()) / 2;
    int dy = (desktop.height() - w.height()) / 2;
    w.move(dx, dy);
    w.show();

    return a.exec();
}
