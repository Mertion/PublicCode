#include "stdafx.h"
#include "AlarmIni.h"

AlarmIni::AlarmIni()
{

}

AlarmIni* AlarmIni::m_psysini = new AlarmIni;
AlarmIni* AlarmIni::initance()
{
	if (NULL == m_psysini->m_pCINIObject)
	{
		m_psysini->m_pCINIObject = new CINIObject;
		m_psysini->m_pCINIObject->SetINIFileName(_T("\\Config\\AlarmConfig.ini"));
	}
	return m_psysini;
}

int AlarmIni::getLogSwitch()
{
	int t_nLogSwitch = 0;
	//普通信息
	const int CONST_INFO = 0x01;
	//调试信息
	const int CONST_DEBUG = 0x02;
	//报警信息
	const int CONST_WARNING = 0x04;

	int t_nINFO = m_pCINIObject->GetINIFileInt(_T("system"), _T("LogSwitch_INFO"),0, t_nINFO);
	int t_nDEBUG = m_pCINIObject->GetINIFileInt(_T("system"), _T("LogSwitch_DEBUG"),0, t_nDEBUG);
	int t_nWARNING = m_pCINIObject->GetINIFileInt(_T("system"), _T("LogSwitch_WARNING"),0, t_nWARNING);

	if (0 != t_nINFO)
	{
		t_nLogSwitch += CONST_INFO;
	}

	if (0 != t_nDEBUG)
	{
		t_nLogSwitch += CONST_DEBUG;
	}

	if (0 != t_nWARNING)
	{
		t_nLogSwitch += CONST_WARNING;
	}

	return t_nLogSwitch;
}

int AlarmIni::getLanguage()
{
	int t_nLanguage = m_pCINIObject->GetINIFileInt(_T("system"), _T("Language"), 0, t_nLanguage);
	return t_nLanguage;
}

void AlarmIni::setLanguage(int p_nLanguage)
{
	m_pCINIObject->SetINIFileInt(_T("system"), _T("Language"), p_nLanguage);
}
