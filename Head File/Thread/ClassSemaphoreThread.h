#pragma once
#include "stdafx.h"
#include<afxmt.h>

//事件触发线程类
//每调用一次TriggerThread方法执行一次线程函数
class ClassSemaphoreThread
{
public:
	enum ENUM_THREADINFO
	{
		ENUM_THREADINFO_SUCCESS = 0,
		ENUM_THREADINFO_CREATTHREADFAILD,	//创建线程失败
		ENUM_THREADINFO_FUNCISEMPYT,		//函数指针为空
		ENUM_THREADINFO_THREADISRUN,		//线程已经在运行
	};
	
	DWORD GetInterval() const { return m_nInterval; }
	void SetInterval(DWORD val) { m_nInterval = val; }
public:
	ClassSemaphoreThread(LONG lInitialCount = 1, LONG lMaxCount = 1,
		LPCTSTR pstrName = NULL, LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);
	~ClassSemaphoreThread();

	//线程回调函数
	unsigned  static __stdcall exThreadTask(LPVOID lpParam);
	//线程执行函数
	unsigned ThreadTask();
	//static unsigned __stdcall ThreadStaticEntryPoint(void * pThis);

	//启动线程
	int Start();
	//停止线程
	void Stop();
	//设置回调函数
	void SetFunction(AFX_THREADPROC p_pFunc);
	//设置线程参数
	void SetArg(LPVOID p_pArg);
	//设置线程初始状态:默认为零
	void SetInitFlag(unsigned p_uiInitFlag);
	//触发一次线程执行
	void TriggerThread();
	//设置内存堆栈大小，在线程启动前设置有效
	void SetMemorySize(int p_nMemorySize);
protected:
	//内存堆栈大小
	int m_nMemorySize = 0;
	//线程句柄
	HANDLE m_hThredHandle = NULL;
	//线程初始状态: 0-立即运行,CREATE_SUSPEND-创建后挂起
	unsigned m_uiInitFlag = 0;
	//线程ID
	unsigned  m_uiThreadID = 0;
	//线程函数指针
	AFX_THREADPROC m_pFunc = NULL;
	//线程参数列表
	LPVOID m_pArg = NULL;
	//线程状态码
	DWORD   dwExitCode = 0;

	//线程扫描间隔
	DWORD m_nInterval = 0;


	//线程同步信号
	CSemaphore* m_CSemaphore = NULL;

	//退出线程
	bool m_bExit = false;
};

