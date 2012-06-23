/********************************************************************************
** Form generated from reading UI file 'crftagrobot.ui'
**
** Created: Sat Jun 23 12:51:05 2012
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
#include <QtGui/QPushButton>
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
    QPushButton *btnStartSimulation;
    QPushButton *btnStopSimulation;
    QPushButton *btnRecordSimulation;
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

        gridLayout->addWidget(graphicsView, 0, 0, 1, 3);

        btnStartSimulation = new QPushButton(centralWidget);
        btnStartSimulation->setObjectName(QString::fromUtf8("btnStartSimulation"));

        gridLayout->addWidget(btnStartSimulation, 1, 0, 1, 1);

        btnStopSimulation = new QPushButton(centralWidget);
        btnStopSimulation->setObjectName(QString::fromUtf8("btnStopSimulation"));

        gridLayout->addWidget(btnStopSimulation, 1, 1, 1, 1);

        btnRecordSimulation = new QPushButton(centralWidget);
        btnRecordSimulation->setObjectName(QString::fromUtf8("btnRecordSimulation"));

        gridLayout->addWidget(btnRecordSimulation, 1, 2, 1, 1);

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
        btnStartSimulation->setText(QApplication::translate("CRFTagRobot", "&Start", 0, QApplication::UnicodeUTF8));
        btnStopSimulation->setText(QApplication::translate("CRFTagRobot", "&Stop", 0, QApplication::UnicodeUTF8));
        btnRecordSimulation->setText(QApplication::translate("CRFTagRobot", "&Record", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CRFTagRobot: public Ui_CRFTagRobot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRFTAGROBOT_H
