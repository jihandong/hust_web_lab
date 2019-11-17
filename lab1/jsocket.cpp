#include "jsocket.h"

//设置服务器socket
void Jsocket::setServerSocket(SOCKET s)
{
    servSocket = s;
}

//设置最大连接数量
void Jsocket::setConnectNumMax(int n)
{
    if(n < 0)
    {
        std::cout << "setConnectNumMax() error negative number" << std::endl;
    }
    connNumMax= n;
}

//设置虚拟路径
void Jsocket::setPath(std::string s)
{
    path = s;
}

//初始化winsock
bool Jsocket::winsockStartup()
{
    WSADATA  wsaData;
    int nRc = WSAStartup(0x0101, &wsaData);
    if(nRc)
    {
        //Winsock初始化错误
        std::cout << "winsockStarup() error" << std::endl;
        return true;
    }
    if(wsaData.wVersion != 0x0101)
    {
        //版本支持不够
        std::cout << "winsockStarup() low version" << std::endl;
        WSACleanup();
        return false;
    }
    return true;
}

//创建并绑定一个监听socket
bool Jsocket::bindStartup(u_short port)
{
    //初始化服务器socket
    servSocket = socket(AF_INET, SOCK_STREAM, 0);
    //设置addr
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);    //u_short->网络字节顺序
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    //尝试绑定
    if(bind(servSocket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        //绑定错误
        int nRc = WSAGetLastError();
        std::cout << "bindStarup() error " << nRc << std::endl;
        return false;
    }
    return true;
}

//监听socket等待连接
bool Jsocket::listenStarup()
{
    if (listen(servSocket, 2) == SOCKET_ERROR)
    {
        //监听错误
        int nRc = WSAGetLastError();
        std::cout << "listenStartup() error " << nRc << std::endl;
        return false;
    }
    return true;
}

//开始对连接多线程生成会话socket
bool Jsocket::acceptStartup(u_short port)
{
    //创建并绑定一个监听socket
    if(bindStartup(port) == false)
    {
        //绑定错误
        std::cout << "acceptStartup() bind error" << std::endl;
        return false;
    }

    //监听socket等待连接
    if(listenStarup() == false)
    {
        //监听错误
        std::cout << "acceptStartup() listen error" << std::endl;
        return false;
    }

    //不断响应客户端连接请求
    SOCKET connSock;                    //会话socket
    sockaddr_in connAddr;               //
    int connAddrLen = sizeof(SOCKADDR); //
    int nRc;                            //错误信息
    while(true){
        //每当收到客户端连接请求，创建新的会话SOCKET
        connSock = accept(servSocket, (SOCKADDR*)&connAddr, &connAddrLen);
        if(connSock == INVALID_SOCKET)
        {
            //创建会话socket出错
            nRc = WSAGetLastError();
            std::cout << "acceptStartup() error invalid socket " << nRc << std::endl;
        }
        else
        {
            //启动新线程与客户端会话
            handlerThreadStartup(connSock);
        }
    }
}

//启动会话子线程
bool Jsocket::handlerThreadStartup(SOCKET s)
{
    connNum++;
    std::thread t(handlerThread, s); //创建会话子线程
    t.detach();                      //发射会话子线程
    return true;
}

//会话子线程
void Jsocket::handlerThread(SOCKET clientSock)
{

    while(true)
    {
        //尝试接收消息

        if()
        {
            //发送结束
            break;
        }

        //消息处理

    }
    //关闭会话子线程
    closesocket(clientSock);
    connNum--;
}
