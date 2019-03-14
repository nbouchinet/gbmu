#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gbmuscreen.h"
#include "debuggerwindow.h"
#include "worker.h"

#include <QFileDialog>
#include <QUrl>
#include <QMessageBox>
#include <QTimer>
#include <QKeyEvent>
#include <QThread>
#include <QGraphicsPixmapItem>

Gameboy *g_gameboy = nullptr;
QMutex mutexGb;

#include <iostream>
#include <unistd.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	//Load icon
	_pause_icon = QIcon(":resources/resources/pause.png");
	_play_icon = QIcon(":resources/resources/play.png");

	//Shortcut settings
	ui->actionOpen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
	ui->actionPlay->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
	ui->actionStop->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	ui->actionMute->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
	ui->actionDebug->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
	_rom_path = QFileDialog::getOpenFileName(this, tr("Open ROM"), "/home", tr("*.gb *.gbc"));
	if (_rom_path.isEmpty())
		return ;
	if (g_gameboy && _gameboy_thread && _gameboy_worker && _timer_screen && _gameboy_screen)
	{
		g_gameboy->set_is_abort(true);
		_gameboy_thread->quit();
		_gameboy_thread->wait();
		_gameboy_worker->deleteLater();
		_gameboy_thread->deleteLater();
		_timer_screen->deleteLater();
		delete _gameboy_screen;
		delete g_gameboy;
		g_gameboy = nullptr;
	}
	g_gameboy = new Gameboy(_rom_path.toUtf8().constData());

	//Setting up gameboy's screen
    _gameboy_screen = new GbmuScreen(this);
    _timer_screen = new QTimer(this);
    connect(_timer_screen, &QTimer::timeout, _gameboy_screen, &GbmuScreen::updateGbScreen);
    _timer_screen->start(17);

	//Setting Controller
	_gameboy_thread = new QThread;
	_gameboy_worker = new Worker();
	_gameboy_worker->moveToThread(_gameboy_thread);
	connect(_gameboy_thread, SIGNAL (started()), _gameboy_worker, SLOT (process()));
	connect(_gameboy_worker, SIGNAL (finished()), _gameboy_thread, SLOT (quit()));
	_gameboy_thread->start();
	setCentralWidget(_gameboy_screen);
}

void MainWindow::pause_gameboy(bool stop)
{
	if (g_gameboy == nullptr)
		return;
	if (!g_gameboy->get_pause() || stop)
	{
		ui->actionPlay->setIcon(_play_icon);
		g_gameboy->set_pause(true);
	}
	else
	{
		ui->actionPlay->setIcon(_pause_icon);
		g_gameboy->set_pause(false);
	}
}

void MainWindow::on_actionPlay_triggered()
{
	pause_gameboy();
}

void MainWindow::on_actionStop_triggered()
{
	if (g_gameboy)
	{
		g_gameboy->reset();
		pause_gameboy(true);
	}
}

void MainWindow::on_actionMute_triggered()
{
    QMessageBox::information(this, "tit", "Mute the game");
}

void MainWindow::on_actionDebug_triggered()
{
	if (g_gameboy)
	{
		g_gameboy->get_debugger().toggle();
		DebuggerWindow debuggerwindow;
		debuggerwindow.setModal(true);
		debuggerwindow.exec();
	}
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	mutexGb.lock();
	switch (event->key())
	{
		case Qt::Key_W:
			std::cout << "I PRESSED W (UP)" << std::endl;
			g_gameboy->handle_input_wraper(0xEB);
			break;
		case Qt::Key_S:
			std::cout << "I PRESSED S (DOWN)" << std::endl;
			g_gameboy->handle_input_wraper(0xE7);
			break;
		case Qt::Key_A:
			std::cout << "I PRESSED A (LEFT)" << std::endl;
			g_gameboy->handle_input_wraper(0xED);
			break;
		case Qt::Key_D:
			std::cout << "I PRESSED D (RIGHT)" << std::endl;
			g_gameboy->handle_input_wraper(0xEE);
			break;
		case Qt::Key_J:
			std::cout << "I PRESSED J (A)" << std::endl;
			g_gameboy->handle_input_wraper(0xDE);
			break;
		case Qt::Key_K:
			std::cout << "I PRESSED K (B)" << std::endl;
			g_gameboy->handle_input_wraper(0xDD);
			break;
		case Qt::Key_N:
			std::cout << "I PRESSED N (START)" << std::endl;
			g_gameboy->handle_input_wraper(0xD7);
			break;
		case Qt::Key_M:
			std::cout << "I PRESSED M (SELECT)" << std::endl;
			g_gameboy->handle_input_wraper(0xDB);
			break;
	}
	mutexGb.unlock();
}
