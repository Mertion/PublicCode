#pragma once

#include "FileOperation/CINIObject.h"

class AlarmIni
{
public:
private:
	AlarmIni();
public:
	static AlarmIni* initance();
	
	//获取日志开关
	int getLogSwitch();
	// 获取当前语言
	int getLanguage();
	//设置当前语言
	void setLanguage(int p_nLanguage);
private:
	static AlarmIni* m_psysini;
	CINIObject* m_pCINIObject = NULL;
};

