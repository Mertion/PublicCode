#include "stdafx.h"
#include "CFileOpertion.h"
#include <vector>

using namespace std;

CString CFileOpertion::GetModuleFileDir()
{
	TCHAR lpFilePath[MAX_PATH];
	::GetModuleFileName(NULL, lpFilePath, MAX_PATH);
	(_tcsrchr(lpFilePath, _T('\\')))[1] = 0;
	CString strExePath = _T("");
	strExePath.Format(_T("%s"), lpFilePath);
	return strExePath;
}

bool CFileOpertion::FindFile(char * p_cstrFilePath)
{
	CFileFind cFinder;
	CStringA strFormat;

	strFormat.Format("%s", p_cstrFilePath);
	CStringW strFilePath;
	strFilePath = strFormat;
	BOOL bFound = cFinder.FindFile(strFilePath);

	if (bFound)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CString CFileOpertion::BuildTimeFileName()
{
	CString t_strFirstTime = _T("");
	//获取初始化时系统时间
	SYSTEMTIME sysTm;
	::GetLocalTime(&sysTm);
	t_strFirstTime.Format(_T("%4d-%02d-%02d %02d-%02d-%02d_%03d"), sysTm.wYear, sysTm.wMonth, sysTm.wDay, sysTm.wHour, sysTm.wMinute, sysTm.wSecond, sysTm.wMilliseconds);

	return t_strFirstTime;
}

void CFileOpertion::ClearFile(CString p_strFileName, int p_nDays)
{
	vector<CStringA> FileName;
	vector<CStringA> FilePath;
	CFileFind t_Finder;
	CStringA t_strPath;
	CString t_strFileName;
	CString t_strDir;
	t_strDir = GetModuleFileDir();
	t_strDir = t_strDir + p_strFileName + _T("//");
	BOOL t_bWorking = t_Finder.FindFile(t_strDir + _T("*.*"));

	while (t_bWorking)
	{
		t_bWorking = t_Finder.FindNextFile();
		t_strPath = (CStringA)t_Finder.GetFilePath();
		t_strFileName = t_Finder.GetFileName();
		CStringA t_strDate = (CStringA)t_strFileName.Left(10);
		t_strDate.Replace("-", "");
		/*	strFileName.Replace(_T("-"),_T(""));
		CString strDate = strFileName.Left(8);*/
		FileName.push_back(t_strDate);
		FilePath.push_back(t_strPath);
		//strPath就是所要获取Test目录下的文件夹和文件（包括路径）  
		//m_List.AddString(strPath);  
	}
	//当前系统时间
	CTime t_ctimeNowTime; t_ctimeNowTime = CTime::GetCurrentTime();
	for (int i = 2; i < FileName.size(); i++)
	{
		CStringA t_strTime = FileName[i];
		int t_nYear, t_nMonth, t_nDay;
		BYTE t_byteByte[5];
		//get year 
		memset(t_byteByte, 0, sizeof(t_byteByte));
		t_byteByte[0] = t_strTime[0];
		t_byteByte[1] = t_strTime[1];
		t_byteByte[2] = t_strTime[2];
		t_byteByte[3] = t_strTime[3];
		t_nYear = atoi((char *)t_byteByte);

		//get month 
		memset(t_byteByte, 0, sizeof(t_byteByte));
		t_byteByte[0] = t_strTime[4];
		t_byteByte[1] = t_strTime[5];
		t_nMonth = atoi((char *)t_byteByte);

		//get day 
		memset(t_byteByte, 0, sizeof(t_byteByte));
		t_byteByte[0] = t_strTime[6];
		t_byteByte[1] = t_strTime[7];
		t_nDay = atoi((char *)t_byteByte);
		CTime t_ctimeFileTime(t_nYear, t_nMonth, t_nDay, 0, 0, 0);
		CTimeSpan TimeDiff = t_ctimeNowTime - t_ctimeFileTime;
		int t_nDays = (int)TimeDiff.GetDays();
		if (t_nDays >= p_nDays)
		{
			DeleteFile((CStringW)FilePath[i]);
		}
	}
	t_Finder.Close();
}

//
//CFileOpertion::CFileOpertion()
//{
//}
//
//
//CFileOpertion::~CFileOpertion()
//{
//}
