#pragma once
//所有工程通用头文件

enum ENUM_LANGUAGE
{
	//英文
	ENUM_LANGUAGE_EN = 0,
	//中文
	ENUM_LANGUAGE_CN,
	//当地语言
	ENUM_LANGUAGE_LOCAL,
};
//执行结果
enum ENUM_RESULT
{
	//未执行
	ENUM_RESULT_NONE = -1,
	//成功
	ENUM_RESULT_SUCCESS,
	//失败
	ENUM_RESULT_FAILED,
};


//执行结果结构体
typedef struct _structResult
{
	//是否完成 
	bool bIsDone;
	//是否成功
	bool bIsSuccess;
	_structResult()
	{
		bIsDone = false;
		bIsSuccess = false;
	}
}structResult;


