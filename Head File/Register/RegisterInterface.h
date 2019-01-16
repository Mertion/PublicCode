#pragma  once
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MATUREAPPROACH_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MATUREAPPROACH_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.



#include "./PUB/DataEncryption/CSecurityVerification.h"
#include "stdafx.h"

//#define PTREGISTER_EXPORTS
#ifdef PTREGISTER_EXPORTS
#define PTREGISTER_API __declspec(dllexport)
#else
#define PTREGISTER_API __declspec(dllimport)
#endif

enum EnumRegisterMessage	//消息枚举
{
	EnumRegisterMessage_OK = 0x00,			//成功
	EnumRegisterMessage_Failed, 			//失败
	EnumRegisterMessage_NoVerifi,			//未调用防伪接口
	EnumRegisterMessage_ProcessError,		//流程错误，该错误不给出明确提示信息，防止恶意破解
};

enum EnumStage		//记录生产数量时需该参数辅助
{
	ST_PROD = 0x00,	//生产中
	ST_END = 0x01,	//生产结束
};

typedef int (_stdcall* pSysRegister)(unsigned long& lChipsCount,unsigned char* ucChipsCount);
typedef int (_stdcall* pInitDongle)(int p_cSoftwareVer);
typedef int (_stdcall* pShowDongleDlg)(void);
typedef int (_stdcall* pUnInitDongle)(void);
typedef int (_stdcall* pSetChipsCount)(unsigned char* ucChipsCount,int ilen,unsigned long lChipsCount,EnumStage nSTAGE);
typedef int (_stdcall* pCreatResetCountSN)(unsigned char* HardwareID,unsigned char* CountSN,int& ilen,unsigned long lCount);
typedef int (_stdcall* pCheckChipsCount)(unsigned long lChipsCount,unsigned char* HardwareID,unsigned char* ChipsCountSN,int ilen);
typedef int (_stdcall* pExecuteDongleApp)(char* p_strAppName,
										  BYTE *p_cInBuf,DWORD p_lInBufLen,
										  BYTE *p_cOutBuf,DWORD p_lOutBufLen);
typedef int(_stdcall* pExgetVerifi)(struVerifiParameter &p_VerifiParameter);
typedef int(_stdcall* pExgetFunctionInfo)(IN int p_nFunctionID, OUT int p_nFunctionState, OUT BYTE *p_pFunctionInfo);

extern "C" PTREGISTER_API int  __stdcall  exSysRegister(unsigned long& lChipsCount,unsigned char* ucChipsCount);	//注册生产数量
extern "C" PTREGISTER_API int  __stdcall  exInitDongle(int p_cSoftwareVer);	//初始化狗连接，参数软件类型号
extern "C" PTREGISTER_API int  __stdcall  exUnInitDongle();					//卸载加密狗
extern "C" PTREGISTER_API int  __stdcall  exShowDongleDlg();				//弹出授权信息窗口
extern "C" PTREGISTER_API int  __stdcall  exSetChipsCount(unsigned char* ucChipsCount,int ilen,unsigned long lChipsCount,EnumStage nSTAGE);//设置生产数量
extern "C" PTREGISTER_API int  __stdcall  exCreatResetCountSN(unsigned char* HardwareID,unsigned char* CountSN,int& ilen,unsigned long lCount);//生成生产数量清空码
extern "C" PTREGISTER_API int  __stdcall  exCheckChipsCount(unsigned long lChipsCount,unsigned char* HardwareID,unsigned char* ChipsCountSN,int ilen);//检查芯片数量
extern "C" PTREGISTER_API int  __stdcall  exExecuteDongleApp(char* p_strAppName,
															 BYTE *p_cInBuf,DWORD p_lInBufLen,
															 BYTE *p_cOutBuf,DWORD p_lOutBufLen);		//执行狗内程序

extern "C" PTREGISTER_API int  __stdcall  exgetVerifi(struVerifiParameter &p_VerifiParameter);			//获取随机数验证码
extern "C" PTREGISTER_API int  __stdcall  exgetFunctionInfo(IN int p_nFunctionID,OUT int &p_nFunctionState,OUT BYTE *p_pFunctionInfo);	//获取锁内授权功能信息

