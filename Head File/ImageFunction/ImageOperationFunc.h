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

//图像翻转方式枚举
typedef enum
{
	ReversalModeHorizontal, // 水平翻转  
	ReversalModeVertical    // 垂直翻转  
}ReversalMode;

// 图像翻转(镜像)  
VOID ImageReversal(IN OUT IplImage **p_iplImage, IN ReversalMode mode);
//转换iplimage到bmp图像
void iplImageToBmp(IN IplImage *ipl, IN int nBpp, OUT byte* p_pbyteBmp, OUT int& p_nBmpSize);
//提取二值图
int Binarization(Mat p_mat, int p_nBinarizationThreshold, Mat* p_matDst);
