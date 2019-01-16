#pragma once
#include "CLoger.h"

class CSingletonLoger:public CLoger
{
protected:
	CSingletonLoger();

public:
	static CSingletonLoger* initance();

private:
	static CSingletonLoger* m_pSingletonLogger;

};


