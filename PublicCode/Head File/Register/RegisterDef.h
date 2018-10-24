#pragma once

//授权类型
enum enum_AuthorizationType
{
	enum_AuthorizationType_None = 0,					//0-无授权
	enum_AuthorizationType_Normal,						//普通授权
	enum_AuthorizationType_Emergency,					//应急授权
	enum_AuthorizationType_ProductionAuthorization,		//产量授权
	enum_AuthorizationType_DemoMode,					//演示授权


};

//产品授权码
enum enum_ProductCode
{
	enum_ProductCode_PersoPDM = 1,		//个人化数据机（包括：5500系列、8500系列）
	enum_ProductCode_120,				//120系列
};
//功能授权码
enum enum_FunctonCode
{
	enum_FunctonCode_IC = 1,			//IC
	enum_FunctonCode_Laser,				//激光
	enum_FunctonCode_Contactless,		//非接
	enum_FunctonCode_OCR,				//OCR识别
	enum_FunctonCode_8500Laser,			//8500高速激光
};

//功能状态码
enum enum_FunctionstatusCode
{
	enum_FunctionstatusCode_None = 0,	//不可用
	enum_FunctionstatusCode_Normal,		//普通，需读取参数
	enum_FunctionstatusCode_Unlimited,	//无限制
};