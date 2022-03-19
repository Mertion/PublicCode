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
	//�ж���־����
	if ((m_nLogSwitch & p_ENUM_LOGSWITCH) > 0)
	{
		//������־��Ϣ�ַ���
		CStringA strTmp;
		//��ÿɱ�����б�,����fmt���ó��������������ͣ�Ҳ�Ƿ������������ơ�%d %s�����ַ���
		va_start(ap, fmt);
		strTmp.FormatV(fmt, ap);
		//�ͷ���Դ,������va_start�ɶԵ���
		va_end(ap);
		CStringA strReturn = GetTimeStr() + strTmp;
		n = strReturn.GetLength();
		
		//����־�����������
		struLogInfo t_struLogInfo;
		t_struLogInfo.LOGSWITCH = p_ENUM_LOGSWITCH;
		t_struLogInfo.strLog = strReturn;
		m_csDQLog.Lock();
		m_DQLogInfo.push_back(t_struLogInfo);
		m_csDQLog.Unlock();

		m_pClassEventThread->TriggerThread();
	}

	return n; //����д����ַ�����	
}


UINT CThreadLoger::_exThread(LPVOID lpParam)
{
	CThreadLoger* t_CThreadLoger = (CThreadLoger*)lpParam;
	return ((CThreadLoger*)lpParam)->ThreadWriteLog();
}

void CThreadLoger::OnlyWirteToFile(CStringA p_strLogInfo)
{
	//����Ŀ¼
	if (NULL != WFile)
	{
		fwrite(p_strLogInfo, 1, p_strLogInfo.GetLength(), WFile);
		fwrite("\n", 1, 1, WFile);
	}
}

void CThreadLoger::OpenFile()
{
	//����Ŀ¼
	int status = _mkdir((CStringA)m_strLogDir);
	//���ļ�
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
	m_csFileLog.Lock();

	//����ʱ��Ϊ���������־���еĴ������ͬʱ��Ӷ�����Ϣ������߶��̲߳���ʱ��¼��־���ٶ�
	Sleep(10);
	//���ļ���Ϊ�����Ч�ʣ���־�ļ����д򿪺͹ر�
	OpenFile();

	//���ļ���д����־��Ϣ
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

	//�ر��ļ�
	CloseFile();

	m_csFileLog.Unlock();
	return 0;
}