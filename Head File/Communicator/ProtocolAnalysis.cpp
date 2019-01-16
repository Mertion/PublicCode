#include "stdafx.h"
#include "ProtocolAnalysis.h"
#include "FileOperation/CFileOpertion.h"

ProtocolAnalysis::ProtocolAnalysis()
{
	m_strDllDir = CFileOpertion::GetModuleFileDir();
	m_strDllName = _T("ProtocolAnalysis.dll");
	m_strProtocolPackage = _T("ProtocolPackage");
	m_strProtocolUnpacking = _T("ProtocolUnpacking");

	CLoadDLLFunction::LoadDllFile(m_strDllDir, m_strDllName, m_pHINSTANCE);
	CLoadDLLFunction::LoadFuncAddress(m_pHINSTANCE, m_strProtocolPackage, (void**)m_pfunProtocolPackage);
	CLoadDLLFunction::LoadFuncAddress(m_pHINSTANCE, m_strProtocolUnpacking, (void**)m_pfunProtocolUnpacking);
}

ProtocolAnalysis::~ProtocolAnalysis()
{

}

int ProtocolAnalysis::exProtocolPackage(IN const byte* p_byteSourceData, IN int p_nSourceDataLen, OUT byte* p_bytearrCMD, OUT int* p_pCMDLen)
{
	int ret = 0;
	if (CLoadDLLFunction::CheckFuncPinterISNULL(m_pfunProtocolPackage, m_strProtocolPackage) == ERROR_LOADDLLFILE_SUCCESS)
	{
		ret = m_pfunProtocolPackage(p_byteSourceData, p_nSourceDataLen, p_bytearrCMD, p_pCMDLen);
	}
	return ret;
}

int ProtocolAnalysis::exProtocolUnpacking(IN OUT byte* p_pbyteSourceData, IN OUT int* p_pnSourceDataLen, OUT byte* p_bytearrCMD, OUT int* p_pCMDLen)
{
	int ret = 0;
	if (CLoadDLLFunction::CheckFuncPinterISNULL(m_pfunProtocolUnpacking, m_strProtocolUnpacking) == ERROR_LOADDLLFILE_SUCCESS)
	{
		ret = m_pfunProtocolUnpacking(p_pbyteSourceData, p_pnSourceDataLen, p_bytearrCMD, p_pCMDLen);
	}
	return ret;
}

