#include "stdafx.h"
#include "RecordingVideo.h"
#include "FileOperation/CFileOpertion.h"

RecordingVideo::RecordingVideo()
{
	m_Writer = NULL;
	InitializeCriticalSection(&m_Section);
}


RecordingVideo::~RecordingVideo()
{
	StopRec();
	DeleteCriticalSection(&m_Section);
}

int RecordingVideo::StartRec()
{
	char t_chrVideoFilePath[256] = { 0 };
	CString t_strVideoFilePath = _T("");
	t_strVideoFilePath = CFileOpertion::GetModuleFileDir() + _T("\\Video\\") + CFileOpertion::BuildTimeFileName()+_T(".avi");

	memcpy(t_chrVideoFilePath, (CStringA)t_strVideoFilePath, ((CStringA)t_strVideoFilePath).GetLength());

	switch (m_VIDEOFORMAT)
	{
	case RecordingVideo::enum_VIDEOFORMAT_MPEG1:
	{
		m_Writer = cvCreateVideoWriter(t_chrVideoFilePath, CV_FOURCC_MPEG1,
			m_nfps, cvSize(m_nFrameW, m_nFrameH), m_nIsColor);
	}
		break;
	case RecordingVideo::enum_VIDEOFORMAT_MOTIONJPEG:
	{
		m_Writer = cvCreateVideoWriter(t_chrVideoFilePath, CV_FOURCC_MPEG1,
			m_nfps, cvSize(m_nFrameW, m_nFrameH), m_nIsColor);
	}
		break;
	case RecordingVideo::enum_VIDEOFORMAT_MPEG42:
	{
		m_Writer = cvCreateVideoWriter(t_chrVideoFilePath, CV_FOURCC_MPEG1,
			m_nfps, cvSize(m_nFrameW, m_nFrameH), m_nIsColor);
	}
		break;
	case RecordingVideo::enum_VIDEOFORMAT_MPEG43:
	{
		m_Writer = cvCreateVideoWriter(t_chrVideoFilePath, CV_FOURCC_MPEG1,
			m_nfps, cvSize(m_nFrameW, m_nFrameH), m_nIsColor);
	}
		break;
	case RecordingVideo::enum_VIDEOFORMAT_MPEG4:
	{
		m_Writer = cvCreateVideoWriter(t_chrVideoFilePath, CV_FOURCC_MPEG1,
			m_nfps, cvSize(m_nFrameW, m_nFrameH), m_nIsColor);
	}
		break;
	case RecordingVideo::enum_VIDEOFORMAT_H263:
	{
		m_Writer = cvCreateVideoWriter(t_chrVideoFilePath, CV_FOURCC_MPEG1,
			m_nfps, cvSize(m_nFrameW, m_nFrameH), m_nIsColor);
	}
		break;
	case RecordingVideo::enum_VIDEOFORMAT_H263I:
	{
		m_Writer = cvCreateVideoWriter(t_chrVideoFilePath, CV_FOURCC_MPEG1,
			m_nfps, cvSize(m_nFrameW, m_nFrameH), m_nIsColor);
	}
		break;
	case RecordingVideo::enum_VIDEOFORMAT_FLV1:
	{
		m_Writer = cvCreateVideoWriter(t_chrVideoFilePath, CV_FOURCC_MPEG1,
			m_nfps, cvSize(m_nFrameW, m_nFrameH), m_nIsColor);
	}
		break;
	default:
	{
		m_Writer = cvCreateVideoWriter(t_chrVideoFilePath, CV_FOURCC_MPEG1,
			m_nfps, cvSize(m_nFrameW, m_nFrameH), m_nIsColor);
	}
		break;
	}


	if (NULL != m_Writer)
	{
		
	}
	else
	{
		return 1;
	}
	

	return 0;
}

int RecordingVideo::StopRec()
{
	EnterCriticalSection(&m_Section);
	if (NULL != m_Writer)
	{
		cvReleaseVideoWriter(&m_Writer);
		m_Writer = NULL;
	}
	else
	{
		LeaveCriticalSection(&m_Section);
		return 1;
	}
	LeaveCriticalSection(&m_Section);
	return 0;
}

int RecordingVideo::UpdateImage(Mat p_matSrc)
{
	EnterCriticalSection(&m_Section);
	if (NULL != m_Writer)
	{
		cvWriteFrame(m_Writer, &IplImage(p_matSrc));      // add the frame to the file
	}
	else
	{
		LeaveCriticalSection(&m_Section);
		return 1;
	}
	LeaveCriticalSection(&m_Section);
	//IplImage* img = 0;
	//int nFrames = 50;
	//for (i = 0; i < nFrames; i++){
	//	//cvGrabFrame(capture);          // capture a frame
	//	//img = cvRetrieveFrame(capture);  // retrieve the captured frame
	//	
	//}

	return 0;
}

int RecordingVideo::SetVideoFormat(int p_nFrameW, int p_nFrameH, int p_nFps, int p_nIsColor, enum_VIDEOFORMAT p_VIDEOFORMAT /*= enum_VIDEOFORMAT_MPEG43*/)
{
	m_nFrameW = p_nFrameW;
	m_nFrameH = p_nFrameH;
	m_nfps = p_nFps;
	m_nIsColor = p_nIsColor;
	m_VIDEOFORMAT = p_VIDEOFORMAT;

	return 0;
}
