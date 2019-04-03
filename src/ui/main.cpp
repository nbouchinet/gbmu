#include <QAction>
#include <QApplication>
#include <QIcon>
#include <QObject>
#include <QPushButton>
#include <QToolBar>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
