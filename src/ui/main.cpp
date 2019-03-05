#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
