#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "jsocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//前置声明
class Jsocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void textBrowser_append(QString s);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Jsocket* js;                //保存服务器的指针
    void tprintf(std::string);  //打印接口

private slots:
    void on_textBrowser_append(QString s);

    void on_pushButtonIP_clicked();

    void on_pushButtonPort_clicked();

    void on_pushButtonPath_clicked();

    void on_pushButtonReset_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
