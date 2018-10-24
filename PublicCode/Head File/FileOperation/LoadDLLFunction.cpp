#include "stdafx.h"
#include "LoadDLLFunction.h"

//CString CLoadDLLFunction::GetModuleFileDir()
//{
//	TCHAR lpFilePath[MAX_PATH];
//	::GetModuleFileName(NULL, lpFilePath, MAX_PATH);
//	(_tcsrchr(lpFilePath, _T('\\')))[1] = 0;
//	CString strExePath = _T("");
//	strExePath.Format(_T("%s"), lpFilePath);
//	return strExePath;
//}

//
//CLoadDLLFunction::CLoadDLLFunction()
//{
//}
//
//
//CLoadDLLFunction::~CLoadDLLFunction()
//{
//}

int CLoadDLLFunction::LoadDllFile(IN CString strFileDir, IN CString strFileName, OUT HINSTANCE &pHINSTANCE)
{
	return LoadDllFile((strFileDir + strFileName), pHINSTANCE);
}

int CLoadDLLFunction::LoadDllFile(IN CString strFilePatch, OUT HINSTANCE &pHINSTANCE)
{
	int nRet = ERROR_LOADDLLFILE_NOTINIT;
	//¼ÓÔØPCMSDevJobData.dll
	//CString str = _T("") ;
	//str.Format(_T("D:\\010-Branches-8500_PCMSV2.0\\003-Ô´´úÂë\\Bin\\"));
	pHINSTANCE = LoadLibrary(strFilePatch);
	//pHINSTANCE = LoadLibrary(str + strFileName);

	if (NULL == pHINSTANCE)
	{
		CString strErr = _T("Load ") + strFilePatch + _T(" is failed!");
		//AfxMessageBox(strErr);
		::AfxMessageBox(strErr);
		//MessageBox(NULL, strErr, _T("Error"), MB_OK | MB_ICONERROR);
		return ERROR_LOADDLLFILE_LOADDLLFAILED;
	}
	else
	{
		nRet = ERROR_LOADDLLFILE_SUCCESS;
	}

	return nRet;
}

int CLoadDLLFunction::FreeDLLFile(IN OUT HINSTANCE &pHINSTANCE)
{
	if (NULL != pHINSTANCE)
	{
		FreeLibrary(pHINSTANCE);
	}
	pHINSTANCE = NULL;

	return ERROR_LOADDLLFILE_SUCCESS;
}

int CLoadDLLFunction::LoadFuncAddress(IN HINSTANCE &pHINSTANCE, IN CString p_strDescription, OUT void ** pFunc)
{
	int nRet = ERROR_LOADDLLFILE_NOTINIT;
	CStringA strDescription = (CStringA)p_strDescription;
	*pFunc = NULL;
	*pFunc = GetProcAddress(pHINSTANCE, strDescription);
	nRet = CheckFuncPinterISNULL(*pFunc, p_strDescription);
	return nRet;
}

int CLoadDLLFunction::CheckFuncPinterISNULL(IN void * p_pFunc, IN CString p_strDescription)
{
	int nRet = ERROR_LOADDLLFILE_NOTINIT;
	CString strDescription = _T("Load ") + p_strDescription + _T("() is failed!");

	if (NULL == p_pFunc)
	{
		AfxMessageBox(strDescription);
		nRet = ERROR_LOADDLLFILE_LOADFUNCTIONFAILED;
	}
	else
	{
		nRet = ERROR_LOADDLLFILE_SUCCESS;
	}

	return nRet;
}
