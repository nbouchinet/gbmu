#ifndef DEBUGGERWINDOW_H
#define DEBUGGERWINDOW_H

#include <QDialog>

namespace Ui {
class DebuggerWindow;
}

class DebuggerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DebuggerWindow(QWidget *parent = nullptr);
    ~DebuggerWindow();

private slots:
    void on_stepButton_clicked();

private:
    Ui::DebuggerWindow *ui;
};

#endif // DEBUGGERWINDOW_H
