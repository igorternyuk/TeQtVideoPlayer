#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("fusion");
    app.setApplicationName("TeQtVideoPlayer");
    app.setApplicationVersion("1.0");
    app.setObjectName("TernyukCorporation");
    app.setOrganizationDomain("www.igorternyuk.com");

    MainWindow w;
    w.show();

    return app.exec();
}
