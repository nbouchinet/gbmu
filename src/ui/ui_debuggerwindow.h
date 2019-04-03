/********************************************************************************
** Form generated from reading UI file 'debuggerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGGERWINDOW_H
#define UI_DEBUGGERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DebuggerWindow {
 public:
  QPushButton *resetButton;
  QPushButton *stepButton;
  QPushButton *runOneFrameButton;
  QPushButton *runDurationButton;
  QLineEdit *memoryLineEdit;
  QLabel *memoryLabel;
  QLabel *registersLabel;
  QLabel *disassemblerLabel;
  QLabel *videoRegistersLabel;
  QLabel *otherRegisterslabel;
  QTableWidget *memoryWidget;
  QTableWidget *disassemblerWidget;
  QTableWidget *registersWidget;
  QTableWidget *videoRegistersWidget;
  QTableWidget *otherRegistersWidget;
  QListWidget *breakpointsWidget;
  QLineEdit *breakpointsEdit;
  QPushButton *addBreakpointButton;
  QPushButton *deleteBreakpointButton;
  QLabel *breakpointsLabel;
  QSpinBox *runDurationSpinBox;
  QListWidget *watchpointsWidget;
  QLabel *wathpointsLabel;
  QPushButton *deleteWatchpointButton;
  QLineEdit *watchpointsAddrEdit;
  QPushButton *addWatchpointButton;
  QPushButton *runCpuSecondButton;
  QLineEdit *watchpointsValueEdit;
  QLabel *watchpointsAddrLabel;
  QLabel *watchpointsValueLabel;

  void setupUi(QDialog *DebuggerWindow) {
    if (DebuggerWindow->objectName().isEmpty())
      DebuggerWindow->setObjectName(QStringLiteral("DebuggerWindow"));
    DebuggerWindow->resize(1200, 600);
    DebuggerWindow->setMinimumSize(QSize(1200, 600));
    DebuggerWindow->setMaximumSize(QSize(1200, 600));
    resetButton = new QPushButton(DebuggerWindow);
    resetButton->setObjectName(QStringLiteral("resetButton"));
    resetButton->setGeometry(QRect(0, 0, 114, 32));
    resetButton->setFocusPolicy(Qt::ClickFocus);
    resetButton->setAutoDefault(false);
    stepButton = new QPushButton(DebuggerWindow);
    stepButton->setObjectName(QStringLiteral("stepButton"));
    stepButton->setGeometry(QRect(110, 0, 114, 32));
    stepButton->setFocusPolicy(Qt::NoFocus);
    stepButton->setAutoDefault(false);
    runOneFrameButton = new QPushButton(DebuggerWindow);
    runOneFrameButton->setObjectName(QStringLiteral("runOneFrameButton"));
    runOneFrameButton->setGeometry(QRect(220, 0, 121, 32));
    runOneFrameButton->setFocusPolicy(Qt::ClickFocus);
    runOneFrameButton->setAutoDefault(false);
    runDurationButton = new QPushButton(DebuggerWindow);
    runDurationButton->setObjectName(QStringLiteral("runDurationButton"));
    runDurationButton->setGeometry(QRect(340, 0, 131, 32));
    runDurationButton->setFocusPolicy(Qt::ClickFocus);
    runDurationButton->setAutoDefault(false);
    memoryLineEdit = new QLineEdit(DebuggerWindow);
    memoryLineEdit->setObjectName(QStringLiteral("memoryLineEdit"));
    memoryLineEdit->setGeometry(QRect(70, 250, 113, 21));
    memoryLineEdit->setFocusPolicy(Qt::ClickFocus);
    memoryLabel = new QLabel(DebuggerWindow);
    memoryLabel->setObjectName(QStringLiteral("memoryLabel"));
    memoryLabel->setGeometry(QRect(10, 250, 60, 16));
    registersLabel = new QLabel(DebuggerWindow);
    registersLabel->setObjectName(QStringLiteral("registersLabel"));
    registersLabel->setGeometry(QRect(10, 30, 60, 16));
    disassemblerLabel = new QLabel(DebuggerWindow);
    disassemblerLabel->setObjectName(QStringLiteral("disassemblerLabel"));
    disassemblerLabel->setGeometry(QRect(110, 30, 91, 16));
    videoRegistersLabel = new QLabel(DebuggerWindow);
    videoRegistersLabel->setObjectName(QStringLiteral("videoRegistersLabel"));
    videoRegistersLabel->setGeometry(QRect(600, 30, 101, 16));
    otherRegisterslabel = new QLabel(DebuggerWindow);
    otherRegisterslabel->setObjectName(QStringLiteral("otherRegisterslabel"));
    otherRegisterslabel->setGeometry(QRect(760, 30, 101, 16));
    memoryWidget = new QTableWidget(DebuggerWindow);
    memoryWidget->setObjectName(QStringLiteral("memoryWidget"));
    memoryWidget->setGeometry(QRect(10, 280, 571, 311));
    memoryWidget->setFocusPolicy(Qt::NoFocus);
    disassemblerWidget = new QTableWidget(DebuggerWindow);
    disassemblerWidget->setObjectName(QStringLiteral("disassemblerWidget"));
    disassemblerWidget->setGeometry(QRect(110, 50, 471, 192));
    disassemblerWidget->setFocusPolicy(Qt::NoFocus);
    registersWidget = new QTableWidget(DebuggerWindow);
    registersWidget->setObjectName(QStringLiteral("registersWidget"));
    registersWidget->setGeometry(QRect(10, 50, 91, 192));
    registersWidget->setFocusPolicy(Qt::NoFocus);
    videoRegistersWidget = new QTableWidget(DebuggerWindow);
    videoRegistersWidget->setObjectName(QStringLiteral("videoRegistersWidget"));
    videoRegistersWidget->setGeometry(QRect(600, 50, 141, 541));
    videoRegistersWidget->setFocusPolicy(Qt::NoFocus);
    otherRegistersWidget = new QTableWidget(DebuggerWindow);
    otherRegistersWidget->setObjectName(QStringLiteral("otherRegistersWidget"));
    otherRegistersWidget->setGeometry(QRect(760, 50, 151, 541));
    otherRegistersWidget->setFocusPolicy(Qt::NoFocus);
    breakpointsWidget = new QListWidget(DebuggerWindow);
    breakpointsWidget->setObjectName(QStringLiteral("breakpointsWidget"));
    breakpointsWidget->setGeometry(QRect(930, 50, 101, 431));
    breakpointsWidget->setFocusPolicy(Qt::NoFocus);
    breakpointsEdit = new QLineEdit(DebuggerWindow);
    breakpointsEdit->setObjectName(QStringLiteral("breakpointsEdit"));
    breakpointsEdit->setGeometry(QRect(930, 490, 101, 21));
    breakpointsEdit->setFocusPolicy(Qt::ClickFocus);
    addBreakpointButton = new QPushButton(DebuggerWindow);
    addBreakpointButton->setObjectName(QStringLiteral("addBreakpointButton"));
    addBreakpointButton->setGeometry(QRect(920, 520, 121, 32));
    addBreakpointButton->setFocusPolicy(Qt::ClickFocus);
    addBreakpointButton->setAutoDefault(false);
    deleteBreakpointButton = new QPushButton(DebuggerWindow);
    deleteBreakpointButton->setObjectName(
        QStringLiteral("deleteBreakpointButton"));
    deleteBreakpointButton->setGeometry(QRect(920, 550, 121, 31));
    deleteBreakpointButton->setFocusPolicy(Qt::ClickFocus);
    deleteBreakpointButton->setAutoDefault(false);
    breakpointsLabel = new QLabel(DebuggerWindow);
    breakpointsLabel->setObjectName(QStringLiteral("breakpointsLabel"));
    breakpointsLabel->setGeometry(QRect(930, 30, 81, 16));
    runDurationSpinBox = new QSpinBox(DebuggerWindow);
    runDurationSpinBox->setObjectName(QStringLiteral("runDurationSpinBox"));
    runDurationSpinBox->setGeometry(QRect(470, 0, 41, 31));
    runDurationSpinBox->setFocusPolicy(Qt::ClickFocus);
    watchpointsWidget = new QListWidget(DebuggerWindow);
    watchpointsWidget->setObjectName(QStringLiteral("watchpointsWidget"));
    watchpointsWidget->setGeometry(QRect(1050, 50, 131, 431));
    watchpointsWidget->setFocusPolicy(Qt::NoFocus);
    wathpointsLabel = new QLabel(DebuggerWindow);
    wathpointsLabel->setObjectName(QStringLiteral("wathpointsLabel"));
    wathpointsLabel->setGeometry(QRect(1050, 30, 81, 16));
    deleteWatchpointButton = new QPushButton(DebuggerWindow);
    deleteWatchpointButton->setObjectName(
        QStringLiteral("deleteWatchpointButton"));
    deleteWatchpointButton->setGeometry(QRect(1040, 570, 151, 32));
    deleteWatchpointButton->setFocusPolicy(Qt::ClickFocus);
    deleteWatchpointButton->setAutoDefault(false);
    watchpointsAddrEdit = new QLineEdit(DebuggerWindow);
    watchpointsAddrEdit->setObjectName(QStringLiteral("watchpointsAddrEdit"));
    watchpointsAddrEdit->setGeometry(QRect(1090, 490, 91, 21));
    watchpointsAddrEdit->setFocusPolicy(Qt::ClickFocus);
    addWatchpointButton = new QPushButton(DebuggerWindow);
    addWatchpointButton->setObjectName(QStringLiteral("addWatchpointButton"));
    addWatchpointButton->setGeometry(QRect(1040, 540, 151, 32));
    addWatchpointButton->setAutoDefault(false);
    runCpuSecondButton = new QPushButton(DebuggerWindow);
    runCpuSecondButton->setObjectName(QStringLiteral("runCpuSecondButton"));
    runCpuSecondButton->setGeometry(QRect(520, 0, 141, 32));
    runCpuSecondButton->setAutoDefault(false);
    watchpointsValueEdit = new QLineEdit(DebuggerWindow);
    watchpointsValueEdit->setObjectName(QStringLiteral("watchpointsValueEdit"));
    watchpointsValueEdit->setGeometry(QRect(1090, 520, 91, 21));
    watchpointsValueEdit->setFocusPolicy(Qt::ClickFocus);
    watchpointsAddrLabel = new QLabel(DebuggerWindow);
    watchpointsAddrLabel->setObjectName(QStringLiteral("watchpointsAddrLabel"));
    watchpointsAddrLabel->setGeometry(QRect(1050, 490, 60, 16));
    watchpointsValueLabel = new QLabel(DebuggerWindow);
    watchpointsValueLabel->setObjectName(
        QStringLiteral("watchpointsValueLabel"));
    watchpointsValueLabel->setGeometry(QRect(1050, 520, 60, 16));

    retranslateUi(DebuggerWindow);

    QMetaObject::connectSlotsByName(DebuggerWindow);
  }  // setupUi

  void retranslateUi(QDialog *DebuggerWindow) {
    DebuggerWindow->setWindowTitle(
        QApplication::translate("DebuggerWindow", "Debugger", nullptr));
    resetButton->setText(
        QApplication::translate("DebuggerWindow", "Reset", nullptr));
    stepButton->setText(
        QApplication::translate("DebuggerWindow", "Step", nullptr));
    runOneFrameButton->setText(
        QApplication::translate("DebuggerWindow", "Run One Frame", nullptr));
    runDurationButton->setText(
        QApplication::translate("DebuggerWindow", "Run Duration", nullptr));
    memoryLabel->setText(
        QApplication::translate("DebuggerWindow", "Memory", nullptr));
    registersLabel->setText(
        QApplication::translate("DebuggerWindow", "Registers", nullptr));
    disassemblerLabel->setText(
        QApplication::translate("DebuggerWindow", "Disassembler", nullptr));
    videoRegistersLabel->setText(
        QApplication::translate("DebuggerWindow", "Video Registers", nullptr));
    otherRegisterslabel->setText(
        QApplication::translate("DebuggerWindow", "Other Registers", nullptr));
    addBreakpointButton->setText(
        QApplication::translate("DebuggerWindow", "Add", nullptr));
    deleteBreakpointButton->setText(
        QApplication::translate("DebuggerWindow", "Delete", nullptr));
    breakpointsLabel->setText(
        QApplication::translate("DebuggerWindow", "Breakpoints", nullptr));
    wathpointsLabel->setText(
        QApplication::translate("DebuggerWindow", "Watchpoints", nullptr));
    deleteWatchpointButton->setText(
        QApplication::translate("DebuggerWindow", "Delete", nullptr));
    addWatchpointButton->setText(
        QApplication::translate("DebuggerWindow", "Add", nullptr));
    runCpuSecondButton->setText(
        QApplication::translate("DebuggerWindow", "Run CPU second", nullptr));
    watchpointsAddrLabel->setText(
        QApplication::translate("DebuggerWindow", "Addr:", nullptr));
    watchpointsValueLabel->setText(
        QApplication::translate("DebuggerWindow", "Value:", nullptr));
  }  // retranslateUi
};

namespace Ui {
class DebuggerWindow : public Ui_DebuggerWindow {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_DEBUGGERWINDOW_H
