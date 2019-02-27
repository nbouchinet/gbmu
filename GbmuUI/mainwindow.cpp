#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gbmuscreen.h"
#include "debuggerwindow.h"
#include "worker.h"

#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <QTimer>
#include <QKeyEvent>
#include <QThread>

Gameboy g_gameboy("/Users/hublanc/Documents/gbInput/tools/Tetris.gb");
QMutex mutexGb;

#include <iostream>
#include <unistd.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	//Setting up gameboy's screen
    GbmuScreen *gameboyScreen = new GbmuScreen(this);
    QTimer *timerScreen = new QTimer(this);
    connect(timerScreen, &QTimer::timeout, gameboyScreen, &GbmuScreen::updateGbScreen);
    timerScreen->start(17);

	//Setting Controller
	QThread* thread = new QThread;
	Worker* worker = new Worker();
	worker->moveToThread(thread);
	// | this connect seems to fail but it is just for debug
	// v
	//connect(worker, SIGNAL (error(QString)), this, SLOT (errorString(QString)));
	connect(thread, SIGNAL (started()), worker, SLOT (process()));
	connect(worker, SIGNAL (finished()), thread, SLOT (quit()));
	connect(worker, SIGNAL (finished()), worker, SLOT (deleteLater()));
	connect(thread, SIGNAL (finished()), thread, SLOT (deleteLater()));
	thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QDesktopServices::openUrl( QUrl::fromLocalFile( "/Users/nbouchin/" ) );
}

void MainWindow::on_actionPlay_triggered()
{
    QMessageBox::information(this, "tit", "Play the game");
}

void MainWindow::on_actionStop_triggered()
{
    QMessageBox::information(this, "tit", "Stop the game");
}

void MainWindow::on_actionMute_triggered()
{
    QMessageBox::information(this, "tit", "Mute the game");
}

void MainWindow::on_actionDebug_triggered()
{
	g_gameboy.get_debugger().toggle();
    DebuggerWindow debuggerwindow;
    debuggerwindow.setModal(true);
    debuggerwindow.exec();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	mutexGb.lock();
	switch (event->key())
	{
		case Qt::Key_W:
			std::cout << "I PRESSED W (UP)" << std::endl;
			g_gameboy.handle_input_wraper(0xEB);
			break;
		case Qt::Key_S:
			std::cout << "I PRESSED S (UP)" << std::endl;
			g_gameboy.handle_input_wraper(0xE7);
			break;
		case Qt::Key_A:
			std::cout << "I PRESSED A (UP)" << std::endl;
			g_gameboy.handle_input_wraper(0xED);
			break;
		case Qt::Key_D:
			std::cout << "I PRESSED D (UP)" << std::endl;
			g_gameboy.handle_input_wraper(0xEE);
			break;
		case Qt::Key_J:
			std::cout << "I PRESSED J (UP)" << std::endl;
			g_gameboy.handle_input_wraper(0xDE);
			break;
		case Qt::Key_K:
			std::cout << "I PRESSED K (UP)" << std::endl;
			g_gameboy.handle_input_wraper(0xDD);
			break;
		case Qt::Key_N:
			std::cout << "I PRESSED N (UP)" << std::endl;
			g_gameboy.handle_input_wraper(0xD7);
			break;
		case Qt::Key_M:
			std::cout << "I PRESSED M (UP)" << std::endl;
			g_gameboy.handle_input_wraper(0xDB);
			break;
	}
	mutexGb.unlock();
}
