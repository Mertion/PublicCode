#include "stdafx.h"
#include "ImageOperationFunc.h"

// 图像翻转(镜像)  
VOID ImageReversal(IN OUT IplImage **p_iplImage, IN ReversalMode mode)
{
	//Mat src = imread("lena.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat src(*p_iplImage, true);
	//imshow("src", src);
	Mat dst;
	dst.create(src.size(), src.type());
	Mat map_x;
	Mat map_y;
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);
	if (ReversalModeHorizontal == mode)
	{
		for (int i = 0; i < src.rows; ++i)
		{
			for (int j = 0; j < src.cols; ++j)
			{
				map_x.at<float>(i, j) = (float)(src.cols - j);
				map_y.at<float>(i, j) = (float)i;  //水平  
			}
		}
	} 
	else
	{
		for (int i = 0; i < src.rows; ++i)
		{
			for (int j = 0; j < src.cols; ++j)
			{
				map_x.at<float>(i, j) = (float) j ;    
				map_y.at<float>(i, j) = (float) (src.rows - i) ;  //垂直  
			}
		}
	}
	remap(src, dst, map_x, map_y, CV_INTER_LINEAR);
	//imshow("dst", dst);
	cvCopy(&IplImage(dst), *p_iplImage);
	//imwrite("invert2.jpg", dst);
	//waitKey(2);
	//system("pause");
	
}
//--------------------------------------------------------------------------- 
//转换iplimage到bmp图像
void iplImageToBmp(IN IplImage *ipl, IN int nBpp,OUT byte* p_pbyteBmp,OUT int& p_nBmpSize)
{
	BITMAPFILEHEADER bmpHeader;
	bmpHeader.bfType = 0x4d42;
	bmpHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + ipl->width * ipl->height * 3;
	bmpHeader.bfReserved1 = 0;
	bmpHeader.bfReserved2 = 0;
	bmpHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	BITMAPINFOHEADER bmpInfoHeader;
	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfoHeader.biWidth = ipl->width;
	bmpInfoHeader.biHeight = ipl->height;
	bmpInfoHeader.biPlanes = 1;
	bmpInfoHeader.biBitCount = nBpp;
	bmpInfoHeader.biCompression = BI_RGB;
	bmpInfoHeader.biSizeImage = (ipl->width*nBpp + 31) / 32 * 4 * ipl->height;
	bmpInfoHeader.biXPelsPerMeter = 100;
	bmpInfoHeader.biYPelsPerMeter = 100;
	bmpInfoHeader.biClrUsed = 0;
	bmpInfoHeader.biClrImportant = 0;


	DWORD dwInfoSize = ipl->width*ipl->height*nBpp / 8;
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, sizeof(bmpHeader) + sizeof(bmpInfoHeader) + dwInfoSize);
	BYTE *pvData = (BYTE*)GlobalLock(hGlobal);
	memcpy(pvData, &bmpHeader, sizeof(bmpHeader));
	memcpy(pvData + sizeof(bmpHeader), &bmpInfoHeader, sizeof(bmpInfoHeader));
	memcpy(pvData + sizeof(bmpHeader) + sizeof(bmpInfoHeader), ipl->imageData, dwInfoSize);
	GlobalUnlock(hGlobal);

	p_nBmpSize = sizeof(bmpHeader) + sizeof(bmpInfoHeader) + ipl->imageSize;
	memcpy(p_pbyteBmp, pvData, p_nBmpSize);

	////记录测试图片
	//WriteBMPFile(pvData, sizeof(bmpHeader) + sizeof(bmpInfoHeader) + ipl->imageSize);
	
	//释放资源
	GlobalFree(hGlobal); // 使用Bitmap完后，需要释放资源，以免造成内存泄漏。  
}

//提取二值图
int Binarization(Mat p_mat, int p_nBinarizationThreshold, Mat* p_matDst)
{
	*p_matDst = Mat::zeros(cvSize(p_mat.cols, p_mat.rows), CV_8UC1);

	//二值化
	for (int y = 0; y < p_mat.rows; y++)
	{
		for (int x = 0; x < p_mat.cols; x++)
		{
			int t_nVal1 = p_mat.at<ushort>(y, x);

			if (t_nVal1 < p_nBinarizationThreshold)
			{
				p_matDst->at<uchar>(y, x) = 0;
			}
			else
			{
				//直接二值化
				p_matDst->at<uchar>(y, x) = 255;
			}
		}
	}
	return 0;
}

int IsGreaterMinimumBrightness(Mat* p_src, Mat& p_Make, std::vector<std::vector<cv::Point> >::iterator itc
	, int m_nMinBrightness, int m_nMaxGrayscale, int m_nMinBrightnessPixelsTotal, int m_nDefectAreaMin, int m_nDefectAreaMax)
{
	int t_nType = p_src->type();
	//遍历轮廓内像素点
	Rect rect = boundingRect(*itc);
	int t_nPixelsCount = 0;
	int t_nNonZeroPointCout = 0;
	int t_nAvg = 0;
	int t_nCounter = 0;

	for (int y = rect.y; y < (rect.y + rect.height); y++)
	{
		for (int x = rect.x; x < (rect.x + rect.width); x++)
		{
			cv::Point t_point;
			t_point.x = x;
			t_point.y = y;
			int nVal = p_Make.at<uchar>(y, x);
			//判断点是否在轮廓内, 为了提高运算效率不再判断点是否在轮廓内
			//if (pointPolygonTest(*itc, t_point, 0) >= 0)
			if (nVal > 0)
			{
				int t_nLight = 0;

				t_nLight = p_src->at<ushort>(y, x);

				//如果亮度大于最小亮度亮度计数++
				if (t_nLight > m_nMinBrightness)
				{
					t_nPixelsCount++;
				}
				//如果亮度大于二值化门槛亮度，非零点计数++
				if (t_nLight >= m_nMaxGrayscale)
				{
					t_nNonZeroPointCout++;
				}

				t_nCounter++;
				t_nAvg += t_nLight;
			}
		}
	}

	//求平均重量
	if (t_nCounter > 0)
	{
		t_nAvg /= t_nCounter;
	}
	else
	{
		t_nAvg = 0;
	}

	//如果同时满足最小亮度和面积条件，认为是缺陷
	if ((t_nPixelsCount > m_nMinBrightnessPixelsTotal)
		&& (t_nNonZeroPointCout > m_nDefectAreaMin && t_nNonZeroPointCout < m_nDefectAreaMax))
	{
		return true;
	}
	return false;
}

int DefectRecognition(Mat* p_mat, Mat* p_matBinaryvalue, const int p_nOffsetX, const int p_nOffsetY, int p_nMin, int p_nMax)
{
	Mat t_mat = p_matBinaryvalue->clone();
	//确定连通体位置
	std::vector<std::vector<cv::Point> >contours;
	//Mat Src(t_matThreshold, true);
	findContours(t_mat, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	int nSize = contours.size();
	int t_nThreads = 10;
#pragma omp parallel for num_threads(t_nThreads)
	for (int i = 0;i<nSize;i++)
	{
		std::vector<cv::Point>* ptr = &contours.at(i)  ;
		if ((ptr->size() < p_nMin) || (ptr->size() > p_nMax))
		{
			//在缺陷图上将不符合条件的部分填充成黑色
			cv::drawContours(*p_mat, contours, i, cv::Scalar(0), CV_FILLED, 8);
		}
	}

	//////轮廓过滤,去掉小于最小尺寸的轮廓
	//std::vector<std::vector<cv::Point> >::iterator itc = contours.begin();
	//int nIndex = 0;
	//while (itc != contours.end())
	//{
	//	if ((itc->size() < p_nMin) || (itc->size() > p_nMax))
	//	{
	//		//只是遍历没必要踢出队列
	//		//itc = contours.erase(itc);

	//		//在缺陷图上将不符合条件的部分填充成黑色
	//		cv::drawContours(*p_mat, contours, nIndex, cv::Scalar(0), CV_FILLED, 8);
	//	}
	//	else
	//	{
	//		

	//		////标记当前轮廓区域
	//		//Mat tmatMake = Mat::zeros(p_mat->size(), CV_8UC1);
	//		//cv::drawContours(tmatMake, contours, nIndex, cv::Scalar(255), CV_FILLED, 8);
	//		////获取轮廓是否大于最小亮度要求
	//		//bool t_bMinBright = IsGreaterMinimumBrightness(p_mat, tmatMake, itc,10,20,20,20,10000);
	//		////如果不符合要求从当前队列中剔除
	//		//if (!t_bMinBright)
	//		//{
	//		//	//只是遍历没必要踢出队列
	//		//	//itc = contours.erase(itc);
	//		//}
	//		//else
	//		//{
	//		//	//存储缺陷结果
	//		//	//SaveDefect(p_nOffsetX, p_nOffsetY, itc);

	//		//}
	//		//tmatMake.release();
	//	}

	//	itc++;
	//	nIndex++;
	//}
	return 0;
}

//16位灰度图均值，以5*5矩阵进行图像均值处理
//使用原数据处理
int ImageMatrixAvg16(Mat &src)
{
	IplImage *t_iplSrc = cvCreateImage(src.size(), IPL_DEPTH_16U, 1);
	cvCopy(&IplImage(src), t_iplSrc);
	for (int y = 0;y< t_iplSrc->height ;y++)
	{
		for (int x =0;x<t_iplSrc->width;x++)
		{
			//计算均值
			int tVal = 0;
			int tTimes = 0;
			for (int y1= y-2;y1<=y+2;y1++)
			{
				for (int x1 = x-2;x1<=x+2;x1++)
				{
					int x2, y2;
					x2 = x1 < 0 ? 0 : x1;
					x2 = x2 >= t_iplSrc->width ? t_iplSrc->width - 1 : x2;
					y2 = y1 < 0 ? 0 : y1;
					y2 = y2 >= t_iplSrc->height ? t_iplSrc->height - 1 : y2;
					tVal += (*(ushort*)(t_iplSrc->imageData + x2 * 2 + y2 * t_iplSrc->widthStep));
					tTimes++;
				}
			}
			tVal /= 25;
			//src.at<ushort>(y, x) = tVal;
			(*(ushort*)(src.data + x * 2 + y * t_iplSrc->widthStep)) = tVal;
			//if ((x == 242) && y==197)
			//{
			//	tTimes = tTimes;
			//}
		}
	}

	cvReleaseImage(&t_iplSrc);

	return 0;
}


//16位灰度图均值，以3*3矩阵进行图像均值处理
//使用新数据迭代处理
//p_nStep:0 3*3,2 5*5 表示以当前点向x、y方向延伸的步长
int ImageMatrixAvg163X3(Mat& src, int p_nStep /*= 3*/)
{
	IplImage* t_iplSrc = &(IplImage)src;
	if (p_nStep<1)
	{
		return 1;
	}
	for (int y = 0; y < t_iplSrc->height; y++)
	{
		for (int x = 0; x < t_iplSrc->width; x++)
		{
			//计算均值
			int tVal = 0;
			int tTimes = 0;
			for (int y1 = y - p_nStep; y1 <= y + p_nStep; y1++)
			{
				for (int x1 = x - p_nStep; x1 <= x + p_nStep; x1++)
				{
					int x2, y2;
					x2 = x1 < 0 ? 0 : x1;
					x2 = x2 >= t_iplSrc->width ? t_iplSrc->width - 1 : x2;
					y2 = y1 < 0 ? 0 : y1;
					y2 = y2 >= t_iplSrc->height ? t_iplSrc->height - 1 : y2;
					tVal += (*(ushort*)(t_iplSrc->imageData + x2 * 2 + y2 * t_iplSrc->widthStep));
					tTimes++;
				}
			}
			tVal /= tTimes;
			//src.at<ushort>(y, x) = tVal;
			(*(ushort*)(t_iplSrc->imageData + x * 2 + y * t_iplSrc->widthStep)) = tVal;
			//if ((x == 242) && y==197)
			//{
			//	tTimes = tTimes;
			//}
		}
	}

	return 0;
}



//16位灰度图均值，以矩阵形式进行图像均值处理
//p_nStep:0 3*3,2 5*5 表示以当前点向x、y方向延伸的步长
int ImageMatrixAvg16Step(Mat& src, int p_nStep /*= 3*/)
{
	Mat tSwap = src.clone();
	IplImage* t_iplSrc = &(IplImage)src;
	if (p_nStep < 1)
	{
		return 1;
	}
	for (int y = 0; y < t_iplSrc->height; y++)
	{
		for (int x = 0; x < t_iplSrc->width; x++)
		{
			//计算均值
			int tVal = 0;
			int tTimes = 0;
			for (int y1 = y - p_nStep; y1 <= y + p_nStep; y1++)
			{
				for (int x1 = x - p_nStep; x1 <= x + p_nStep; x1++)
				{
					int x2, y2;
					x2 = x1 < 0 ? 0 : x1;
					x2 = x2 >= t_iplSrc->width ? t_iplSrc->width - 1 : x2;
					y2 = y1 < 0 ? 0 : y1;
					y2 = y2 >= t_iplSrc->height ? t_iplSrc->height - 1 : y2;
					tVal += (*(ushort*)(tSwap.data + x2 * 2 + y2 * t_iplSrc->widthStep));
					tTimes++;
				}
			}
			tVal /= tTimes;
			//src.at<ushort>(y, x) = tVal;
			(*(ushort*)(t_iplSrc->imageData + x * 2 + y * t_iplSrc->widthStep)) = tVal;
			//if ((x == 242) && y==197)
			//{
			//	tTimes = tTimes;
			//}
		}
	}

	return 0;
}