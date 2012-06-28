/********************************************************************************
** Form generated from reading UI file 'crftagrobot.ui'
**
** Created: Wed Jun 27 17:06:32 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRFTAGROBOT_H
#define UI_CRFTAGROBOT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "stage.h"

QT_BEGIN_NAMESPACE

class Ui_CRFTagRobot
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    Stage *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CRFTagRobot)
    {
        if (CRFTagRobot->objectName().isEmpty())
            CRFTagRobot->setObjectName(QString::fromUtf8("CRFTagRobot"));
        CRFTagRobot->resize(812, 588);
        centralWidget = new QWidget(CRFTagRobot);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        graphicsView = new Stage(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 2);

        CRFTagRobot->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CRFTagRobot);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 812, 21));
        CRFTagRobot->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CRFTagRobot);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CRFTagRobot->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CRFTagRobot);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CRFTagRobot->setStatusBar(statusBar);

        retranslateUi(CRFTagRobot);

        QMetaObject::connectSlotsByName(CRFTagRobot);
    } // setupUi

    void retranslateUi(QMainWindow *CRFTagRobot)
    {
        CRFTagRobot->setWindowTitle(QApplication::translate("CRFTagRobot", "CRFTagRobot", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CRFTagRobot: public Ui_CRFTagRobot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRFTAGROBOT_H
