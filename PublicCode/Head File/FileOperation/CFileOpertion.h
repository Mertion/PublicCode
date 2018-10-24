#pragma once
//enum ERROR_LOADDLLFILE
//{
//	ERROR_LOADDLLFILE_NOTINIT = -1,
//	ERROR_LOADDLLFILE_SUCCESS = 0,
//	ERROR_LOADDLLFILE_LOADDLLFAILED,
//	ERROR_LOADDLLFILE_LOADFUNCTIONFAILED
//};



class CFileOpertion
{
public:
	//CFileOpertion();
	//~CFileOpertion();

	//获得运行程序目录
	static CString GetModuleFileDir();
	//查找文件是否存在
	static bool FindFile(char * p_cstrFilePath);
	//以时间生成文件名
	static CString BuildTimeFileName();
	//定期清理文件
	static void ClearFile(CString p_strDir, int p_nDays);
};

