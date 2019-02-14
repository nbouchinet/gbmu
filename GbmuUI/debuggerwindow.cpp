#include "debuggerwindow.h"
#include "ui_debuggerwindow.h"

DebuggerWindow::DebuggerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebuggerWindow)
{
    ui->setupUi(this);


	ui->registersWidget->setColumnCount(1);
	QStringList titles;
	titles << "Value";
	ui->registersWidget->setHorizontalHeaderLabels(titles);

	ui->registersWidget->setRowCount(6);
	QStringList verticalLabels;
	verticalLabels << "PC" << "AF" << "BC" << "DE" << "HL" << "SP";
	ui->registersWidget->setVerticalHeaderLabels(verticalLabels);
	ui->registersWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->registersWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

DebuggerWindow::~DebuggerWindow()
{
    delete ui;
}

void DebuggerWindow::on_stepButton_clicked()
{
	ui->registersWidget->insertRow(ui->registersWidget->rowCount());
	ui->registersWidget->setItem(0, 0, new QTableWidgetItem(QString::number(5)));
	ui->registersWidget->setItem(0, 1, new QTableWidgetItem(QString::number(9)));
}
