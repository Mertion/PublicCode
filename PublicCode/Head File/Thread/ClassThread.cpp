#include "stdafx.h"
#include "ClassThread.h"


ClassThread::ClassThread()
{
	
}


ClassThread::~ClassThread()
{
	Stop();
	//_endthreadex();
}

unsigned __stdcall ClassThread::exThreadTask(LPVOID lpParam)
{
	ClassThread* t_ClassThread = (ClassThread*)lpParam;
	return t_ClassThread->ThreadTask();
}

unsigned ClassThread::ThreadTask()
{
	unsigned t_uiRet = 0;

	while (!m_bExitThread)
	{
		if (!m_bSuspendThread)
		{
			t_uiRet = (m_pFunc)(m_pArg);
		}

		Sleep(m_nInterval);
	}

	return t_uiRet;
}

int ClassThread::Start()
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
			m_bExitThread = false;
			m_hThredHandle = (HANDLE)_beginthreadex(NULL,         // security
				0,            // stack size
				exThreadTask,
				this,           // arg list
				m_uiInitFlag,
				&m_uiThreadID);
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

void ClassThread::Stop()
{
	m_bExitThread = true;

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

void ClassThread::SuspendThread()
{
	m_bSuspendThread = true;
}

void ClassThread::ResumeThread()
{
	m_bSuspendThread = false;
}

void ClassThread::SetFunction(AFX_THREADPROC p_pFunc)
{
	m_pFunc = p_pFunc;
}

void ClassThread::SetArg(void* p_pArg)
{
	m_pArg = p_pArg;
}

void ClassThread::SetInterval(int p_nInterval)
{
	m_nInterval = p_nInterval;
}
