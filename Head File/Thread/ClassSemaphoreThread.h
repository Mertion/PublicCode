#pragma once
#include "stdafx.h"
#include<afxmt.h>

//�¼������߳���
//ÿ����һ��TriggerThread����ִ��һ���̺߳���
class ClassSemaphoreThread
{
public:
	enum ENUM_THREADINFO
	{
		ENUM_THREADINFO_SUCCESS = 0,
		ENUM_THREADINFO_CREATTHREADFAILD,	//�����߳�ʧ��
		ENUM_THREADINFO_FUNCISEMPYT,		//����ָ��Ϊ��
		ENUM_THREADINFO_THREADISRUN,		//�߳��Ѿ�������
	};
	
	DWORD GetInterval() const { return m_nInterval; }
	void SetInterval(DWORD val) { m_nInterval = val; }
public:
	ClassSemaphoreThread(LONG lInitialCount = 1, LONG lMaxCount = 1,
		LPCTSTR pstrName = NULL, LPSECURITY_ATTRIBUTES lpsaAttributes = NULL);
	~ClassSemaphoreThread();

	//�̻߳ص�����
	unsigned  static __stdcall exThreadTask(LPVOID lpParam);
	//�߳�ִ�к���
	unsigned ThreadTask();
	//static unsigned __stdcall ThreadStaticEntryPoint(void * pThis);

	//�����߳�
	int Start();
	//ֹͣ�߳�
	void Stop();
	//���ûص�����
	void SetFunction(AFX_THREADPROC p_pFunc);
	//�����̲߳���
	void SetArg(LPVOID p_pArg);
	//�����̳߳�ʼ״̬:Ĭ��Ϊ��
	void SetInitFlag(unsigned p_uiInitFlag);
	//����һ���߳�ִ��
	void TriggerThread();
	//�����ڴ��ջ��С�����߳�����ǰ������Ч
	void SetMemorySize(int p_nMemorySize);
protected:
	//�ڴ��ջ��С
	int m_nMemorySize = 0;
	//�߳̾��
	HANDLE m_hThredHandle = NULL;
	//�̳߳�ʼ״̬: 0-��������,CREATE_SUSPEND-���������
	unsigned m_uiInitFlag = 0;
	//�߳�ID
	unsigned  m_uiThreadID = 0;
	//�̺߳���ָ��
	AFX_THREADPROC m_pFunc = NULL;
	//�̲߳����б�
	LPVOID m_pArg = NULL;
	//�߳�״̬��
	DWORD   dwExitCode = 0;

	//�߳�ɨ����
	DWORD m_nInterval = 0;


	//�߳�ͬ���ź�
	CSemaphore* m_CSemaphore = NULL;

	//�˳��߳�
	bool m_bExit = false;
};
