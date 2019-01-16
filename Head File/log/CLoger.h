#pragma once
#include "stdafx.h"
#include <afxmt.h>

using namespace std;
class CLoger
{
public:
	//日志等级
	enum ENUM_LOGSWITCH
	{
		//不记录
		ENUM_LOGSWITCH_NONE = 0,
		//普通信息
		ENUM_LOGSWITCH_INFO = 0x01,
		//调试信息
		ENUM_LOGSWITCH_DEBUG = 0x02,
		//报警信息
		ENUM_LOGSWITCH_WARNING = 0x04,
	};

public:
	CLoger();
	CLoger(CString strLogPath);
	~CLoger();

	//设置日志路径
	void setLogPath(CString strLogPath);
	//设置日志目录
	void setLogDir(CString p_strLogDir);
	//设置日志记录到程序的子目录下
	void setSubLogDir(CString p_strLogDir);
	//设置日志等级
	void SetLogSwitch(int p_nLogSwitch);
	//写日志
	virtual int Wirtelog(ENUM_LOGSWITCH p_ENUM_LOGSWITCH, const char *fmt, ...);
protected:
	//格式化日志字符串
	CStringA Format(const char *fmt, va_list& ap);
	//写入日志文件
	void WirteToFile(CStringA p_strLogInfo);
	//获得当前时间字符串
	CStringA GetTimeStr();
protected:
	//日志文件路径
	CString m_strLogPath;
	//日志文件名
	CString m_strLogName;
	CString m_strLogDir;

	//当前日志工作等级
	int m_nLogSwitch;
private:
	CCriticalSection critical_section;
};


