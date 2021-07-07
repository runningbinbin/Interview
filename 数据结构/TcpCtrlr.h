
#ifndef TCP_CTRLR_H
#define TCP_CTRLR_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef int (*PFuncDataHandler)(unsigned char *pucData, unsigned int nDataLen, void * pvUsrArg);	// 数据处理函数

typedef struct TcpClientMgr
{
    int iClientSockFd;								// 套接字
    struct sockaddr_in tRemoteClientAddr;			// 网络通信结构体---客户端信息
    bool bClientRunning;							// 客户端处理线程标志
    pthread_t tClientThreadId;						// 新的客户端线程ID
    PFuncDataHandler *ppFuncDataHandler;			// 数据处理函数
    void **ppvUsrArg;								// 用户参数
    struct TcpClientMgr *ptNext;					// 新的客户端结点
} T_TcpClientMgr, * PT_TcpClientMgr;

typedef struct TcpServerMgr
{
    int iSockFd;									// 套接字
    unsigned short wPort;							// 端口号
    struct sockaddr_in tLocalServerAddr;			// 网络通信结构体---服务器信息
    bool bListening;								// 监听线程标志
    int iConnectedClients;							// 客户端序号
    int iMaxConnections;							// 支持最大客户端连接数，可借助配置文件配置
    pthread_t tListenThread;						// 监听线程ID
    T_TcpClientMgr *ptTcpClientMgrHead;				// 客户端管理结构体
} T_TcpServerMgr, *PT_TcpServerMgr;

class CTcpCtrlr
{
public:
    CTcpCtrlr();
    ~CTcpCtrlr();

    static int setKeepAlive(int iSockFd, bool bKeepAlive, int iKeepIdle, int iKeepInterval, int iKeepCount);	// 设置KeepAlive属性，方便获取连接状态
    static int checkTcpLink(int iSockFd);																		// 检测TCP连接状态
    int sendData(const unsigned char *pucData, unsigned int nLen);												// 数据发送接口
    void closeSocket();																							// 关闭套接字
    void setDataHandler(PFuncDataHandler pFuncDataHandler, void *pvUsrArg);										// 注册数据处理函数
    const T_TcpClientMgr *getTcpClientMgrHead() const;															// 获取客户端网络信息

private:
    static int initSocket(T_TcpServerMgr *ptTcpServerMgr);													// 初始化套接字
    static void *listeningThread(void *pvArg);																	// 监听线程
    static void *clientManageThread(void *pvArg);																// 客户端管理线程，处理实际业务

    void clearClientLinks();

    T_TcpServerMgr m_tTcpServerMgr;
    PFuncDataHandler m_pFuncDataHandler;
    void *m_pvUsrArg;
    pthread_mutex_t m_tMutex;
};

#endif // TCP_CTRLR_H
