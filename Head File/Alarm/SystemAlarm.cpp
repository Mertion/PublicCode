#include "stdafx.h"
#include "SystemAlarm.h"
#include "FileOperation/CFileOpertion.h"
#include "AlarmIni.h"

SystemAlarm::SystemAlarm(void)
{

}

CString SystemAlarm::getWarningStr(int p_nWarningNo)
{
	CString t_strWarning;
	CString t_strWarningNo;
	t_strWarningNo.Format(_T("%d"), p_nWarningNo);
	m_pWarningIni->GetINIFileString(_T("Warning"), t_strWarningNo, _T(""), 255, t_strWarning);

	return t_strWarning;
}

SystemAlarm* SystemAlarm::m_pSystemAlarm = new SystemAlarm;
bool SystemAlarm::m_bISInitance = false;

SystemAlarm* SystemAlarm::initance()
{
	if (!m_bISInitance)
	{
		m_bISInitance = true;
		m_pSystemAlarm->m_pCThreadLoger = CThreadLoger::initance();
		m_pSystemAlarm->m_pfuncSetAlarmInfo = NULL;
		m_pSystemAlarm->m_pWarningIni = new CINIObject();
		//更新报警信息
		m_pSystemAlarm->UpdateLanguage();
	}

	return m_pSystemAlarm;
}

void SystemAlarm::AutomReleaseAlarm(AlarmUnit* p_AlarmUnit)
{
	if (NULL != m_pfuncSetAlarmInfo)
	{
		m_pCThreadLoger->Wirtelog(CLoger::ENUM_LOGSWITCH_WARNING, "AlarmNo: %d", p_AlarmUnit->AlarmNo);
		m_pfuncSetAlarmInfo((AlarmInfo)(*p_AlarmUnit));
	}

}

void SystemAlarm::NormalReleaseAlarm(AlarmUnit* p_AlarmUnit)
{
	if (p_AlarmUnit->bRelease)
	{
		m_pCThreadLoger->Wirtelog(CLoger::ENUM_LOGSWITCH_DEBUG, "Normal Alarm No:%d  ", p_AlarmUnit->AlarmNo);
		p_AlarmUnit->bRelease = FALSE;
		AutomReleaseAlarm(p_AlarmUnit);
	}
}

void SystemAlarm::ReleaseAlarm(AlarmUnit* p_AlarmUnit)
{
	if (!p_AlarmUnit->bRelease)
	{
		m_pCThreadLoger->Wirtelog(CLoger::ENUM_LOGSWITCH_DEBUG, "Release No:%d Alarm ", p_AlarmUnit->AlarmNo);
	}
	p_AlarmUnit->bRelease = TRUE;
}

void SystemAlarm::SetAlarmCallBackFunction(void* p_pFun)
{
	m_pfuncSetAlarmInfo = (pfuncSetAlarmInfo)p_pFun;
}

void SystemAlarm::Warning(int p_nWarningNo, CString p_strWarning)
{
	AlarmInfo t_AlarmInfo;
	t_AlarmInfo.AlarmNo = p_nWarningNo;
	memcpy(t_AlarmInfo.arrchrAlarmInfo, (CStringA)p_strWarning, ((CStringA)p_strWarning).GetLength());
	m_pCThreadLoger->Wirtelog(CLoger::ENUM_LOGSWITCH_WARNING, "Warning: No %d, %s", t_AlarmInfo.AlarmNo, t_AlarmInfo.arrchrAlarmInfo);
	if (NULL != m_pfuncSetAlarmInfo)
	{
		m_pfuncSetAlarmInfo(t_AlarmInfo);
	}
}

void SystemAlarm::Warning(int P_nWarningNo)
{
	CString t_strWarning;
	t_strWarning.Format(_T("Warrning: No %d "), P_nWarningNo);
	t_strWarning += getWarningStr(P_nWarningNo);
	Warning(P_nWarningNo, t_strWarning);
}

void SystemAlarm::Warning(int P_nWarningNo, int p_nUnitNo)
{
	CString t_strWarning;
	t_strWarning.Format(_T("Warrning: No %d %s: %d"), P_nWarningNo, m_strUnit, p_nUnitNo);
	t_strWarning += getWarningStr(P_nWarningNo);
	Warning(P_nWarningNo, t_strWarning);
}

void SystemAlarm::Warning(int P_nWarningNo, int p_nUnitNo, int p_nStationNo)
{
	CString t_strWarning;
	t_strWarning.Format(_T("Warrning: No %d %s: %d %s: %d"), P_nWarningNo, m_strUnit, p_nUnitNo,m_strStation,p_nStationNo);
	t_strWarning += getWarningStr(P_nWarningNo);
	Warning(P_nWarningNo, t_strWarning);
}

void SystemAlarm::UpdateLanguage()
{
	AlarmIni* t_pSysIni = AlarmIni::initance();
	ENUM_LANGUAGE p_Language = (ENUM_LANGUAGE)t_pSysIni->getLanguage();
	CStringA t_strWarningFileName;
	switch (p_Language)
	{
	case ENUM_LANGUAGE_EN:
	{
		t_strWarningFileName = "config\\Warning_EN.txt";
	}
	break;
	case ENUM_LANGUAGE_CN:
	{
		t_strWarningFileName = "config\\Warning_CN.txt";
	}
	break;
	case ENUM_LANGUAGE_LOCAL:
	{
		t_strWarningFileName = "config\\Warning_LOCAL.txt";
	}
	break;
	default:
		break;
	}

	CString t_strModuleDir = CFileOpertion::GetModuleFileDir();
	m_strWarningFilePatch = t_strModuleDir + (CString)t_strWarningFileName;
	m_pWarningIni->SetINIFilePath(m_strWarningFilePatch);

	m_pWarningIni->GetINIFileString(_T("Other"), _T("unit"), _T(""), 255, m_strUnit);
	m_pWarningIni->GetINIFileString(_T("Other"), _T("station"), _T(""), 255, m_strStation);
}
