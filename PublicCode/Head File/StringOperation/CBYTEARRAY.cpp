#include "stdafx.h"
#include "CBYTEARRAY.h"


CBYTEARRAY::CBYTEARRAY()
{
	m_BYTEArray = NULL;
	m_ulArraySize = 0;
}


CBYTEARRAY::~CBYTEARRAY()
{
	Empty();
}

//************************************
// Method:    PushBack
// FullName:  CBYTEARRAY::PushBack
// Access:    public 
// Returns:   void
// Qualifier: 在数组末端追加数据
// Parameter: IN BYTE * p_pBYTEArray         追加数据
// Parameter: IN unsigned long p_ulArraySize 追加数据长度
//************************************
void CBYTEARRAY::PushBack(IN BYTE * p_pBYTEArray, IN unsigned long p_ulArraySize)
{
	unsigned long t_ulArrayLen = m_ulArraySize + p_ulArraySize;
	BYTE * t_pBYTEArray = new BYTE[t_ulArrayLen];

	if (0 != m_ulArraySize)
	{
		memcpy(t_pBYTEArray, m_BYTEArray, m_ulArraySize);
		delete[] m_BYTEArray;
	}
	memcpy(t_pBYTEArray + m_ulArraySize, p_pBYTEArray, p_ulArraySize);

	m_ulArraySize = t_ulArrayLen;
	m_BYTEArray = t_pBYTEArray;
}

//************************************
// Method:    GetBYTE
// FullName:  CBYTEARRAY::GetBYTE
// Access:    public 
// Returns:   unsigned long							输出数据长度
// Qualifier: 从指定位置获取数组中的数据
// Parameter: IN unsigned long p_ulStartPosition	获取起点
// Parameter: IN unsigned long p_ulLen				获取长度
// Parameter: OUT BYTE * p_pBYTEArray				接收数据指针
//************************************
unsigned long CBYTEARRAY::GetBYTE(IN unsigned long p_ulStartPosition, IN unsigned long p_ulLen, OUT BYTE * p_pBYTEArray)
{
	unsigned long t_ulLen = p_ulStartPosition + p_ulLen;

	//判断起点是否超过数组长度
	if (p_ulStartPosition > m_ulArraySize)
	{
		return 0;
	}

	//判断要获取的数据是否超过数组长度
	if (t_ulLen > m_ulArraySize)
	{
		t_ulLen = m_ulArraySize - p_ulStartPosition;
	} 
	else
	{
		t_ulLen = t_ulLen - p_ulStartPosition;
	}
	memcpy(p_pBYTEArray, m_BYTEArray + p_ulStartPosition, t_ulLen);
	return t_ulLen;
}

//************************************
// Method:    GetBYTE
// FullName:  CBYTEARRAY::GetBYTE
// Access:    public 
// Returns:   unsigned long				输出数据长度
// Qualifier: 获取数组中所有数据
// Parameter: IN unsigned long p_ulSize	接收数据数组大小 
// Parameter: OUT BYTE * p_pBYTEArray	接收数据数组指针
//************************************
unsigned long CBYTEARRAY::GetBYTE(IN unsigned long p_ulSize, OUT BYTE * p_pBYTEArray)
{
	unsigned long t_ulLen = p_ulSize;
	if (t_ulLen > m_ulArraySize)
	{
		t_ulLen = m_ulArraySize;
	} 
	else
	{
	}
	memcpy(p_pBYTEArray, m_BYTEArray, t_ulLen);
	return t_ulLen;
}

//************************************
// Method:    GetSize
// FullName:  CBYTEARRAY::GetSize
// Access:    public 
// Returns:   unsigned long
// Qualifier: 获取数组大小
//************************************
unsigned long CBYTEARRAY::GetSize()
{
	return m_ulArraySize;
}

//************************************
// Method:    Empty
// FullName:  CBYTEARRAY::Empty
// Access:    public 
// Returns:   void
// Qualifier: 清空数组
//************************************
void CBYTEARRAY::Empty()
{
	m_ulArraySize = 0;
	delete[] m_BYTEArray;
	m_BYTEArray = NULL;
}
