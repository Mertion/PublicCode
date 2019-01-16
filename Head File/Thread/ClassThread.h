#pragma once

//周期循环线程类
class ClassThread
{
public:
	enum ENUM_THREADINFO
	{
		ENUM_THREADINFO_SUCCESS = 0,
		ENUM_THREADINFO_CREATTHREADFAILD,	//创建线程失败
		ENUM_THREADINFO_FUNCISEMPYT,		//函数指针为空
		ENUM_THREADINFO_THREADISRUN,		//线程已经在运行

	};
	
	
public:
	ClassThread();
	~ClassThread();

	//线程回调函数
	unsigned  static __stdcall exThreadTask(LPVOID lpParam);
	//线程执行函数
	unsigned ThreadTask();
	//static unsigned __stdcall ThreadStaticEntryPoint(void * pThis);

	//启动线程
	int Start();
	//停止线程
	void Stop();
	//暂停线程运行
	void SuspendThread();
	//恢复线程运行
	void ResumeThread();
	//设置回调函数
	void SetFunction(AFX_THREADPROC p_pFunc);
	//设置线程参数
	void SetArg(void* p_pArg);
	//设置线程初始状态:默认为零
	void SetInitFlag(unsigned p_uiInitFlag);
	//设置扫描时间间隔
	void SetInterval(int p_nInterval);
protected:
	//线程暂停标志
	bool m_bSuspendThread = false;
	//退出线程标志
	bool m_bExitThread = false;
	//线程开始信号
	HANDLE m_hStartEvent = NULL;
	//线程结束信号
	HANDLE m_hFinishEvent = NULL;
	//线程句柄
	HANDLE m_hThredHandle = NULL;
	//线程初始状态: 0-立即运行,CREATE_SUSPEND-创建后挂起
	unsigned m_uiInitFlag = 0;
	//线程ID
	unsigned  m_uiThreadID = 0;
	//线程函数指针
	AFX_THREADPROC m_pFunc = NULL;
	//线程参数列表
	void* m_pArg = NULL;
	//线程状态码
	DWORD   dwExitCode = 0;

	//线程扫描间隔
	int m_nInterval = 10;
	
};

