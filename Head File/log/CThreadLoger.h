#pragma once
#include "CLoger.h"
#include "Thread/ClassEventThread.h"
#include "Thread/ClassSemaphoreThread.h"
#include <deque>

using namespace std;
//线程日志类
//单例模块，以线程方法记录日志
//当调用写日志接口时，先将要记录的内容存入日志队列，
//然后触发写日志开关再由写入线程将信息写入日志文件。
//使用方法：
//1. 在程序初始时实例化一个日志对象，在后续其它位置使用时都会以初始化对象为准。
//2. 在实例化对象时默认位置为软件根目录下，如需改变位置请在实例化后马上设定。
//3. 文件默认以日期时间为名称。
//4. 退出系统时需调用Dispose()方法销毁对象。
class CThreadLoger :public CLoger
{
protected:
	typedef struct _struLogInfo
	{
		ENUM_LOGSWITCH LOGSWITCH;
		CStringA strLog;
	}struLogInfo;
	typedef deque<struLogInfo> DQLogInfo;
protected:
	CThreadLoger();

public:
	//实例化日志对象
	static CThreadLoger* initance();
	//销毁日志对象
	void Dispose();
	//写日志
	virtual int Wirtelog(ENUM_LOGSWITCH p_ENUM_LOGSWITCH, const char *fmt, ...);

private:
	UINT static _exThread(LPVOID lpParam);
	int ThreadWriteLog();
	void OnlyWirteToFile(CStringA p_strLogInfo);
	void OpenFile();
	
	void CloseFile();
private:
	//自身单例指针
	static CThreadLoger* m_pThreadLoger;
	//日志记录线程
	ClassSemaphoreThread* m_pClassEventThread = NULL;
	//日志数据队列
	DQLogInfo m_DQLogInfo;
	//发送数据临界区
	CCriticalSection m_csDQLog;
	//文件临界区
	CCriticalSection m_csFileLog;
	//日志文件
	FILE *WFile = NULL;
};


