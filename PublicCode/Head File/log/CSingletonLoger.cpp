#include "stdafx.h"
#include "CSingletonLoger.h"


CSingletonLoger::CSingletonLoger(void)
{
	
}
CSingletonLoger* CSingletonLoger::m_pSingletonLogger = new CSingletonLoger;
CSingletonLoger* CSingletonLoger::initance()
{
	return m_pSingletonLogger;
}
