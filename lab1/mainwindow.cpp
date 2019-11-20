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

//刷新IP清单
void MainWindow::on_pushButtonIP_clicked()
{
    char host[255];
    //得到主机地址结构信息的指针p
    if (gethostname(host, sizeof(host)) == SOCKET_ERROR)
        std::cout << "gethostname() failed" << std::endl;
    struct hostent *p = gethostbyname(host);
    if (!p)
        std::cout << "gethostbyname() failed" << std::endl;
    else
    {
        //清空清单
        ui->comboBoxIP->clear();
        //遍历每个可用的IP地址
        for(int i = 0; p->h_addr_list + i != nullptr; i++)
        {
            struct in_addr in;
            memcpy(&in, p->h_addr_list[i], sizeof(struct in_addr));
            //在清单添加新条目
            QString ipQS(inet_ntoa(in));
            ui->comboBoxIP->addItem(ipQS);
        }
    }
}

//选择特定IP
void MainWindow::on_comboBoxIP_currentIndexChanged(const QString &ipQS)
{
    std::string ip = ipQS.toStdString();
    //修改ip
    js->setIP(ip);
    //显示当前IP
    ui->textBrowserIP->setText(ipQS);
}

//设置port
void MainWindow::on_pushButtonPort_clicked()
{
    int port = ui->lineEditPort->text().toInt();
    //检查端口范围
    if(port > 0 && port < 65536)
    {
        //关闭机器
        js->shutdown();
        //修改端口重启
        js->startup();
        //显示当前端口
        QString portQS(port);
        ui->textBrowserPort->setText(portQS);
    }
}

//设置路径
void MainWindow::on_pushButtonPath_clicked()
{
    QString pathQS = ui->lineEditPath->text();
    std::string path = pathQS.toStdString();
    //修改虚拟路径
    js->setHomePath(path);
    //显示当前虚拟路径
    ui->textBrowserPath->setText(pathQS);
}

//重启服务器
void MainWindow::on_pushButtonReset_clicked()
{
    //清空服务器对象
    if(js) js->shutdown();
    printf("on_pushButtonReset_clicked() shutdown\n");  //调试
    delete js;
    js = new Jsocket;
    //初始化服务器
    js->reset();
    //显示到GUI
    QString ipQS(QString::fromStdString((js->getIP())));
    QString portQS(js->getPort());
    QString pathQS(QString::fromStdString((js->getHomePath())));
    ui->textBrowserIP->setText(ipQS);
    ui->textBrowserPort->setText(portQS);
    ui->textBrowserPath->setText(pathQS);
}
