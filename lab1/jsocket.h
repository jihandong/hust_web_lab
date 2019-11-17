#ifndef JSOCKET_H
#define JSOCKET_H
#include<cstdio>
#include<iostream>
#include<string>
#include<thread>
#include<WinSock2.h>
#include<Windows.h>

class Jsocket
{
    static SOCKET servSocket; //服务器套接字
    static int connNum;      //连接数量
    static int connNumMax;   //最大连接数量
    static std::string path;    //虚拟路径
public:
    static void setServerSocket(SOCKET s);      //设置服务器socket
    static void setConnectNumMax(int n);        //设置最大连接数量
    static void setPath(std::string s);         //设置虚拟路径
    static bool winsockStartup();               //初始化winsock
    static bool bindStartup(u_short port);      //创建并绑定一个监听socket
    static bool listenStarup();                 //监听socket等待连接
    static bool acceptStartup(u_short port);    //开始对连接多线程生成会话socket
    static bool handlerThreadStartup(SOCKET s); //启动会话子线程
    static void handlerThread(SOCKET s);        //会话子线程
private:

};

#endif // JSOCKET_H
