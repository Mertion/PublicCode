#pragma once

//名称：CDoubleDIRList
//功能：双向链表元素数据结构及基本操作。

template<typename T>
class CDoubleDIRList
{
public:

	CDoubleDIRList();
	~CDoubleDIRList();

	CDoubleDIRList<T> * GetNext();
	void SetNext(CDoubleDIRList<T> *DoubleDIRLists);
	CDoubleDIRList<T> * GetPrevious();
	void SetPrevious(CDoubleDIRList<T> *DoubleDIRLists);
	void SetData(T _Data);
	T GetData();
private:
	CDoubleDIRList<T> * m_pPrevious;
	CDoubleDIRList<T> * m_pNext;
	//T * m_pData;

	T  m_pData;
};

template<typename T>
T CDoubleDIRList<T>::GetData()
{
	//return (*m_pData);
	return m_pData;
}

template<typename T>
CDoubleDIRList<T>::CDoubleDIRList()
	:m_pPrevious(NULL),
	m_pNext(NULL)//,
	//m_pData(NULL)
{
	//m_pData = new T;
}

template<typename T>
CDoubleDIRList<T>::~CDoubleDIRList()
{	
	m_pPrevious = NULL;
	m_pNext = NULL;
	//m_pData = NULL;
}


template<typename T>
void CDoubleDIRList<T>::SetData(T _Data)
{
	m_pData = _Data;
	//* m_pData = _Data;
}

template<typename T>
void CDoubleDIRList<T>::SetPrevious(CDoubleDIRList<T>  *pDoubleDIRLists)
{
	m_pPrevious = pDoubleDIRLists;
}

template<typename T>
CDoubleDIRList<T> * CDoubleDIRList<T>::GetPrevious()
{
	return m_pPrevious;
}

template<typename T>
void CDoubleDIRList<T>::SetNext(CDoubleDIRList<T>  *pDoubleDIRLists)
{
	m_pNext = pDoubleDIRLists;
}

template<typename T>
CDoubleDIRList<T> * CDoubleDIRList<T>::GetNext()
{
	return m_pNext;
}




