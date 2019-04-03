/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
 public:
  QAction *actionOpen;
  QAction *actionPlay;
  QAction *actionStop;
  QAction *actionMute;
  QAction *actionDebug;
  QAction *actionSave;
  QAction *actionSpeed;
  QAction *actionSnapshot;
  QAction *actionLoad_Snapshot;
  QAction *actionDefault;
  QAction *actionDMG;
  QAction *actionCGB;
  QWidget *centralWidget;
  QVBoxLayout *verticalLayout;
  QMenuBar *menuBar;
  QMenu *menuFile;
  QMenu *menuAction;
  QMenu *menuHelp;
  QMenu *menuModel;
  QToolBar *mainToolBar;

  void setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName(QStringLiteral("MainWindow"));
    MainWindow->resize(400, 300);
    MainWindow->setMinimumSize(QSize(160, 172));
    actionOpen = new QAction(MainWindow);
    actionOpen->setObjectName(QStringLiteral("actionOpen"));
    actionOpen->setCheckable(false);
    actionOpen->setChecked(false);
    actionOpen->setEnabled(true);
    QIcon icon;
    icon.addFile(QStringLiteral(":/resources/open.png"), QSize(), QIcon::Normal,
                 QIcon::Off);
    actionOpen->setIcon(icon);
    actionPlay = new QAction(MainWindow);
    actionPlay->setObjectName(QStringLiteral("actionPlay"));
    actionPlay->setEnabled(false);
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/resources/pause.png"), QSize(),
                  QIcon::Normal, QIcon::Off);
    actionPlay->setIcon(icon1);
    actionStop = new QAction(MainWindow);
    actionStop->setObjectName(QStringLiteral("actionStop"));
    actionStop->setEnabled(false);
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/resources/stop.png"), QSize(),
                  QIcon::Normal, QIcon::Off);
    actionStop->setIcon(icon2);
    actionMute = new QAction(MainWindow);
    actionMute->setObjectName(QStringLiteral("actionMute"));
    actionMute->setEnabled(false);
    QIcon icon3;
    icon3.addFile(QStringLiteral(":/resources/sound.png"), QSize(),
                  QIcon::Normal, QIcon::Off);
    actionMute->setIcon(icon3);
    actionDebug = new QAction(MainWindow);
    actionDebug->setObjectName(QStringLiteral("actionDebug"));
    actionDebug->setEnabled(false);
    QIcon icon4;
    icon4.addFile(QStringLiteral(":/resources/bug.png"), QSize(), QIcon::Normal,
                  QIcon::Off);
    actionDebug->setIcon(icon4);
    actionSave = new QAction(MainWindow);
    actionSave->setObjectName(QStringLiteral("actionSave"));
    actionSave->setEnabled(false);
    QIcon icon5;
    icon5.addFile(QStringLiteral(":/resources/save.png"), QSize(),
                  QIcon::Normal, QIcon::Off);
    actionSave->setIcon(icon5);
    actionSpeed = new QAction(MainWindow);
    actionSpeed->setObjectName(QStringLiteral("actionSpeed"));
    actionSpeed->setEnabled(false);
    QIcon icon6;
    icon6.addFile(QStringLiteral(":/resources/speed.png"), QSize(),
                  QIcon::Normal, QIcon::Off);
    actionSpeed->setIcon(icon6);
    actionSnapshot = new QAction(MainWindow);
    actionSnapshot->setObjectName(QStringLiteral("actionSnapshot"));
    actionSnapshot->setEnabled(false);
    QIcon icon7;
    icon7.addFile(QStringLiteral(":/resources/create_snapshot.png"), QSize(),
                  QIcon::Normal, QIcon::Off);
    actionSnapshot->setIcon(icon7);
    actionLoad_Snapshot = new QAction(MainWindow);
    actionLoad_Snapshot->setObjectName(QStringLiteral("actionLoad_Snapshot"));
    actionLoad_Snapshot->setEnabled(false);
    QIcon icon8;
    icon8.addFile(QStringLiteral(":/resources/load_snapshot.png"), QSize(),
                  QIcon::Normal, QIcon::Off);
    actionLoad_Snapshot->setIcon(icon8);
    actionDefault = new QAction(MainWindow);
    actionDefault->setObjectName(QStringLiteral("actionDefault"));
    actionDefault->setCheckable(true);
    actionDefault->setChecked(true);
    actionDMG = new QAction(MainWindow);
    actionDMG->setObjectName(QStringLiteral("actionDMG"));
    actionDMG->setCheckable(true);
    actionCGB = new QAction(MainWindow);
    actionCGB->setObjectName(QStringLiteral("actionCGB"));
    actionCGB->setCheckable(true);
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    verticalLayout = new QVBoxLayout(centralWidget);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    MainWindow->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(MainWindow);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 400, 22));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QStringLiteral("menuFile"));
    menuAction = new QMenu(menuBar);
    menuAction->setObjectName(QStringLiteral("menuAction"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QStringLiteral("menuHelp"));
    menuModel = new QMenu(menuBar);
    menuModel->setObjectName(QStringLiteral("menuModel"));
    MainWindow->setMenuBar(menuBar);
    mainToolBar = new QToolBar(MainWindow);
    mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    mainToolBar->setEnabled(true);
    mainToolBar->setIconSize(QSize(16, 16));
    MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuAction->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuBar->addAction(menuModel->menuAction());
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSnapshot);
    menuFile->addAction(actionLoad_Snapshot);
    menuAction->addAction(actionPlay);
    menuAction->addAction(actionStop);
    menuAction->addAction(actionMute);
    menuAction->addAction(actionSpeed);
    menuHelp->addAction(actionDebug);
    menuModel->addAction(actionDefault);
    menuModel->addAction(actionDMG);
    menuModel->addAction(actionCGB);
    mainToolBar->addAction(actionOpen);
    mainToolBar->addAction(actionSave);
    mainToolBar->addAction(actionPlay);
    mainToolBar->addAction(actionStop);
    mainToolBar->addAction(actionMute);
    mainToolBar->addAction(actionDebug);
    mainToolBar->addAction(actionSpeed);
    mainToolBar->addAction(actionSnapshot);
    mainToolBar->addAction(actionLoad_Snapshot);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
  }  // setupUi

  void retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(
        QApplication::translate("MainWindow", "Gbmu", nullptr));
    actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
#ifndef QT_NO_SHORTCUT
    actionOpen->setShortcut(
        QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif  // QT_NO_SHORTCUT
    actionPlay->setText(QApplication::translate("MainWindow", "Play", nullptr));
#ifndef QT_NO_SHORTCUT
    actionPlay->setShortcut(
        QApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif  // QT_NO_SHORTCUT
    actionStop->setText(QApplication::translate("MainWindow", "Stop", nullptr));
#ifndef QT_NO_SHORTCUT
    actionStop->setShortcut(
        QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif  // QT_NO_SHORTCUT
    actionMute->setText(QApplication::translate("MainWindow", "Mute", nullptr));
#ifndef QT_NO_SHORTCUT
    actionMute->setShortcut(
        QApplication::translate("MainWindow", "Ctrl+M", nullptr));
#endif  // QT_NO_SHORTCUT
    actionDebug->setText(
        QApplication::translate("MainWindow", "Debug", nullptr));
#ifndef QT_NO_SHORTCUT
    actionDebug->setShortcut(
        QApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif  // QT_NO_SHORTCUT
    actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
    actionSpeed->setText(
        QApplication::translate("MainWindow", "Speed", nullptr));
    actionSnapshot->setText(
        QApplication::translate("MainWindow", "Snapshot", nullptr));
    actionLoad_Snapshot->setText(
        QApplication::translate("MainWindow", "Load Snapshot", nullptr));
    actionDefault->setText(
        QApplication::translate("MainWindow", "Default", nullptr));
    actionDMG->setText(QApplication::translate("MainWindow", "DMG", nullptr));
    actionCGB->setText(QApplication::translate("MainWindow", "CGB", nullptr));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    menuAction->setTitle(
        QApplication::translate("MainWindow", "Action", nullptr));
    menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    menuModel->setTitle(
        QApplication::translate("MainWindow", "Model", nullptr));
  }  // retranslateUi
};

namespace Ui {
class MainWindow : public Ui_MainWindow {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_MAINWINDOW_H
