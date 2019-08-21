#include "stdafx.h"
#include "IplImageEx.h"

IplImageEx::IplImageEx(CvSize size, int depth, int channels)
{
	m_pIplImage = cvCreateImage(size, depth, channels);
	switch (depth)
	{
	case 8:
	{
		pFuncGetVal = &IplImageEx::GetVal8;
	}
	break;
	case 16:
	{
		pFuncGetVal = &IplImageEx::GetVal16;

	}
	break;
	default:
	{
		pFuncGetVal = NULL;
	}
	}
}

IplImageEx::~IplImageEx()
{
	cvReleaseImage(&m_pIplImage);
}

IplImage* IplImageEx::GetImage()
{
	return m_pIplImage;
}

int IplImageEx::GetVal(int nCol, int nRow)
{
	int nVal = 0;

	if (NULL != m_pIplImage)
	{
		nVal = (this->*pFuncGetVal)(nCol, nRow);
	}

	return nVal;
}

int IplImageEx::GetVal8(int nCol, int nRow)
{
	int nVal = 0;

	if (NULL != m_pIplImage)
	{
		nVal = (*(uchar*)(m_pIplImage->imageData + nRow * m_pIplImage->widthStep + nCol * m_pIplImage->nChannels));
	}

	return nVal;
}

int IplImageEx::GetVal16(int nCol, int nRow)
{
	int nVal = 0;

	if (NULL != m_pIplImage)
	{
		nVal = (*(ushort*)(m_pIplImage->imageData + nRow * m_pIplImage->widthStep + nCol * m_pIplImage->nChannels * 2));
	}

	return nVal;
}
