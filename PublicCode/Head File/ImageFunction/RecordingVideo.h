#pragma once
#pragma warning(disable:4996)

#include "stdafx.h"

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

//视频格式代码
//#define CV_FOURCC_DEFAULT CV_FOURCC('I', 'Y', 'U', 'V') /* Use default codec for specified filename (Linux only) */

#define CV_FOURCC_MPEG1 CV_FOURCC('P', 'I', 'M', '1')		// MPEG - 1 codec
#define CV_FOURCC_MOTIONJPEG CV_FOURCC('M', 'J', 'P', 'G')	// motion - jpeg codec(does not work well)
#define CV_FOURCC_MPEG42 CV_FOURCC('M', 'P', '4', '2')		// MPEG - 4.2 codec
#define CV_FOURCC_MPEG43 CV_FOURCC('D', 'I', 'V', '3')		// MPEG - 4.3 codec
#define CV_FOURCC_MPEG4 CV_FOURCC('D', 'I', 'V', 'X')		// MPEG - 4 codec
#define CV_FOURCC_H263 CV_FOURCC('U', '2', '6', '3')		// H263 codec
#define CV_FOURCC_H263I CV_FOURCC('I', '2', '6', '3')		// H263I codec
#define CV_FOURCC_FLV1 CV_FOURCC('F', 'L', 'V', '1')		// FLV1 codec


class RecordingVideo
{
public:
	enum enum_VIDEOFORMAT
	{
		enum_VIDEOFORMAT_MPEG1 = 0,
		enum_VIDEOFORMAT_MOTIONJPEG,
		enum_VIDEOFORMAT_MPEG42,
		enum_VIDEOFORMAT_MPEG43,
		enum_VIDEOFORMAT_MPEG4,
		enum_VIDEOFORMAT_H263,
		enum_VIDEOFORMAT_H263I,
		enum_VIDEOFORMAT_FLV1,
	};
	RecordingVideo();
	~RecordingVideo();

	int StartRec();
	int StopRec();
	int UpdateImage(Mat p_matSrc);
	int SetVideoFormat(int p_nFrameW, int p_nFrameH, int p_nFps, int p_nIsColor, enum_VIDEOFORMAT p_VIDEOFORMAT = enum_VIDEOFORMAT_MPEG43);
private:
	CvVideoWriter* m_Writer = 0;
	int m_nIsColor = 1;
	int m_nfps = 25;  // or 30
	int m_nFrameW = 480; // 744 for firewire cameras
	int m_nFrameH = 640; // 480 for firewire cameras
	enum_VIDEOFORMAT m_VIDEOFORMAT = enum_VIDEOFORMAT_MPEG43;

	CRITICAL_SECTION m_Section;
};