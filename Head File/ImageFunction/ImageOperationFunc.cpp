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