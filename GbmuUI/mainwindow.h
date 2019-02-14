#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/Gameboy.hpp"

namespace Ui {
class MainWindow;
}


extern Gameboy g_gameboy;
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

	//Key Event function
	void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
