#pragma region 

#pragma region 
#pragma warning(disable:4996)



//退出系统
//ReSetWindows(EWX_LOGOFF, false);//注销
//ReSetWindows(EWX_REBOOT, true);//重启
//ReSetWindows(EWX_SHUTDOWN, true);//关机
BOOL ReSetWindows(DWORD dwFlags, BOOL bForce);


//提升系统权限
BOOL EnableShutDownPriv();
