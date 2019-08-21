#pragma once
#pragma warning(disable:4996)

#include <algorithm>
#include <cvaux.h>
#include <math.h>  
#include <cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv.hpp>

#include <process.h> 
#include <cvaux.h>
#include <cv.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv.hpp>
#include "cxcore.hpp"
#include "build\include\opencv2\core\core.hpp"
#include <cxcore.h>
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include <opencv2/ml/ml.hpp>

using namespace cv;

class IplImageEx
{
public:
	IplImageEx(CvSize size, int depth, int channels);
	~IplImageEx();

	IplImage* GetImage();
	int GetVal(int nCol, int nRow);
	
private:
	typedef int(IplImageEx::* FuncGetVal)(int nCol, int nRow);
	int GetVal8(int nCol, int nRow);
	int GetVal16(int nCol, int nRow);
private:
	FuncGetVal pFuncGetVal = NULL;
	IplImage* m_pIplImage = NULL;
};

