#include "stdafx.h"
#include "CLoger.h"
#include "../FileOperation/CFileOpertion.h"
#include <direct.h>


CLoger::CLoger(void)
{
	 m_strLogPath =_T("");
	 m_strLogName =_T("");
	 m_strLogDir = _T("");

	 //默认位置程序根目录 
	 m_strLogDir = CFileOpertion::GetModuleFileDir();
	 m_strLogName = CFileOpertion::BuildTimeFileName() + _T(".txt");
	 m_strLogPath = m_strLogDir + _T("Log\\") + m_strLogName;

	 m_nLogSwitch = 0;
}


CLoger::CLoger(CString strLogPath)
{
	CLoger();
	setLogPath(strLogPath);
}

CLoger::~CLoger(void)
{
}

void CLoger::setLogPath(CString strLogPath)
{
	int t_nPos = strLogPath.ReverseFind('\\') + 1;
	int t_nNameLen = strLogPath.GetLength() - t_nPos;
	
	m_strLogPath = strLogPath;
	m_strLogDir = strLogPath.Left(t_nPos);
	m_strLogName = strLogPath.Mid(t_nPos, t_nNameLen);
};


void CLoger::setLogDir(CString p_strLogDir)
{
	m_strLogDir = p_strLogDir;
	m_strLogPath = m_strLogDir + m_strLogName;
}

void CLoger::setSubLogDir(CString p_strLogDir)
{
	m_strLogDir = m_strLogDir + p_strLogDir + _T("\\");
	setLogDir(m_strLogDir);
}

void CLoger::SetLogSwitch(int p_nLogSwitch)
{
	m_nLogSwitch = p_nLogSwitch;
}
//此方法不可用于多参数拼接，只能用来访问其中的一个参数
CStringA CLoger::Format(const char *fmt, va_list& ap)
{
	CStringA strTmp;

	//获得可变参数列表,分析fmt，得出各个参数的类型，也是分析参数中类似”%d %s“的字符串
	//此处因无法在函数内部使用va_start方法访问ap参数列表，又因为无法使用...将参数进行二
	//次专递，所以使用函数对可变参数进行封装无法实现
	//va_start(ap, fmt);
	strTmp.FormatV(fmt, ap);
	va_arg(ap, int);//访问va_list中的一个参数
	//释放资源,必须与va_start成对调用
	//va_end(ap);
	AfxMessageBox(_T("This is test code for va_list !"));
	CStringA strReturn = GetTimeStr() + strTmp;
	return "";
}

/*==============C++不定参数用法示例===========================

char s[1000];
int log(char *s, int size, const char *fmt, ...) //该自定义函数，与系统提供的snprintf()函数相同。
{
va_list ap;
int n=0,size=1000;
va_start(ap, fmt); //获得可变参数列表,分析fmt，得出各个参数的类型，也是分析参数中类似”%d%s“的字符串
n=vsnprintf (s, size, fmt, ap); //写入字符串s
va_end(ap); //释放资源,必须与va_start成对调用
return n; //返回写入的字符个数
}
===============================================================*/

//************************************
// Method:    Wirtelog
// FullName:  CLoger::Wirtelog
// Access:    public 
// Returns:   int 返回字符串长度
// Qualifier: 记录日志信息
// Parameter: ENUM_LOGSWITCH p_ENUM_LOGSWITCH 日志等级
//			  以下两个参数用法与sprintf()相同
// Parameter: const char * fmt 
// Parameter: ...
//************************************
int CLoger::Wirtelog(ENUM_LOGSWITCH p_ENUM_LOGSWITCH, const char *fmt, ...)
{
	int n = 0;
	va_list ap;
	//判断日志开关
	if ((m_nLogSwitch & p_ENUM_LOGSWITCH) > 0)
	{
		CStringA strTmp;

		//获得可变参数列表,分析fmt，得出各个参数的类型，也是分析参数中类似”%d %s“的字符串
		va_start(ap, fmt);
		strTmp.FormatV(fmt, ap);
		//释放资源,必须与va_start成对调用
		va_end(ap);

		CStringA strReturn = GetTimeStr() + strTmp;
		n = strReturn.GetLength();
		WirteToFile(strReturn);
	}
	
	return n; //返回写入的字符个数	
}

void CLoger::WirteToFile(CStringA p_strLogInfo)
{
	FILE *WFile = NULL;
	//创建目录
	int status = _mkdir((CStringA)m_strLogDir);

	critical_section.Lock();
	//打开文件
	//WFile = fopen((CStringA)m_strLogPath, "a");
	fopen_s(&WFile, (CStringA)m_strLogPath, "a");
	if (NULL != WFile)
	{
		fwrite(p_strLogInfo, 1, p_strLogInfo.GetLength(), WFile);
		fwrite("\r\n", 1, 2, WFile);
		fclose(WFile);
	}
	critical_section.Unlock();
}

CStringA CLoger::GetTimeStr()
{
	SYSTEMTIME sysTm;
	CStringA strTimeTag;//时间标记
	GetLocalTime(&sysTm);
	strTimeTag.Format("%4d-%02d-%02d %02d:%02d:%02d.%03d: ", sysTm.wYear, sysTm.wMonth, sysTm.wDay, sysTm.wHour, sysTm.wMinute, sysTm.wSecond, sysTm.wMilliseconds);

	return strTimeTag;
}
