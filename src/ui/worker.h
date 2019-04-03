#ifndef WORKER_H
#define WORKER_H

#include <QMutex>
#include <QThread>

#include "mainwindow.h"
#include "src/Gameboy.hpp"

class Worker : public QObject {
  Q_OBJECT

 public:
  Worker();
  ~Worker();
 public slots:
  void process();
 signals:
  void finished();
  void error(QString err);
};

#endif
