#ifndef DEBUGGERWINDOW_H
#define DEBUGGERWINDOW_H

#include <QDialog>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include <QListWidget>

#define MAIN_REGISTERS_BEGIN 0
#define MAIN_REGISTERS_END 5
#define VIDEO_REGISTERS_BEGIN 6
#define VIDEO_REGISTERS_END 21 
#define OTHER_REGISTERS_BEGIN 22
#define OTHER_REGISTERS_END 38

namespace Ui {
class DebuggerWindow;
}

class DebuggerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DebuggerWindow(QWidget *parent = nullptr);
    ~DebuggerWindow();
	void refresh_info();
	void refresh_registers();
	void refresh_instr();
	void refresh_memory_map();
	void addBreakpoint();
	void add_watchpoint(const QString &label, const QString &addrText);
	bool duplicateInListWidgetItem(const QString &value, const QListWidget *list);
	void reset_color(QTableWidget *widget, int column);
	inline QString qstring_hex_pad(uint32_t value, int padding);

private slots:
    void on_stepButton_clicked();
    void on_runOneFrameButton_clicked();
    void on_runDurationButton_clicked();
	void on_addBreakpointButton_clicked();
	void on_breakpointsEdit_editingFinished();
	void on_deleteBreakpointButton_clicked();
	void on_DebuggerWindow_rejected();
	void on_deleteWatchpointButton_clicked();
	void on_memoryLineEdit_editingFinished();

private:
    Ui::DebuggerWindow *ui;
	uint16_t			_addr_memory_map;
};

#endif // DEBUGGERWINDOW_H
