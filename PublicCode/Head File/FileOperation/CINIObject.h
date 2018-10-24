#pragma once
#include <afxmt.h>
//配置文件类，用于操作单个配置文件
//用法:
//1. 通过SetINIFileName或SetINIFilePath方法设置配置文件信息。
//2. 通过相应的get/set方法设置或读取配置文件中的信息。
class CINIObject
{
public:
	enum ENUM_INIERR
	{
		//操作成功
		ENUM_INIERR_SUCCESS = 0,
		//获得文件路径失败，可能路径错误或文件不存在
		ENUM_INIERR_GETMODULEPATCH_FAIL,
		//文件不存在
		ENUM_INIERR_FILENOTFIND
	};
private:
	CString m_strINIFilePatch;
	CString m_strINIFileName;

	CCriticalSection critical_section;
public:
	CINIObject(void);
	~CINIObject(void);


	//设置配置文件名称
	int SetINIFileName(IN CString p_strINIFileName);
	//获取文件路径
	void SetINIFilePath(IN CString p_strINIFilePatch);
	//获取int型数据
	int GetINIFileInt(IN CString p_strAppName, IN CString p_strKEY, IN int p_nDefultVal, OUT int &p_nVal);
	//获取string型数据
	int GetINIFileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strDefult, IN int p_nSize, OUT CString &p_strReturnedString);
	//获取string型数据
	int GetINIFileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strDefult, IN int p_nSize, OUT TCHAR *p_strReturnedString);
	//设置int型数据
	int SetINIFileInt(IN CString p_strAppName, IN CString p_strKEY, IN int p_nVal);
	//设置string型数据
	int SetINIFileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strVal);

private:
	//获取文件路径
	int GetINIFilePatch(IN CString p_strIniFileName, OUT CString &p_strIniPath);
};