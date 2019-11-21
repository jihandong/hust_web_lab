#include "jsocket.h"

//初始化静态类变量
bool Jsocket::servState = false;
std::thread* Jsocket::servThread = nullptr;
SOCKET Jsocket::servSocket = NULL;
u_long Jsocket::servIP = 0;
int Jsocket::servPort = 8888;
std::string Jsocket::homePath = "C:\\Users\\13120\\Desktop\\jsocket\\home1";
int Jsocket::connNum = 0;
int Jsocket::connNumMax = 50;
MainWindow* Jsocket::wd = nullptr;

//开机
void Jsocket::startup()
{
    //发出开机信号
    servState = true;
    //抛出一个服务器线程
    servThread = new std::thread(Jsocket::acceptStartup);
    //提示
    tprintf("startup success");
}

//关机
void Jsocket::shutdown()
{
    //发出关机信号
    servState = false;
    //尝试关闭服务器线程
    if (servThread && (*servThread).joinable())
    {
        (*servThread).join();
        delete servThread;
    }
    //等待会话子线程结束
    tprintf("shutdown wait handler threads ...");
    while (connNum > 0) ;
    //关闭服务器套接字
    closesocket(servSocket);
    //提示成功
    tprintf("shutdown success");
}

//服务器运行中
bool Jsocket::inservive()
{
    return servState;
}

//服务器重置
void Jsocket::reset(MainWindow* w)
{
    servState = false;
    Jsocket::servThread = nullptr;
    servSocket = NULL;
    Jsocket::servIP = 0;
    servPort = 8888;
    homePath = "C:\\Users\\13120\\Desktop\\jsocket";
    connNum = 0;
    connNumMax = 50;
    wd = w;
}

//设置服务器IP
void Jsocket::setIP(std::string ip)
{
    servIP = inet_addr(ip.c_str());
}

//设置服务器port
void Jsocket::setPort(int n)
{
    servPort = n;
}

//设置虚拟路径
void Jsocket::setHomePath(std::string s)
{
    homePath = s;
}

//访问服务器IP
std::string Jsocket::getIP()
{
    struct in_addr in;
    memcpy(&in, &servIP, sizeof(struct in_addr));
    return inet_ntoa(in);
}

//访问服务器Port
int Jsocket::getPort()
{
    return servPort;
}

//访问虚拟目录
std::string Jsocket::getHomePath()
{
    return homePath;
}

//初始化winsock
bool Jsocket::winsockStartup()
{
    WSADATA  wsaData;
    int nRc = WSAStartup(0x0101, &wsaData);
    if(nRc)
    {
        //Winsock初始化错误
        tprintf("winsockStarup() error");
        return true;
    }
    if(wsaData.wVersion != 0x0101)
    {
        //版本支持不够
        tprintf("winsockStarup() low version");
        WSACleanup();
        return false;
    }
    return true;
}

//创建并绑定一个监听socket
bool Jsocket::bindStartup()
{
    //初始化服务器socket
    servSocket = socket(AF_INET, SOCK_STREAM, 0);
    //设置addr
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(servPort);    //u_short->网络字节顺序
    addr.sin_addr.S_un.S_addr = servIP;
    //尝试绑定
    if(bind(servSocket, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
    {
        //绑定错误
        int nRc = WSAGetLastError();
        tprintf("bindStarup() error " + std::to_string(nRc));
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
        tprintf("listenStartup() error " + std::to_string(nRc));
        return false;
    }
    return true;
}

//开始对连接多线程生成会话socket
bool Jsocket::acceptStartup()
{
    //启动winsock
    if(winsockStartup() == false)
    {
        //初始化错误
        tprintf("acceptStartup() winsockStartup error");
        return false;
    }

    //创建并绑定一个监听socket
    if(bindStartup() == false)
    {
        //绑定错误
        tprintf("acceptStartup() bind error");
        return false;
    }

    //监听socket等待连接
    if(listenStarup() == false)
    {
        //监听错误
        tprintf("acceptStartup() listen error");
        return false;
    }

    //不断响应客户端连接请求
    SOCKET connSock;                    //会话socket
    sockaddr_in connAddr;               //
    int connAddrLen = sizeof(SOCKADDR); //
    int nRc;                            //错误信息
    FD_SET set;
    timeval tv {1, 0};
    while(true){
        //初始化
        FD_ZERO(&set);
        FD_SET(servSocket, &set);

        //判断是否接受到内容
        if(servState == false)
        {
            //停机
            break;
        } else if(select(0, &set, nullptr, nullptr, &tv) == 0)
        {
            //超时无修改
            continue;
        }
        //每当收到客户端连接请求，创建新的会话SOCKET
        connSock = accept(servSocket, (SOCKADDR*)&connAddr, &connAddrLen);
        if(connSock == INVALID_SOCKET)
        {
            //创建会话socket出错
            nRc = WSAGetLastError();
            tprintf("acceptStartup() error invalid socket " + std::to_string(nRc));
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
    tprintf("new handler thread " + std::to_string(connNum));
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
        if(servState == false)
        {
            //服务器已停机
            break;
        }
        else if(select(0, &set, nullptr, nullptr, &tv) == 0)
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
            std::string objectName = requestObjectPath(buf);
            if(objectName == "")
            {
                //请求对象为空
                continue;
            }
            showRequest(connSock, objectName);
            sendObject(connSock, homePath + objectName);
        }
    }
    //关闭会话子线程
    closesocket(connSock);
    connNum--;
    tprintf("end handler thread " + std::to_string(connNum));
}

//解析请求对象路径
std::string Jsocket::requestObjectPath(std::string buf)
{
    int pos1, pos2, pos3;
    //pos1寻找"/"的位置
    if((pos1 = buf.find("/", 0)) == std::string::npos)
    {
        //解析失败，返回默认请求对象
        tprintf("requestObjectPath fail");
        return "";
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
    return objectName;
}

//发送对象到会话socket
void Jsocket::sendObject(SOCKET connSock, std::string objectPath)
{
    char buf[BUFSIZE];  //send对象缓冲区
    //修正请求对象
    if(objectPath == "\\") objectPath = "\\index.html";
    //将请求文件作为流打开
    std::ifstream object(objectPath, std::ios::binary);
    if(object)
    {
        //找到请求对象
        tprintf("200 " + objectPath);
        sprintf(buf, "HTTP/1.1 200 OK\nContent-Length: %d\n\n\0", getContentLength(objectPath) );
    }
    else
    {
        //请求对象不存在，使用ERROR404页面代替
        tprintf("404 " + objectPath);
        sprintf(buf, "HTTP/1.1 404 Not Found\nContent-Length: %d\n\n\0", getContentLength(ERROR404HTML) );
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
    tprintf("send over: " + objectPath);
}

int Jsocket::getContentLength(std::string objectPath)
{
    std::ifstream object(objectPath, std::ios::binary | std::ios::ate);
    if (!object)
    {
        return -1;
    }
    int length = object.tellg();
    object.close();
    return length;
}

//显示请求信息
void Jsocket::showRequest(SOCKET connSock, std::string objectName)
{
    sockaddr_in addr;
    int nameLen, nRc;
    nRc = getpeername(connSock, (LPSOCKADDR)&addr, &nameLen);
    if (nRc != SOCKET_ERROR)
    {
        std::string clientIP = inet_ntoa(addr.sin_addr);
        std::string clientPort = std::to_string(addr.sin_port);
        //打印请求信息
        tprintf("request: " + clientIP + ":" + clientPort + "/" + objectName);
    }
}

void Jsocket::tprintf(std::string s)
{
    if(wd) wd->tprintf(s);
}
