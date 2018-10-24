#include "stdafx.h"
#include "CSecurityVerification.h"
#include "EnDes.h"
#include "../StringOperation/CStringOperation.h"

CSecurityVerification::CSecurityVerification()
{
	memcpy(SetCardkey, "\xFF\xDC\x54\x23\x65\xEF\x34\x12\xDE\xA3\xA3\xB9\x12\x44\x15\x16", 16);
}


CSecurityVerification::~CSecurityVerification()
{
}

//获取随机数
//在主程序中生成随机数字符串，并将该字符串发给Register.DLL生成校验码。
//主程序将Register.DLL生成的校验码发送到Verification方法中比对随机数
//的换算方法是否一致。如一致Register.DLL防伪校验通过。
int CSecurityVerification::getRandom(OUT struVerifiParameter &p_VerifiParameter)
{
	CStringA t_strTarget;
	
	int t_nRet = enum_Verification_OK;
//	BYTE t_carrRandom[33];
//	BYTE t_carrDes[33];

	SYSTEMTIME sysTm;
	CString strTimeTag;//时间标记
	GetLocalTime(&sysTm);
	//strTimeTag.Format(L"%4d-%2d-%2d %2d:%2d:%2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);

	//使用日期、时间和"PIOTEC"混乱顺序组成随机数字符串
	strTimeTag.Format(_T("P[%4dI-%02dO-%02d][%02dT:%02dE:%02d.%03d]C"), sysTm.wYear, sysTm.wMonth, sysTm.wDay, sysTm.wHour, sysTm.wMinute, sysTm.wSecond, sysTm.wMilliseconds);

	CString_TripleDES_EncryptionA( SetCardkey, CStringA(strTimeTag), t_strTarget);

	CStringOperation::CopyCStringToCharA(p_VerifiParameter.c_arrRandom, p_VerifiParameter.nRanLen, t_strTarget.Right(32));
	return t_nRet;
}

//获取验证码
int CSecurityVerification::getVerifi(IN OUT struVerifiParameter &p_VerifiParameter)
{
	int t_nRet = enum_Verification_OK;
	CStringA t_strTarget = "";
	CStringA t_strRandom = "";

	for (int i = 0; i < p_VerifiParameter.nRanLen; i++)
	{
		t_strRandom.AppendChar(p_VerifiParameter.c_arrRandom[i]);
	}
	CString_TripleDES_EncryptionA(SetCardkey, t_strRandom, t_strTarget);

	CStringOperation::CopyCStringToCharA(p_VerifiParameter.c_arrVerifi, p_VerifiParameter.nRanLen, t_strTarget.Right(32));
	return t_nRet;
}

//校验DLL结果
int CSecurityVerification::Verification(IN const struVerifiParameter &p_VerifiParameter)
{
	int t_nRet = enum_Verification_OK;
	struVerifiParameter t_struVerifiParameter;

	memcpy(t_struVerifiParameter.c_arrRandom, p_VerifiParameter.c_arrRandom, p_VerifiParameter.nRanLen);
	getVerifi(t_struVerifiParameter);

	for (int i = 0; i < p_VerifiParameter.nRanLen;i++)
	{
		if (t_struVerifiParameter.c_arrVerifi[i] == p_VerifiParameter.c_arrVerifi[i])
		{ }
		else
		{
			t_nRet = enum_Verification_Failed;
			break;
		}
	}
	return t_nRet;
}
