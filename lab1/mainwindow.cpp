#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "jsocket.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    connect(this,  &MainWindow::textBrowser_append, this, &MainWindow::on_textBrowser_append);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//刷新IP清单
void MainWindow::on_pushButtonIP_clicked()
{
   QString ipQS = ui->comboBoxIP->currentText();
   js->shutdown(); //关闭机器
   js->setIP(ipQS.toStdString());  //修改IP
   js->startup();  //机器重启
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
        QString portQS = QString::number(port);
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
    delete js;
    js = new Jsocket;

    //初始化服务器参数（绑定到此窗口）
    js->reset(this);
    //启动服务器
    js->startup();

    //显示到GUI
    QString ipQS(QString::fromStdString((js->getIP())));
    QString portQS = QString::number(js->getPort());
    QString pathQS(QString::fromStdString((js->getHomePath())));
    ui->textBrowserIP->setText(ipQS);
    ui->textBrowserPort->setText(portQS);
    ui->textBrowserPath->setText(pathQS);

    //初始化IP选择列表
    char host[255];
    //得到主机地址结构信息的指针p
    if (gethostname(host, sizeof(host)) == SOCKET_ERROR)
        tprintf("gethostname() failed\n");
    struct hostent *p = gethostbyname(host);
    if (!p)
        tprintf("gethostbyname() failed\n");
    else
    {
        //清空清单
        ui->comboBoxIP->clear();
        QString ip0QS("0.0.0.0");
        ui->comboBoxIP->addItem(ip0QS);
        //遍历每个可用的IP地址（注意判断地址取完的逻辑）
        for(int i = 0; p->h_addr_list[i] + p->h_length < p->h_name; i++)
        {
            struct in_addr in;
            memcpy(&in, p->h_addr_list[i], sizeof(struct in_addr));
            //在清单添加新条目
            QString ipQS(inet_ntoa(in));
            ui->comboBoxIP->addItem(ipQS);
        }
    }
}

//打印终端调用接口
void MainWindow::tprintf(std::string s)
{
    std::cout << s << std::endl;
    emit textBrowser_append(s);
}

//打印信号槽函数
void MainWindow::on_textBrowser_append(std::string s)
{
    ui->textBrowser->append(QString::fromStdString(s));
}
