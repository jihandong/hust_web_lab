/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonIP;
    QPushButton *pushButtonPort;
    QPushButton *pushButtonPath;
    QLineEdit *lineEditPath;
    QLineEdit *lineEditPort;
    QLineEdit *lineEditIP;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButtonIP = new QPushButton(centralwidget);
        pushButtonIP->setObjectName(QString::fromUtf8("pushButtonIP"));
        pushButtonIP->setGeometry(QRect(70, 70, 121, 41));
        pushButtonPort = new QPushButton(centralwidget);
        pushButtonPort->setObjectName(QString::fromUtf8("pushButtonPort"));
        pushButtonPort->setGeometry(QRect(70, 120, 121, 41));
        pushButtonPath = new QPushButton(centralwidget);
        pushButtonPath->setObjectName(QString::fromUtf8("pushButtonPath"));
        pushButtonPath->setGeometry(QRect(70, 170, 121, 41));
        lineEditPath = new QLineEdit(centralwidget);
        lineEditPath->setObjectName(QString::fromUtf8("lineEditPath"));
        lineEditPath->setGeometry(QRect(200, 170, 441, 41));
        lineEditPort = new QLineEdit(centralwidget);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));
        lineEditPort->setGeometry(QRect(200, 120, 441, 41));
        lineEditIP = new QLineEdit(centralwidget);
        lineEditIP->setObjectName(QString::fromUtf8("lineEditIP"));
        lineEditIP->setGeometry(QRect(200, 70, 431, 41));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(70, 220, 571, 201));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButtonIP->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        pushButtonPort->setText(QCoreApplication::translate("MainWindow", "port", nullptr));
        pushButtonPath->setText(QCoreApplication::translate("MainWindow", "path", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
