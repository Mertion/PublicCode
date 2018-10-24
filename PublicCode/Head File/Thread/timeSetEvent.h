#pragma once

#include "stdafx.h"
#include <Mmsystem.h>

//启动多媒体定时器
 void SYS_BeginTimeEvent(_In_ LPTIMECALLBACK fptc
	, _Out_ UINT& p_pTimeEventID
	, _In_ LPTHREAD_START_ROUTINE lpStartAddress
	, _Out_ HANDLE& m_MainThread
	, _In_ int p_pMilliSecond);

//结束多媒体定时器
void SYS_EndTimeEvent(_In_ UINT p_pTimeEventID);