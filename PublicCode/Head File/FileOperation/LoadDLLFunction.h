#pragma once
enum ERROR_LOADDLLFILE
{
	//DLL未初始化
	ERROR_LOADDLLFILE_NOTINIT = -1,	
	//DLL加载成功
	ERROR_LOADDLLFILE_SUCCESS = 0,
	//DLLl加载失败
	ERROR_LOADDLLFILE_LOADDLLFAILED,
	//函数加载失败
	ERROR_LOADDLLFILE_LOADFUNCTIONFAILED
};


//动态加载DLL类
//使用方法
//  1. 先调用LoadDllFile加载DLL
//  2. 使用LoadFuncAddress加载所有要用到的函数
//  3. 在执行DLL内的方法时，先调用CheckFuncPinterISNULL校验方法是否被加载，然后再调用相应方法
class CLoadDLLFunction
{
public:
	//CLoadDLLFunction();
	//~CLoadDLLFunction();

	/*static CString GetModuleFileDir();*/
	static int LoadDllFile(IN CString strFileDir, IN CString strFileName, OUT HINSTANCE &pHINSTANCE);
	static int LoadDllFile(IN CString strFilePatch, OUT HINSTANCE &pHINSTANCE);
	static int FreeDLLFile(IN OUT HINSTANCE &pHINSTANCE);
	static int LoadFuncAddress(IN HINSTANCE &pHINSTANCE, IN CString p_strDescription, OUT void ** pFunc);
	static int CheckFuncPinterISNULL(IN void * p_pFunc, IN CString p_strDescription);
};

