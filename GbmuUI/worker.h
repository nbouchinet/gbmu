#ifndef WORKER_H
# define WORKER_H

#include <QThread>
#include <QMutex>

#include "src/Gameboy.hpp"
#include "mainwindow.h"

class Worker : public QObject
{
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
