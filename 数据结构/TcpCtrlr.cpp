
#include <cstring>
#include <cstdio>
#include <netinet/tcp.h>
#include <netinet/in.h>

#include <poll.h>
/* According to POSIX.1-2001, POSIX.1-2008 */
// #include <sys/select.h>
// #include <sys/ioctl.h>
#include <fcntl.h>

#include "ErrorCode.h"
#include "TcpCtrlr.h"

// 构造函数，初始化成员变量
CTcpCtrlr::CTcpCtrlr()
{
    memset(&m_tTcpServerMgr, 0, sizeof(m_tTcpServerMgr));
    m_tTcpServerMgr.wPort = (unsigned short)read_profile_int("setting", "Port", 34007, FILE_INI_NAME);		// 从配置文件获取本地端口
    m_tTcpServerMgr.iMaxConnections = read_profile_int("setting", "MaxConnection", 2, FILE_INI_NAME);		// 从配置文件获取最大支持客户端连接数
    m_tTcpServerMgr.ptTcpClientMgrHead = new T_TcpClientMgr;
    m_tTcpServerMgr.ptTcpClientMgrHead->ptNext = nullptr;

    int iRet;
    iRet = pthread_create(&m_tTcpServerMgr.tListenThread, NULL, listeningThread, (void *)(this));
    iRet = pthread_mutex_init(&m_tMutex, NULL);
    if (iRet != 0)
    {
        return;
    }
}

// 析构
CTcpCtrlr::~CTcpCtrlr()
{
    clearClientLinks();
    pthread_mutex_destroy(&m_tMutex);
}

// 设置KeepAlive属性
int CTcpCtrlr::setKeepAlive(int iSockFd, bool bKeepAlive, int iKeepIdle, int iKeepInterval, int iKeepCount)
{
    int iRet;
    int iKeepAlive;
    if (bKeepAlive)
    {
        iKeepAlive = 1;
        iRet = setsockopt(iSockFd, SOL_SOCKET, SO_KEEPALIVE, (const void *)&iKeepAlive, sizeof(iKeepAlive));
        if (iRet <  0)
        {
            return iRet;
        }

        iRet = setsockopt(iSockFd, SOL_TCP, TCP_KEEPIDLE, (const void *)&iKeepIdle, sizeof(iKeepIdle));
        if (iRet <  0)
        {
            return iRet;
        }

        iRet = setsockopt(iSockFd, SOL_TCP, TCP_KEEPINTVL, (const void *)&iKeepInterval, sizeof(iKeepInterval));
        if (iRet <  0)
        {
            return iRet;
        }

        iRet = setsockopt(iSockFd, SOL_TCP, TCP_KEEPCNT, (const void *)&iKeepCount, sizeof(iKeepCount));
        if (iRet <  0)
        {
            return iRet;
        }
    }
    else
    {
        iKeepAlive = 0;
        iRet = setsockopt(iSockFd, SOL_SOCKET, SO_KEEPALIVE, (const void *)&iKeepAlive, sizeof(iKeepAlive));
        if (iRet <  0)
        {
            return iRet;
        }
    }

    return iRet;
}

// 检查TCP连接状态
int CTcpCtrlr::checkTcpLink(int iSockFd)
{
    struct tcp_info tcpInfo;
    int iSize = sizeof(tcpInfo);
    int iRet = getsockopt(iSockFd, IPPROTO_TCP, TCP_INFO, &tcpInfo, (socklen_t *)(&iSize));

    if (iRet == 0)
    {
        return tcpInfo.tcpi_state;
    }

    return iRet;
}

// 关闭套接字
void CTcpCtrlr::closeSocket()
{
    if (m_tTcpServerMgr.iSockFd > 0)
    {
        close(m_tTcpServerMgr.iSockFd);
    }

    m_tTcpServerMgr.iSockFd = -1;
}

// 注册数据处理函数
void CTcpCtrlr::setDataHandler(PFuncDataHandler pFuncDataHandler, void * pvUsrArg)
{
    m_pFuncDataHandler = pFuncDataHandler;
    m_pvUsrArg = pvUsrArg;
}

// 获取客户端网络信息
const T_TcpClientMgr * CTcpCtrlr::getTcpClientMgrHead() const
{
    return m_tTcpServerMgr.ptTcpClientMgrHead;
}

// 初始化套接字，包括申请套接字、设置套接字属性、绑定、监听等
int CTcpCtrlr::initSocket(T_TcpServerMgr * ptTcpServerMgr)
{
    int iFlags;
    int iRet;

    ptTcpServerMgr->iSockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (ptTcpServerMgr->iSockFd < 0)
    {
        return eECSocket;
    }

    /* 如果设为非阻塞模式，则 send 函数需要自行封装，send 在非阻塞模式下返回值不一定是用户指定传输数据量参数 */
#if 0
    iFlags = fcntl(ptTcpServerMgr->iSockFd, F_GETFL, 0);

    iRet = fcntl(ptTcpServerMgr->iSockFd, F_SETFL, iFlags | O_NONBLOCK);
    if (iRet != 0)
    {
        close(ptTcpServerMgr->iSockFd);
        ptTcpServerMgr->iSockFd = -1;
        return eECSetSocketFlag;
    }
#endif
    // in case of 'address already in use' error
    iFlags = 1;
    iRet = setsockopt(ptTcpServerMgr->iSockFd, SOL_SOCKET, SO_REUSEADDR, &iFlags, sizeof(iFlags));
    if (iRet != 0)
    {
        close(ptTcpServerMgr->iSockFd);
        ptTcpServerMgr->iSockFd = -1;
        return eECSetSocketFlag;
    }

    // in case of 'port already in use' error
    iRet = setsockopt(ptTcpServerMgr->iSockFd, SOL_SOCKET, SO_REUSEPORT, &iFlags, sizeof(iFlags));
    if (iRet != 0)
    {
        close(ptTcpServerMgr->iSockFd);
        ptTcpServerMgr->iSockFd = -1;
        return eECSetSocketFlag;
    }

    bzero(&(ptTcpServerMgr->tLocalServerAddr), sizeof(ptTcpServerMgr->tLocalServerAddr));
    ptTcpServerMgr->tLocalServerAddr.sin_family = AF_INET;
    ptTcpServerMgr->tLocalServerAddr.sin_port = htons(ptTcpServerMgr->wPort);
    ptTcpServerMgr->tLocalServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    iRet = bind(ptTcpServerMgr->iSockFd, (struct sockaddr *)&ptTcpServerMgr->tLocalServerAddr, sizeof(struct sockaddr));
    if (iRet < 0)
    {
        close(ptTcpServerMgr->iSockFd);
        ptTcpServerMgr->iSockFd = -1;
        return eECBindSocket;
    }

    iRet = listen(ptTcpServerMgr->iSockFd, 10);
    if (iRet < 0)
    {
        close(ptTcpServerMgr->iSockFd);
        ptTcpServerMgr->iSockFd = -1;
        return eECListen;
    }

    return eECOK;
}

// 客户端管理线程，处理实际业务
void *CTcpCtrlr::clientManageThread(void *pvArg)
{
    T_TcpClientMgr *ptTcpClientMgr = (T_TcpClientMgr *)pvArg;

    struct pollfd tPollFds;
    int iTimeout;
    int iRet;
    unsigned char aucBuf[256];

    if (setKeepAlive(ptTcpClientMgr->iClientSockFd, true, 5, 1, 3) != 0)
    {
        goto Ret;
    }

    iTimeout = 100; // 毫秒
    tPollFds.fd = ptTcpClientMgr->iClientSockFd;
    tPollFds.events = POLLIN | POLLPRI;

    while (ptTcpClientMgr->bClientRunning)
    {
        // check the connection
        if (checkTcpLink(ptTcpClientMgr->iClientSockFd) != TCP_ESTABLISHED)
        {
            printf("Connection disconnected by peer.\n");
            goto Ret;
        }

        iRet = poll(&tPollFds, 1, iTimeout);
        switch (iRet)
        {
            case -1:
            {
                goto Ret;
            }
            case 0:
            {
                continue;
            }
            default:
            {
                if ((tPollFds.revents & POLLIN) || (tPollFds.revents & POLLPRI))
                {
                    // receive cmd
                    iRet = recv(ptTcpClientMgr->iClientSockFd, aucBuf, 256, 0);
                    printf("Cmd: \n");
                    for(int cnt = 0; cnt < iRet; cnt++)
                    {
                        printf(" %02x", aucBuf[cnt]);
                        if((cnt + 1) % 16 == 0)
                            printf("\n");
                    }
                    printf("\n");

                    if (iRet > 0)
                    {
                        if ((*(ptTcpClientMgr->ppFuncDataHandler)) != nullptr)
                        {
                            // 处理数据
                            (*(ptTcpClientMgr->ppFuncDataHandler))(aucBuf, iRet, *(ptTcpClientMgr->ppvUsrArg));
                        }
                    }
                }

                break;
            }
        }
    }

Ret:
    close(ptTcpClientMgr->iClientSockFd);
    ptTcpClientMgr->iClientSockFd = -1;
    ptTcpClientMgr->bClientRunning = false;

    return nullptr;
}

// 套接字监听线程
void *CTcpCtrlr::listeningThread(void * pvArg)
{
    CTcpCtrlr * pTcpCtrlr = (CTcpCtrlr *)pvArg;
    T_TcpServerMgr *ptTcpServerMgr = &(pTcpCtrlr->m_tTcpServerMgr);
    T_TcpClientMgr *ptPreTcpClientMgr;
    T_TcpClientMgr *ptCurTcpClientMgr;
    T_TcpClientMgr *ptNextTcpClientMgr;

    int iTmp, ret;
    int iSinSize = sizeof(struct sockaddr_in);
    struct sockaddr_in tRemoteClientAddr;

    ptTcpServerMgr->bListening = (initSocket(ptTcpServerMgr) == 0);

    while (ptTcpServerMgr->bListening && ptTcpServerMgr->iSockFd > 0)
    {
        memset(&tRemoteClientAddr, 0, iSinSize);

        iTmp = accept(ptTcpServerMgr->iSockFd, (struct sockaddr *)&tRemoteClientAddr, (socklen_t *)(&iSinSize));
        if (iTmp > 0)
        {
            printf("Here comes a client.\n");
            ptPreTcpClientMgr = ptTcpServerMgr->ptTcpClientMgrHead;
            ptCurTcpClientMgr = ptTcpServerMgr->ptTcpClientMgrHead->ptNext;
            while (nullptr != ptCurTcpClientMgr)
            {
                if (ptCurTcpClientMgr->iClientSockFd <= 0 && !ptCurTcpClientMgr->bClientRunning)	// 如果客户端标志/状态异常，则释放已经断开的连接
                {
                    pthread_join(ptCurTcpClientMgr->tClientThreadId, NULL); // 回收线程资源
                    ptNextTcpClientMgr = ptCurTcpClientMgr->ptNext;
                    ptPreTcpClientMgr->ptNext = ptNextTcpClientMgr;
                    delete ptCurTcpClientMgr;

                    ptTcpServerMgr->iConnectedClients -= 1;
                    if (ptTcpServerMgr->iConnectedClients < 0)
                    {
                        ptTcpServerMgr->iConnectedClients = 0;
                    }

                    ptCurTcpClientMgr = ptNextTcpClientMgr;
                }
                else																					// 否则，增加新链表结点管理新客户端
                {
                    ptPreTcpClientMgr = ptCurTcpClientMgr;
                    ptCurTcpClientMgr = ptCurTcpClientMgr->ptNext;
                }
            }

            // 超过最大连接数量
            if (ptTcpServerMgr->iConnectedClients >= ptTcpServerMgr->iMaxConnections)
            {
                close(iTmp);
                continue;
            }

            int sockBufLen = 0;
            sockBufLen = 1024 * 1024 * 20; //20MB
            ret = setsockopt(iTmp, SOL_SOCKET, SO_SNDBUFFORCE, &sockBufLen, sizeof (int));
            if (ret < 0) 
            {
                printf("setsockopt SO_RCVBUFFORCE error. %d\n", ret);
                return NULL;
            }
            
            // int len = sizeof(int);
            // ret = getsockopt(iTmp, SOL_SOCKET, SO_SNDBUF, &sockBufLen, (socklen_t *) &len);
            // if (ret < 0) 
            // {
            //     printf("getsockopt SO_RCVBUF errot. %d\n", ret);
            //     return NULL;
            // }
            // printf("TCP socket send buf is set to %d\n", sockBufLen);

            ptNextTcpClientMgr = new T_TcpClientMgr;
            if (nullptr == ptNextTcpClientMgr)
            {
                close(iTmp);
                continue;
            }

            ptNextTcpClientMgr->iClientSockFd = iTmp;
            ptNextTcpClientMgr->bClientRunning = true;
            memcpy(&(ptNextTcpClientMgr->tRemoteClientAddr), &tRemoteClientAddr, sizeof(tRemoteClientAddr));
            ptNextTcpClientMgr->ppFuncDataHandler = &(pTcpCtrlr->m_pFuncDataHandler);
            ptNextTcpClientMgr->ppvUsrArg = &(pTcpCtrlr->m_pvUsrArg);
            iTmp = pthread_create(&(ptNextTcpClientMgr->tClientThreadId), NULL, clientManageThread, (void *)ptNextTcpClientMgr);	//开辟客户端管理线程，处理实际业务
            if (iTmp != 0)
            {
                close(ptNextTcpClientMgr->iClientSockFd);
                ptNextTcpClientMgr->iClientSockFd = -1;
                ptNextTcpClientMgr->bClientRunning = false;
                delete ptNextTcpClientMgr;
                continue;
            }

            // 插入链表
            ptPreTcpClientMgr->ptNext = ptNextTcpClientMgr;
            ptNextTcpClientMgr->ptNext = nullptr;
            ptTcpServerMgr->iConnectedClients += 1;
        }
        else
        {
            sleep(1);
        }
    }

    return nullptr;
}

// 释放已经断开连接的资源
void CTcpCtrlr::clearClientLinks()
{
    m_tTcpServerMgr.bListening = false;
    closeSocket();

    pthread_join(m_tTcpServerMgr.tListenThread, NULL);

    // printf("Listen thread exited\n");

    T_TcpClientMgr *ptCurTcpClientMgr = m_tTcpServerMgr.ptTcpClientMgrHead->ptNext;
    T_TcpClientMgr *ptNextTcpClientMgr;
    while (nullptr != ptCurTcpClientMgr)
    {
        ptCurTcpClientMgr->bClientRunning = false;
        pthread_join(ptCurTcpClientMgr->tClientThreadId, NULL);
        // printf("Client %p exited and will be cleared\n", ptCurTcpClientMgr);
        ptNextTcpClientMgr = ptCurTcpClientMgr->ptNext;
        delete ptCurTcpClientMgr;
        // printf("Client %p cleared\n", ptCurTcpClientMgr);
        ptCurTcpClientMgr = ptNextTcpClientMgr;
    }

    delete m_tTcpServerMgr.ptTcpClientMgrHead;

    // printf("Client head %p cleared\n", m_tTcpServerMgr.ptTcpClientMgrHead);
    m_tTcpServerMgr.ptTcpClientMgrHead = nullptr;
}

// 发送数据接口
int CTcpCtrlr::sendData(const unsigned char *pucData, unsigned int nLen)
{
    pthread_mutex_lock(&m_tMutex);

    int iCnt = 0;
    T_TcpClientMgr * ptTcpClientMgr = m_tTcpServerMgr.ptTcpClientMgrHead->ptNext;
    
    while (nullptr != ptTcpClientMgr)
    {
        if (ptTcpClientMgr->bClientRunning)
        {
            if (send(ptTcpClientMgr->iClientSockFd, pucData, nLen, 0) <= 0)
            {
                ptTcpClientMgr->bClientRunning = false;
            }
            else
            {
                ++iCnt;
            }
        }

        ptTcpClientMgr = ptTcpClientMgr->ptNext;
    }

    pthread_mutex_unlock(&m_tMutex);

    if (iCnt > 0)
    {
        return eECOK;
    }
    else
    {
        return eECDataSendError;
    }
}
