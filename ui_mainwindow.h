/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue 19. Apr 17:31:26 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewTask;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        MainWindow->setStyleSheet(QString::fromUtf8(" QMainWindow::separator {\n"
"     background: darkgrey;\n"
"     width: 1px; /* when vertical */\n"
"     height: 1px; /* when horizontal */\n"
" }\n"
"\n"
""));
        actionNewTask = new QAction(MainWindow);
        actionNewTask->setObjectName(QString::fromUtf8("actionNewTask"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMaximumSize(QSize(1, 16777215));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QString::fromUtf8("menuDatei"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setAllowedAreas(Qt::LeftToolBarArea);
        mainToolBar->setIconSize(QSize(48, 48));
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::LeftToolBarArea, mainToolBar);

        menuBar->addAction(menuDatei->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Kantalupe Editor", 0, QApplication::UnicodeUTF8));
        actionNewTask->setText(QApplication::translate("MainWindow", "New Task", 0, QApplication::UnicodeUTF8));
        menuDatei->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
