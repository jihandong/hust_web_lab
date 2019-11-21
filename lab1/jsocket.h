#ifndef JSOCKET_H
#define JSOCKET_H
#include<cstdio>
#include<iostream>
#include<fstream>
#include<string>
#include<thread>
#include<exception>
#include<winsock2.h>
#include<windows.h>
#include"mainwindow.h"

#pragma comment(lib, "Ws2_32.lib")

#define BUFSIZE 1024*8
#define ERROR404HTML "error404.html"    

//前置声明
class MainWindow;

class Jsocket
{
    static bool servState;          //服务器状态
    static std::thread* servThread; //服务器线程地址
    static SOCKET servSocket;       //服务器套接字
    static u_long servIP;           //服务器IP
    static int servPort;            //服务器port
    static std::string homePath;    //虚拟路径
    static int connNum;             //连接数量
    static int connNumMax;          //最大连接数量
    static MainWindow* wd;          //窗口指针

public:
    static void startup();                      //服务器启动
    static void shutdown();                     //服务器关闭
    static bool inservive();                    //服务器运行中
    static void reset(MainWindow* w);           //服务器重置
    static void setIP(std::string s);           //设置服务器IP
    static void setPort(int p);                 //设置服务器port
    static void setHomePath(std::string s);     //设置虚拟路径
    static std::string getIP();                 //访问服务器IP
    static int         getPort();               //访问服务器port
    static std::string getHomePath();           //访问虚拟路径
    static bool winsockStartup();               //初始化winsock
    static bool bindStartup();                  //创建并绑定一个监听socket
    static bool listenStarup();                 //监听socket等待连接
    static bool acceptStartup();                //开始对连接多线程生成会话socket
    static bool handlerThreadStartup(SOCKET s); //启动会话子线程
    static void handlerThread(SOCKET s);        //会话子线程

private:
    static std::string requestObjectPath(std::string buf);   //解析请求对象路径
    static void sendObject(SOCKET s, std::string p);        //发送对象到会话socket
    static int getContentLength(std::string s);            //得到文件长度
    static void showRequest(SOCKET s, std::string p);       //打印请求信息
    static void tprintf(std::string s);                     //打印信息到绑定窗口终端
};

#endif // JSOCKET_H
