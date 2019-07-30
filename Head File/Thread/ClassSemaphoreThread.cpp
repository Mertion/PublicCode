#include "stdafx.h"
#include "ClassSemaphoreThread.h"
/*
参数：	lInitialCount 信号的初始使用计数。必须是大于或等于0，并且小于或等于lMaxCount。
		lMaxCount 信号的使用计数的最大值。必须大于0。
		pstrName 信号的名字。
		lpsaAttributes 此信号对象的安全标志。有关这个结构的详细描述，参见“Win32 SDK程序员参考”中的SECURITY_ATTRIBUTES。
说明： 此成员函数用来构造一个有名字或没有名字的CSemaphore对象。要访问或释放一个CSemaphore对象，可以创建一个CMultiLock或CSingleLock对象，并调用它们的Lock和Unlock函数。
*/
ClassSemaphoreThread::ClassSemaphoreThread(LONG lInitialCount, LONG lMaxCount,
	LPCTSTR pstrName, LPSECURITY_ATTRIBUTES lpsaAttributes)
{
	m_CSemaphore = new CSemaphore(lInitialCount, lMaxCount, pstrName, lpsaAttributes);
}


ClassSemaphoreThread::~ClassSemaphoreThread()
{
	Stop();

	if (NULL != m_CSemaphore)
	{
		delete m_CSemaphore;
		m_CSemaphore = NULL;
	}
	

}

unsigned ClassSemaphoreThread::exThreadTask(LPVOID lpParam)
{
	ClassSemaphoreThread* t_ClassThread = (ClassSemaphoreThread*)lpParam;
	return t_ClassThread->ThreadTask();
}
unsigned ClassSemaphoreThread::ThreadTask()
{
	unsigned t_uiRet = 0;

	do
	{
		m_CSemaphore->Lock();
		if (m_bExit)
		{
			return 0;
		}
		else
		{
			t_uiRet = (m_pFunc)(m_pArg);
		}

		Sleep(GetInterval());
	} while (true);

	return t_uiRet;
}

int ClassSemaphoreThread::Start()
{
	//判断是否有回调函数
	if (m_pFunc)
	{
		//判断是否有副本TASK在运行
		if (m_hThredHandle)
		{
			return ENUM_THREADINFO_THREADISRUN;
		}
		else
		{
			m_hThredHandle = (HANDLE)_beginthreadex(NULL,         // security 安全性 NULL 表示默认安全性
				m_nMemorySize,	// stack size 线程的堆栈大小，默认为0
				exThreadTask,	//线程回调函数
				this,           // arg list	线程参数
				m_uiInitFlag,	//初始状态，0表示立即执行
				&m_uiThreadID);	//线程句柄
			if (NULL == m_hThredHandle)
			{
				return ENUM_THREADINFO_CREATTHREADFAILD;
			}
			else
			{

			}
		}
	}
	else
	{
		return ENUM_THREADINFO_FUNCISEMPYT;
	}

	return ENUM_THREADINFO_SUCCESS;
}

void ClassSemaphoreThread::Stop()
{
	m_bExit = true;
	if (NULL != m_CSemaphore)
	{
		m_CSemaphore->Unlock();
	}

	if (NULL != m_hThredHandle)
	{
		while (true)
		{
			GetExitCodeThread(m_hThredHandle, &dwExitCode);  // should be STILL_ACTIVE = 0x00000103 = 259
			if (STILL_ACTIVE != dwExitCode)
			{
				CloseHandle(m_hThredHandle);
				m_hThredHandle = NULL;
				break;
			}
			Sleep(10);
		}
	}

}

void ClassSemaphoreThread::SetFunction(AFX_THREADPROC p_pFunc)
{
	m_pFunc = p_pFunc;
}

void ClassSemaphoreThread::SetArg(LPVOID p_pArg)
{
	m_pArg = p_pArg;
}

void ClassSemaphoreThread::SetInitFlag(unsigned p_uiInitFlag)
{
	m_uiInitFlag = p_uiInitFlag;
}

void ClassSemaphoreThread::TriggerThread()
{
	m_CSemaphore->Unlock();
}

void ClassSemaphoreThread::SetMemorySize(int p_nMemorySize)
{
	m_nMemorySize = p_nMemorySize;
}
