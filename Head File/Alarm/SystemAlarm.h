#pragma once
#include "log/CSingletonLoger.h"
#include "log/CThreadLoger.h"
#include "FileOperation/CINIObject.h"
#include "General.h"

//界面用报警信息
typedef struct _AlarmInfo
{
	CONST static int CONST_MAX_ALARMINFOLEN = 1024;
	//报警编号
	int AlarmNo;
	char arrchrAlarmInfo[CONST_MAX_ALARMINFOLEN];
	_AlarmInfo()
	{
		AlarmNo = 0;
		memset(arrchrAlarmInfo, 0, CONST_MAX_ALARMINFOLEN);
	}

}AlarmInfo;

//底层用报警信息
typedef struct _AlarmUnit :public AlarmInfo
{
	//报警状态是否解除，如果一个报警状态未解除，该报警不会再次向界面发送
	BOOL bRelease;
	_AlarmUnit()
	{
		bRelease = TRUE;
	}
}AlarmUnit;

//设置报警信息回调函数
//typedef void(WINAPI *pfuncSetAlarmInfo) (AlarmInfo);
typedef void( *pfuncSetAlarmInfo) (AlarmInfo);
//报警类
class SystemAlarm
{
public:
	enum ENUM_LANGUAGE
	{
		//英文
		ENUM_LANGUAGE_EN = 0,
		//中文
		ENUM_LANGUAGE_CN,
		//当地语言
		ENUM_LANGUAGE_LOCAL,
	};

protected:
	SystemAlarm();

public:
	static SystemAlarm* initance();
	//自动解除报警状态，报警后自动解除报警状态，再次调用可直接向界面发送报警
	void AutomReleaseAlarm(AlarmUnit* p_AlarmUnit);
	//手动解除报警状态，报警后需调用解除报警状态方法，再次报警时才会向界面发送报警
	void NormalReleaseAlarm(AlarmUnit* p_AlarmUnit);
	//解除报警状态
	void ReleaseAlarm(AlarmUnit* p_AlarmUnit);
	//设置报警回调函数
	void SetAlarmCallBackFunction(void* p_pFun);

	//字符串报警
	void Warning(int p_nWarningNo, CString p_strWarning);
	//根据报警编号报警
	void Warning(int P_nWarningNo);
	//根据单元号报警
	void Warning(int P_nWarningNo, int p_nUnitNo);
	//根据站号报警
	void Warning(int P_nWarningNo, int p_nUnitNo,int p_nStationNo);
	//设置语言
	void UpdateLanguage();

private:
	CString getWarningStr(int p_nWarningNo);
private:
	//自身指针
	static SystemAlarm* m_pSystemAlarm;
	//是否实例化标志
	static bool m_bISInitance;
	//全局日志对象
	//CSingletonLoger* m_pCSingletonLogger;
	CThreadLoger * m_pCThreadLoger;
	//界面报警回调函数指针
	pfuncSetAlarmInfo m_pfuncSetAlarmInfo;
	//语言
	ENUM_LANGUAGE m_Language;

	//报警信息语言文件名
	CString m_strWarningFilePatch;
	//报警信息配置文件操作对象
	CINIObject * m_pWarningIni;

	//特定字符
	CString m_strUnit;
	CString m_strStation;
};


