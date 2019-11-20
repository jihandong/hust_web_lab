#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "jsocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Jsocket* js;  //保存服务器的指针
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonIP_clicked();

    void on_pushButtonPort_clicked();

    void on_pushButtonPath_clicked();

    void on_pushButtonReset_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
