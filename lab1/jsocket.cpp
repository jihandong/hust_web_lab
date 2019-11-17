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
    connNumMax = n;
}

//设置虚拟路径
void Jsocket::setHomePath(std::string s)
{
    homePath = s;
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
void Jsocket::handlerThread(SOCKET connSock)
{
    char buf[BUFSIZE];      //缓冲区
    int length;             //接受长度
    FD_SET set;             //可读性检查socket集合
    timeval tv = {1, 0};    //超时时间
    while(true)
    {
        //清空set
        FD_ZERO(&set);
        FD_SET(connSock, &set);
        //判断是否接受到内容
        if(select(0, &set, NULL, NULL, &tv) == 0)
        {
            //超时无修改
            continue;
        }
        else
        {
            //接受内容至buf
            length = recv(connSock, buf, BUFSIZE, 0);
            if(length < 0)
            {
                //发送错误
                break;
            }
            //处理buf中缓存的请求
            buf[length] = '\0';
            std::cout << "buf:\n" << buf << std::endl;
            std::string objectPath = requestObjectPath(buf);
            showRequest(connSock, objectPath);
            sendObject(connSock, objectPath);
        }
    }
    //关闭会话子线程
    closesocket(connSock);
    connNum--;
}

std::string Jsocket::requestObjectPath(std::string buf)
{
    int pos1, pos2, pos3;
    //pos1寻找"/"的位置
    if((pos1 = buf.find("/", 0)) == std::string::npos)
    {
        //解析失败
        std::cout << "requestObjectPath fail" << std::endl;
        return nullptr;
    }
    //pos2寻找" "的位置
    pos2 = buf.find(" ", pos1);
    //pos3寻找"?"的位置并修正pos2的位置
    if((pos3 = buf.find("?", pos1) != std::string::npos) && pos2 > pos3)
    {
        pos2 = pos3;
    }
    //得到文件路径
    std::string objectName = buf.substr(pos1, pos2 - pos1);
    for(int i = 0; i < objectName.size(); i++)
        if(objectName[i] == '/')
            objectName[i] = '\\';
    std::string objectPath = homePath + objectName;
    return objectPath;
}

void Jsocket::sendObject(SOCKET connSock, std::string objectPath)
{
    char buf[BUFSIZE];  //send对象缓冲区
    std::ifstream object(objectPath, std::ios::binary);
    if(object)
    {
        //找到请求对象
        sscanf(buf, "HTTP/1.1 200 OK\nContent-Length: %d\nContent-Type: %s\n\n\0", object.tellg(), );
    }
    else
    {
        //请求对象不存在，使用ERROR404页面代替
        std::cout << "sendObject() fail object 404 " << objectPath << std::endl;
        object.open(homePath + ERROR404HTML, std::ios::binary);  //打开404文件
        sscanf(buf, "HTTP/1.1 404 Not Found\nContent-Length: %d\nContent-Type: %s\n\n\0", object.tellg(), );
    }
    //发送报文头
    send(connSock, buf, strlen(buf), 0);
    //发送报文体
    do
    {
        //不断读入buf并发送
        object.read(buf, BUFSIZE);
        send(connSock, buf, object.gcount(), 0);
    } while(object.gcount() == BUFSIZE);    //最后一次发送不填满buf
    object.close();
}

void Jsocket::showRequest(SOCKET connSock, std::string objectPath)
{
    sockaddr_in addr;
    int nameLen, nRc;
    nRc = getpeername(connSock, (LPSOCKADDR)&addr, &nameLen);
    if (nRc != SOCKET_ERROR)
    {
        std::string clientIP = inet_ntoa(addr.sin_addr);
        unsigned short ulPPort = addr.sin_port;
        //打印请求信息
        std::cout << "IP:" << clientIP << " port:" << ulPPort << " path:" << objectPath << std::endl;
    }
}
