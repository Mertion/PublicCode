#include "stdafx.h"
#include "ClassEventThread.h"

ClassEventThread::ClassEventThread()
{
	if (NULL == m_hExit)
	{
		m_hExit = CreateEvent(NULL, TRUE, FALSE, NULL);
		ResetEvent(m_hExit);
	}
	if (NULL == m_hActive)
	{
		m_hActive = CreateEvent(NULL, TRUE, FALSE, NULL);
		ResetEvent(m_hActive);
	}
	m_hEvent[0] = m_hExit;
	m_hEvent[1] = m_hActive;
}


ClassEventThread::~ClassEventThread()
{
	Stop();

	if (NULL != m_hExit)
	{
		CloseHandle(m_hExit);
	}
	if (NULL != m_hActive)
	{
		CloseHandle(m_hActive);
	}
	if (NULL != m_hThredHandle)
	{
		CloseHandle(m_hThredHandle);
	}

}

unsigned ClassEventThread::exThreadTask(LPVOID lpParam)
{
	ClassEventThread* t_ClassThread = (ClassEventThread*)lpParam;
	return t_ClassThread->ThreadTask();
}
unsigned ClassEventThread::ThreadTask()
{
	unsigned t_uiRet = 0;

	DWORD dwEvent;
	do
	{
		dwEvent = WaitForMultipleObjects(2, m_hEvent, FALSE, INFINITE);
		switch (dwEvent)
		{
		case WAIT_OBJECT_0 + 0:
		{
			//_endthreadex(0);
			return 0;
		}
		break;
		case  WAIT_OBJECT_0 + 1:
		{
			ResetEvent(m_hActive);
			t_uiRet = (m_pFunc)(m_pArg);
		}
		break;
		default:
			break;
		}

	} while (true);

	return t_uiRet;
}

int ClassEventThread::Start()
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
			ResetEvent(m_hExit);
			ResetEvent(m_hActive);
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

void ClassEventThread::Stop()
{
	SetEvent(m_hExit);

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

void ClassEventThread::SetFunction(AFX_THREADPROC p_pFunc)
{
	m_pFunc = p_pFunc;
}

void ClassEventThread::SetArg(LPVOID p_pArg)
{
	m_pArg = p_pArg;
}

void ClassEventThread::SetInitFlag(unsigned p_uiInitFlag)
{
	m_uiInitFlag = p_uiInitFlag;
}

void ClassEventThread::TriggerThread()
{
	SetEvent(m_hActive);
}

void ClassEventThread::SetMemorySize(int p_nMemorySize)
{
	m_nMemorySize = p_nMemorySize;
}
