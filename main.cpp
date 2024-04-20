#include "mainwindow.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/images/main.png"));
    a.setApplicationName("RB AUTO");
    a.setApplicationDisplayName("RAPPROCHEMENT BANCAIRE AUTO");
    a.setApplicationVersion("1.0.0");

    MainWindow w;
    w.setWindowIcon(QIcon(":/images/images/main.png"));
    w.show();
    return a.exec();
}
