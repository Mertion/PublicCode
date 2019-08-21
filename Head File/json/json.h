#ifndef JSON_JSON_H_INCLUDED
# define JSON_JSON_H_INCLUDED

# include "autolink.h"
# include "value.h"
# include "reader.h"
# include "writer.h"
# include "features.h"


//#include "json/json.h" 


//运行库模式宏定义说明
//  Single 	Threaded			/ ML	LIBC(none)
//  Static 	MultiThread			/ MT	LIBCMT	_MT
//  Dynamic Link(DLL)			/ MD	MSVCRT	_MT and _DLL
//  Debug 	Single Threaded		/ MLd	LIBCD	_DEBUG
//  Debug 	Static MultiThread	/ MTd	LIBCMTD	_DEBUG and _MT
//  Debug 	Dynamic Link(DLL)	/ MDd	MSVCRTD	_DEBUG, _MT, and _DLL

//开发环境宏定义说明
//Visual Studio2019 _MSC_VER != 1923
//Visual Studio2017 _MSC_VER != 1914
//Visual Studio2015 _MSC_VER != 1900
//Visual Studio2013 _MSC_VER != 1800
//Visual Studio2012 _MSC_VER != 1700
//Visual Studio2010 _MSC_VER != 1600
//Visual Studio2008 _MSC_VER != 1500
//Visual Studio2005 _MSC_VER != 1400
//Visual Studio2003 _MSC_VER != 1300
//Visual Studio 6   _MSC_VER != 1200

//lzg 20160308 start
//根据编译器和运行库模式加载不同JSON库
#if (_MSC_VER != 1800) && (_MSC_VER != 1400) && (_MSC_VER != 1914)&& (_MSC_VER != 1923)
#error Please build the lib switch for model
#endif

#ifdef _DEBUG  
#ifndef _WIN64  

#if defined(_MT) && defined(_DLL)

#if (_MSC_VER == 1800)
#pragma comment(lib,"./Lib/json_vc12_libmdd") 
#endif // _MSC_VER = 1800 
#if (_MSC_VER == 1400)
#pragma comment(lib,"./Lib/json_vc8_libmdd")  
#endif // _MSC_VER = 1400 
#if (_MSC_VER == 1914)
#pragma comment(lib,"./Lib/json_vc14_libmdd") 
#endif // _MSC_VER = 1800 
#else
#if (_MSC_VER == 1800)
#ifdef  UNICODE 
#pragma comment(lib,"./json_vc12_libmtd_Unicode") 
//#pragma comment(lib,"./PublicCode/Head File/json/Lib/json_vc12_libmtd_Unicode")
//#pragma comment(lib,"./json/Lib/json_vc12_libmtd_Unicode")
#else
#pragma comment(lib,"./json_vc12_libmtd") 
#endif
#endif // _MSC_VER = 1800 
#if (_MSC_VER == 1400)
#pragma comment(lib,"./Lib/json_vc8_libmtd")
//#pragma comment(lib,"../../../Include/Lib/JsonLib/json_vc8_libmtd")  
#endif // _MSC_VER = 1400 
#if (_MSC_VER == 1914)
#pragma comment(lib,"./Lib/json_vc14_libmtd")
#endif 
#endif

//#include "../../../Include/Lib/JsonLib/SCM3000Protocol.h"

#else  
#if defined(_MT) && defined(_DLL)
#if (_MSC_VER == 1800)
#ifdef  UNICODE 
#pragma comment(lib,"./Lib/json_vc12_libmdd_Unicode_x64") 
//#pragma comment(lib,"json_vc12_libmdd_Unicode_x64") 
#else	//UNICODE
#pragma comment(lib,"./Lib/json_vc12_libmdd_x64") 
#endif // _MSC_VER = 1800 
#endif 
#else
#ifdef  UNICODE 
#if (_MSC_VER == 1800)
#pragma comment(lib,"json_vc12_libmtd_Unicode_x64")
#endif 
#else	//UNICODE
#if (_MSC_VER == 1800)
#pragma comment(lib,"json_vc12_libmtd_x64")
#endif 
#endif

#endif
//#error Please build the lib switch for model
//#pragma comment(lib,"./Lib/json_mtd_x64.lib")  
#endif  

#else  
#ifndef _WIN64  
#error Please build the lib switch for model
#pragma comment(lib,"./Lib/json_mt.lib")  
#else  
#error Please build the lib switch for model
#pragma comment(lib,"./Lib/json_mt_x64.lib")  
#endif  
#endif
//lzg 20160308 end

#endif // JSON_JSON_H_INCLUDED
