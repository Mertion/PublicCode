#include "stdafx.h"
#include "RecognitionFunction.h"


RecognitionFunction::RecognitionFunction()
{
}


RecognitionFunction::~RecognitionFunction()
{
}

//************************************
// Method:    GetMultiRingsGray
// FullName:  RecognitionFunction::GetMultiRingsGray
// Access:    public 
// Returns:   int 预留
// Qualifier:
// Parameter: Mat p_matSrc	数据源图像
// Parameter: GrayRings * * p_arrGrayRings	圆环数组
// Parameter: int p_RingsCount	圆环个数
//************************************
int RecognitionFunction::GetMultiRingsGray(Mat p_matSrc, GrayRings** p_arrGrayRings, int p_RingsCount, Mat* p_pmatDebug)
{
	//像素点到圆心X方向距离
	int t_nDistanceX = 0;
	//像素点到圆心Y方向距离
	int t_nDistanceY = 0;


	GrayRings* t_GrayRings = NULL;

	//清空数据
	for (int i = 0; i < p_RingsCount; i++)
	{
		t_GrayRings = p_arrGrayRings[i];
		t_GrayRings->AvgGray = 0;
		t_GrayRings->PixelCount = 0;
	}

	//计算各圆环内所有介素灰度总和
	for (int i = 0; i < p_matSrc.cols; i++)
	{
		//水平方向以中线为准向两侧取一个光带进行运算，因为拍摄到的图像是椭圆的。
		for (int j = 0; j < p_matSrc.rows; j++)
		{
			for (int k = 0; k < p_RingsCount; k++)
			{
				t_GrayRings = p_arrGrayRings[k];

				t_nDistanceX = abs(i - t_GrayRings->Center.x);
				t_nDistanceY = abs(j - t_GrayRings->Center.y);

				int t_nX = (t_nDistanceX * t_nDistanceX + t_nDistanceY * t_nDistanceY);
				if (((t_GrayRings->OuterCircleReadius * t_GrayRings->OuterCircleReadius) > t_nX)
					&& (t_nX > (t_GrayRings->InsideCirclReadius * t_GrayRings->InsideCirclReadius))
					)
				{
					t_GrayRings->AvgGray += p_matSrc.at<uchar>(j, i);
					t_GrayRings->PixelCount++;
					p_pmatDebug->at<uchar>(j, i) = p_matSrc.at<uchar>(j, i);

					int x = i - (t_GrayRings->Center.x - t_GrayRings->OuterCircleReadius);
					int y = j - (t_GrayRings->Center.y - t_GrayRings->OuterCircleReadius);
					t_GrayRings->RingsGrayImage.at<uchar>(y,x) = p_matSrc.at<uchar>(j, i);
				}
			}
			
		}
	}

	//计算灰度平均值
	for (int i = 0; i < p_RingsCount; i++)
	{
		t_GrayRings = p_arrGrayRings[i];
		if (0 != t_GrayRings->PixelCount)
		{
			t_GrayRings->AvgGray /= t_GrayRings->PixelCount;
		}
	}

	return 0;
}

int RecognitionFunction::GetAvgLight(IN Mat p_mRecognitionImage, OUT Mat* p_pCircleImage)
{
	//平均亮度
	int t_nAvgLight = 0;
	//所有像素点总亮度
	int t_nSumLight = 0;
	//参与计算像素点个数
	int t_nPixelCount = 0;
	//内切圆半径
	int t_nRadius = (p_mRecognitionImage.cols / 2);
	//内切圆半径平方
	int t_nRadius2 = t_nRadius * t_nRadius;
	//像素点到圆心X方向距离
	int t_nDistanceX = 0;
	//像素点到圆心Y方向距离
	int t_nDistanceY = 0;

	p_pCircleImage->release();
	*p_pCircleImage = Mat::zeros(p_mRecognitionImage.size(), CV_8UC1);

	for (int i = 0; i < p_mRecognitionImage.cols; i++)
	{
		t_nDistanceX = abs(i - t_nRadius);
		for (int j = 0; j < p_mRecognitionImage.rows; j++)
		{
			t_nDistanceY = abs(j - t_nRadius);
			if ((t_nDistanceX * t_nDistanceX + t_nDistanceY * t_nDistanceY) > t_nRadius2)
			{
				t_nSumLight += p_mRecognitionImage.at<uchar>(i, j);
				t_nPixelCount++;
			}
			else
			{
				p_pCircleImage->at<uchar>(i, j) = p_mRecognitionImage.at<uchar>(i, j);
			}
		}
	}
	t_nAvgLight = t_nSumLight / t_nPixelCount;

	return t_nAvgLight;
}

int RecognitionFunction::CalculateDistance2Point(Point p_pointA, Point p_pointB, Point& p_pointOutput)
{
	int x = 0;
	int y = 0;
	int Distance = 0;
	p_pointOutput = p_pointB - p_pointA;

	x = p_pointOutput.x;
	y = p_pointOutput.y;

	Distance = sqrt(x * x + y * y);
	return Distance;
}

int RecognitionFunction::BuildEnergyCurve(Mat p_matDataSrc, Mat& p_matDst, Mat& p_matDstDisplay, Scalar p_colorDisplay, deque<Point>& lines)
{
	for (int i = 0; i < lines.size(); i++)
	{
		Point t_Point = lines.at(i);
		//draw_img.at<Vec3b>(lines[i][j]) = Vec3b(p_colorDisplay[0], p_colorDisplay[1], p_colorDisplay[2]);
		int t_nVal = p_matDataSrc.at<ushort>(t_Point.y, t_Point.x);
		//t_nVal /= 100;
		//t_nVal *= 30;
		//t_nVal /= 255;
		p_matDst.at<uchar>(t_nVal, t_Point.x) = 255;
		p_matDstDisplay.at<Vec3b>(t_nVal, t_Point.x) = Vec3b(p_colorDisplay[0], p_colorDisplay[1], p_colorDisplay[2]);
	}
	return 0;
}
