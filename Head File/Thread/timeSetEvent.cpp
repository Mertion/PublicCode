///////////////////////////////////////////////////////////
//  timeSetEvent.cpp
//  
//  Created on:      01-11月-2017 18:19:00
//  Original author: Lzg
///////////////////////////////////////////////////////////
#include "stdafx.h"
#include "timeSetEvent.h"
#include <minwindef.h>

#pragma comment(lib,"comctl32.lib") 
#pragma comment(lib,"winmm.lib")
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
//***************************************************************************************
//                             ****多媒体定时器变量定义****                            **
//***************************************************************************************
//定义1ms时钟间隔，以ms为单位 
//# define ONE_MILLI_SECOND 1  
//定义时钟分辨率，以ms为单位 
# define TIMER_ACCURACY 1  
UINT wTimerRes_1ms;//定义时间间隔
UINT wAccuracy;//定义分辨率 
//20120822
UINT TimerID_DepressCard_Up, TimerID_DepressCard_Down;
const int SOFTWARETYPE = 1;    //1:原架构软件版本，0：新架构软件版本
//使用线程模式调试
#define  MC_MY_DEBUG  1
//****************************************************************************************


//*********************************************************************************
//*                                                                              **
//*                         创建多线程并运行系统主函数                           **
//*                                                                              **
//*********************************************************************************
 void SYS_BeginTimeEvent(_In_ LPTIMECALLBACK fptc, _Out_ UINT& p_pTimeEventID
	, _In_ LPTHREAD_START_ROUTINE lpStartAddress, _Out_ HANDLE& m_MainThread
	, _In_ int p_pMilliSecond = 1)
{
	//模拟调试时使用线程模式
	if (MC_MY_DEBUG == 1)
	{
		//创建主线程 或使用多媒体定时器
		m_MainThread = CreateThread(NULL, 0, lpStartAddress, NULL, 0, NULL);
	}
	else
	{
		wTimerRes_1ms = p_pMilliSecond;// 给时间间隔变量赋值 
		TIMECAPS tc;
		//利用函数timeGetDevCaps取出系统分辨率的取值范围，如果无错则继续 
		if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) == TIMERR_NOERROR)
		{
			// 分辨率的值不能超出系统的取值范围 
			wAccuracy = min(max(tc.wPeriodMin, TIMER_ACCURACY), tc.wPeriodMax);
			//调用timeBeginPeriod函数设置定时器的分辨率 
			timeBeginPeriod(wAccuracy);
		}

		if (1 == SOFTWARETYPE)
		{
			//启动多媒体定时器
			p_pTimeEventID = timeSetEvent(wTimerRes_1ms, wAccuracy,
				fptc,
				(DWORD)SYS_BeginTimeEvent, TIME_PERIODIC);
		}

	}

}


//结束主线程
void SYS_EndTimeEvent(_In_ UINT p_pTimeEventID)
{
	//模拟调试时使用线程模式
	if (MC_MY_DEBUG == 1)
	{
		//m_bTreadCtl = true;
	}
	else
	{
		timeKillEvent(p_pTimeEventID);
	}
}
