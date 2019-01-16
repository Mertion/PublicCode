
#pragma once
#pragma warning(disable:4996)

#include "stdafx.h"
#include "ConnectionIF.h"
#include "Thread/ClassEventThread.h"
#include "log/CThreadLoger.h"

//Socket 服务端连接实现，完成单端口对单客户端连接。
//一对多客户端方式不适合目前系统应用存在以下问题：
//1. 数据拆包如果在该层内实现影响目前系统结构，如果不在该层内实现会导致数据包不完整时无法处理。
//2. 多客户端每个客户端业务又不相同无法明确区分哪个连接是什么业务，导致服务端在返回数据时可能会面临无法使用正确客户端的情况。
//   a. 如服务端记录是哪个客户端发来的指令在返回，如果该连接已断开导致数据无法返回。
//   b. 如采用随机客户端返回会增加客户端程序处理复杂度。

class ConnectionSocketServer : public ConnectionIF
{
public:

public:
	ConnectionSocketServer();
	ConnectionSocketServer(int p_nPort, CString p_strAddress, int p_nProtocolType = 0);
	~ConnectionSocketServer();
	int init();
	int Connect();
	int DisConnect();
	bool ISConnect();
	int Receive(char* p_pchrData, const int p_nDataSize, int& p_nRecDatalen);
	int Send(char* p_pchrData, int p_nDatalen);
private:

	//监听线程回调函数
	UINT static _exListen(LPVOID lpParam);
	//监听客户端接入并创建连接，当客户端断开后自动监听下一次连接
	int Listen();
protected:

	int DisConnectServer();
protected:
	//客户端套接字
	SOCKET m_sclient;
	//连接地址
	sockaddr_in m_serAddr;
	//协议类型:0-TCP 1-UDP
	int m_nProtocolType = 0;
	//当前连接状态 false-未连接 true-连接
	bool m_bConnectState = false;

	//服务端监听套接字  
	SOCKET m_slisten;
	//远程客户端地址
	sockaddr_in m_remoteAddr;
	//应答客户端请求事件信号
	HANDLE m_hQureConnect = NULL;
	//退出监听信号
	HANDLE m_hExitListen = NULL;
	HANDLE m_hHandles[2];
	//监听服务线程对象
	ClassEventThread* m_ClassEventThread = NULL;

	CThreadLoger* m_pThreadLoger;
};
