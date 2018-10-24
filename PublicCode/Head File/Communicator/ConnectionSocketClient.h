
#pragma once
#pragma warning(disable:4996)

#include "stdafx.h"
#include "ConnectionIF.h"
#include "log/CThreadLoger.h"

//Socket 客户端类，实现客户端到服务器的连接
class ConnectionSocketClient : public ConnectionIF
{

public:
	ConnectionSocketClient();
	ConnectionSocketClient(int p_nPort, CString p_strAddress, int p_nProtocolType = 0);
	int Connect();
	int DisConnect();
	bool ISConnect();
	int Receive(char* p_pchrData, const int p_nDataSize, int& p_nRecDatalen);
	int Send(char* p_pchrData, int p_nDatalen);

public:
	~ConnectionSocketClient();
	void init();
protected:
	//客户端套接字
	SOCKET m_sclient;
	//连接地址
	sockaddr_in m_serAddr;
	//协议类型:0-TCP 1-UDP
	int m_nProtocolType = 0;
	//当前连接状态 false-未连接 true-连接
	bool m_bConnectState = false;

	CString m_strIP;
	int m_nPort = 0;
	CThreadLoger* m_pThreadLoger;
};

