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

class Ui_DebuggerWindow
{
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

    void setupUi(QDialog *DebuggerWindow)
    {
        if (DebuggerWindow->objectName().isEmpty())
            DebuggerWindow->setObjectName(QStringLiteral("DebuggerWindow"));
        DebuggerWindow->resize(1200, 600);
        DebuggerWindow->setMinimumSize(QSize(1200, 600));
        DebuggerWindow->setMaximumSize(QSize(1200, 600));
        resetButton = new QPushButton(DebuggerWindow);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(0, 0, 114, 32));
        stepButton = new QPushButton(DebuggerWindow);
        stepButton->setObjectName(QStringLiteral("stepButton"));
        stepButton->setGeometry(QRect(110, 0, 114, 32));
        runOneFrameButton = new QPushButton(DebuggerWindow);
        runOneFrameButton->setObjectName(QStringLiteral("runOneFrameButton"));
        runOneFrameButton->setGeometry(QRect(220, 0, 121, 32));
        runDurationButton = new QPushButton(DebuggerWindow);
        runDurationButton->setObjectName(QStringLiteral("runDurationButton"));
        runDurationButton->setGeometry(QRect(340, 0, 131, 32));
        memoryLineEdit = new QLineEdit(DebuggerWindow);
        memoryLineEdit->setObjectName(QStringLiteral("memoryLineEdit"));
        memoryLineEdit->setGeometry(QRect(70, 250, 113, 21));
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
        disassemblerWidget = new QTableWidget(DebuggerWindow);
        disassemblerWidget->setObjectName(QStringLiteral("disassemblerWidget"));
        disassemblerWidget->setGeometry(QRect(110, 50, 471, 192));
        registersWidget = new QTableWidget(DebuggerWindow);
        registersWidget->setObjectName(QStringLiteral("registersWidget"));
        registersWidget->setGeometry(QRect(10, 50, 91, 192));
        videoRegistersWidget = new QTableWidget(DebuggerWindow);
        videoRegistersWidget->setObjectName(QStringLiteral("videoRegistersWidget"));
        videoRegistersWidget->setGeometry(QRect(600, 50, 141, 541));
        otherRegistersWidget = new QTableWidget(DebuggerWindow);
        otherRegistersWidget->setObjectName(QStringLiteral("otherRegistersWidget"));
        otherRegistersWidget->setGeometry(QRect(760, 50, 151, 541));
        breakpointsWidget = new QListWidget(DebuggerWindow);
        breakpointsWidget->setObjectName(QStringLiteral("breakpointsWidget"));
        breakpointsWidget->setGeometry(QRect(930, 50, 101, 431));
        breakpointsEdit = new QLineEdit(DebuggerWindow);
        breakpointsEdit->setObjectName(QStringLiteral("breakpointsEdit"));
        breakpointsEdit->setGeometry(QRect(930, 490, 101, 21));
        addBreakpointButton = new QPushButton(DebuggerWindow);
        addBreakpointButton->setObjectName(QStringLiteral("addBreakpointButton"));
        addBreakpointButton->setGeometry(QRect(920, 520, 121, 32));
        deleteBreakpointButton = new QPushButton(DebuggerWindow);
        deleteBreakpointButton->setObjectName(QStringLiteral("deleteBreakpointButton"));
        deleteBreakpointButton->setGeometry(QRect(920, 550, 121, 31));
        breakpointsLabel = new QLabel(DebuggerWindow);
        breakpointsLabel->setObjectName(QStringLiteral("breakpointsLabel"));
        breakpointsLabel->setGeometry(QRect(930, 30, 81, 16));
        runDurationSpinBox = new QSpinBox(DebuggerWindow);
        runDurationSpinBox->setObjectName(QStringLiteral("runDurationSpinBox"));
        runDurationSpinBox->setGeometry(QRect(470, 0, 41, 31));
        watchpointsWidget = new QListWidget(DebuggerWindow);
        watchpointsWidget->setObjectName(QStringLiteral("watchpointsWidget"));
        watchpointsWidget->setGeometry(QRect(1050, 50, 131, 431));
        wathpointsLabel = new QLabel(DebuggerWindow);
        wathpointsLabel->setObjectName(QStringLiteral("wathpointsLabel"));
        wathpointsLabel->setGeometry(QRect(1050, 30, 81, 16));
        deleteWatchpointButton = new QPushButton(DebuggerWindow);
        deleteWatchpointButton->setObjectName(QStringLiteral("deleteWatchpointButton"));
        deleteWatchpointButton->setGeometry(QRect(1040, 490, 151, 32));

        retranslateUi(DebuggerWindow);

        QMetaObject::connectSlotsByName(DebuggerWindow);
    } // setupUi

    void retranslateUi(QDialog *DebuggerWindow)
    {
        DebuggerWindow->setWindowTitle(QApplication::translate("DebuggerWindow", "Debugger", nullptr));
        resetButton->setText(QApplication::translate("DebuggerWindow", "Reset", nullptr));
        stepButton->setText(QApplication::translate("DebuggerWindow", "Step", nullptr));
        runOneFrameButton->setText(QApplication::translate("DebuggerWindow", "Run One Frame", nullptr));
        runDurationButton->setText(QApplication::translate("DebuggerWindow", "Run Duration", nullptr));
        memoryLabel->setText(QApplication::translate("DebuggerWindow", "Memory", nullptr));
        registersLabel->setText(QApplication::translate("DebuggerWindow", "Registers", nullptr));
        disassemblerLabel->setText(QApplication::translate("DebuggerWindow", "Disassembler", nullptr));
        videoRegistersLabel->setText(QApplication::translate("DebuggerWindow", "Video Registers", nullptr));
        otherRegisterslabel->setText(QApplication::translate("DebuggerWindow", "Other Registers", nullptr));
        addBreakpointButton->setText(QApplication::translate("DebuggerWindow", "Add", nullptr));
        deleteBreakpointButton->setText(QApplication::translate("DebuggerWindow", "Delete", nullptr));
        breakpointsLabel->setText(QApplication::translate("DebuggerWindow", "Breakpoints", nullptr));
        wathpointsLabel->setText(QApplication::translate("DebuggerWindow", "Watchpoints", nullptr));
        deleteWatchpointButton->setText(QApplication::translate("DebuggerWindow", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DebuggerWindow: public Ui_DebuggerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGGERWINDOW_H
