#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsocket.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonIP_clicked()
{
    //设置IP

}

void MainWindow::on_pushButtonPort_clicked()
{
    //设置port

}

void MainWindow::on_pushButtonPath_clicked()
{
    //设置路径
    std::string path = ui->lineEditPath->text().toStdString();
    Jsocket::setHomePath(path);
}
