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
#include <QtWidgets/QComboBox>
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
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowserPath;
    QTextBrowser *textBrowserPort;
    QTextBrowser *textBrowserIP;
    QPushButton *pushButtonReset;
    QComboBox *comboBoxIP;
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
        pushButtonIP->setGeometry(QRect(20, 70, 121, 41));
        pushButtonPort = new QPushButton(centralwidget);
        pushButtonPort->setObjectName(QString::fromUtf8("pushButtonPort"));
        pushButtonPort->setGeometry(QRect(20, 120, 121, 41));
        pushButtonPath = new QPushButton(centralwidget);
        pushButtonPath->setObjectName(QString::fromUtf8("pushButtonPath"));
        pushButtonPath->setGeometry(QRect(20, 170, 121, 41));
        lineEditPath = new QLineEdit(centralwidget);
        lineEditPath->setObjectName(QString::fromUtf8("lineEditPath"));
        lineEditPath->setGeometry(QRect(150, 170, 271, 41));
        lineEditPort = new QLineEdit(centralwidget);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));
        lineEditPort->setGeometry(QRect(150, 120, 271, 41));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 220, 681, 201));
        textBrowserPath = new QTextBrowser(centralwidget);
        textBrowserPath->setObjectName(QString::fromUtf8("textBrowserPath"));
        textBrowserPath->setGeometry(QRect(430, 170, 271, 41));
        textBrowserPort = new QTextBrowser(centralwidget);
        textBrowserPort->setObjectName(QString::fromUtf8("textBrowserPort"));
        textBrowserPort->setGeometry(QRect(430, 120, 271, 41));
        textBrowserIP = new QTextBrowser(centralwidget);
        textBrowserIP->setObjectName(QString::fromUtf8("textBrowserIP"));
        textBrowserIP->setGeometry(QRect(430, 70, 271, 41));
        pushButtonReset = new QPushButton(centralwidget);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));
        pushButtonReset->setGeometry(QRect(20, 20, 121, 41));
        comboBoxIP = new QComboBox(centralwidget);
        comboBoxIP->setObjectName(QString::fromUtf8("comboBoxIP"));
        comboBoxIP->setGeometry(QRect(150, 70, 271, 41));
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
        pushButtonIP->setText(QCoreApplication::translate("MainWindow", "update IP list", nullptr));
        pushButtonPort->setText(QCoreApplication::translate("MainWindow", "change port", nullptr));
        pushButtonPath->setText(QCoreApplication::translate("MainWindow", "change homepath", nullptr));
        pushButtonReset->setText(QCoreApplication::translate("MainWindow", "reset server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
