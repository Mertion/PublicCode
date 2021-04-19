#include "stdafx.h"
#include "CThreadLoger.h"
#include <direct.h>

CThreadLoger::CThreadLoger(void)
{
	
}
CThreadLoger* CThreadLoger::m_pThreadLoger = new CThreadLoger;
CThreadLoger* CThreadLoger::initance()
{
	if (NULL == m_pThreadLoger->m_pClassEventThread)
	{
		m_pThreadLoger->m_pClassEventThread = new ClassSemaphoreThread(0,100);
		m_pThreadLoger->m_pClassEventThread->SetArg(m_pThreadLoger);
		m_pThreadLoger->m_pClassEventThread->SetFunction(_exThread);
		m_pThreadLoger->m_pClassEventThread->Start();
	}

	return m_pThreadLoger;
}

void CThreadLoger::Dispose()
{
	if (NULL != m_pClassEventThread)
	{
		m_pClassEventThread->Stop();
	}
}

int CThreadLoger::Wirtelog(ENUM_LOGSWITCH p_ENUM_LOGSWITCH, const char *fmt, ...)
{
	int n = 0;
	va_list ap;
	//判断日志开关
	if ((m_nLogSwitch & p_ENUM_LOGSWITCH) > 0)
	{
		//生成日志信息字符串
		CStringA strTmp;
		//获得可变参数列表,分析fmt，得出各个参数的类型，也是分析参数中类似”%d %s“的字符串
		va_start(ap, fmt);
		strTmp.FormatV(fmt, ap);
		//释放资源,必须与va_start成对调用
		va_end(ap);
		CStringA strReturn = GetTimeStr() + strTmp;
		n = strReturn.GetLength();
		
		//向日志队列添加数据
		struLogInfo t_struLogInfo;
		t_struLogInfo.LOGSWITCH = p_ENUM_LOGSWITCH;
		t_struLogInfo.strLog = strReturn;
		m_csDQLog.Lock();
		m_DQLogInfo.push_back(t_struLogInfo);
		m_csDQLog.Unlock();

		m_pClassEventThread->TriggerThread();
	}

	return n; //返回写入的字符个数	
}


UINT CThreadLoger::_exThread(LPVOID lpParam)
{
	CThreadLoger* t_CThreadLoger = (CThreadLoger*)lpParam;
	return ((CThreadLoger*)lpParam)->ThreadWriteLog();
}

void CThreadLoger::OnlyWirteToFile(CStringA p_strLogInfo)
{
	//创建目录
	if (NULL != WFile)
	{
		fwrite(p_strLogInfo, 1, p_strLogInfo.GetLength(), WFile);
		fwrite("\n", 1, 1, WFile);
	}
}

void CThreadLoger::OpenFile()
{
	//创建目录
	int status = _mkdir((CStringA)m_strLogDir);
	//打开文件
	fopen_s(&WFile, (CStringA)m_strLogPath, "a");
}
void CThreadLoger::CloseFile()
{
	if (NULL != WFile)
	{
		fclose(WFile);
	}
}
int CThreadLoger::ThreadWriteLog()
{
	//此延时是为了让添加日志队列的代码可以同时添加多条信息，以提高多线程并发时记录日志的速度
	Sleep(10);
	//打开文件，为了提高效率，日志文件集中打开和关闭
	OpenFile();

	//向文件中写入日志信息
	m_csDQLog.Lock();
	while (m_DQLogInfo.size() > 0)
	{
		CStringA strLog = m_DQLogInfo.front().strLog;
		
		if ((m_nLogSwitch & m_DQLogInfo.front().LOGSWITCH) > 0)
		{
			OnlyWirteToFile(strLog);
		}
		m_DQLogInfo.pop_front();
	}
	m_csDQLog.Unlock();

	//关闭文件
	CloseFile();

	return 0;
}