#include "stdafx.h"
#include "Singleton.h"


Singleton* Singleton::p = new Singleton;
Singleton* Singleton::initance()
{
    return p;
}