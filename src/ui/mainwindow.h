#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMutex>

#include "src/Gameboy.hpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gbmuscreen.h"
#include "debuggerwindow.h"
#include "worker.h"

class Worker;

namespace Ui {
class MainWindow;
}


extern Gameboy *g_gameboy;
extern QMutex mutexGb;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionStop_triggered();

    void on_actionMute_triggered();

    void on_actionDebug_triggered();
    
private:
    Ui::MainWindow *ui;
	QString			_rom_path;
	QThread			*_gameboy_thread = nullptr;
	Worker			*_gameboy_worker = nullptr;
	QTimer			*_timer_screen = nullptr;
	GbmuScreen		*_gameboy_screen = nullptr;
	QIcon			_pause_icon;
	QIcon			_play_icon;


	//Key Event function
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void pause_gameboy(bool stop = false);
};

#endif // MAINWINDOW_H
