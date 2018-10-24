//名称：CDoubleDIRListsContainer
//功能：单个双向链表容器，链表中的每个元素为CDoubleDIRList类型，
//		提供链表创建、册除、插入、弹出、清空、获取首尾元素等操作。

//修改历史
//-----------------------------
//2016.08.20 1.0版 
//说明：首次发布
//-----------------------------
//2016.09.20 1.1
//在对链表的操作方法中增加临界区保护

#pragma once
#include "DoubleDIRList.h"

template<typename T>
class CDoubleDIRListContainer
{
public:
	typedef CDoubleDIRList<T> * iterator;
public:
	CDoubleDIRListContainer();
	~CDoubleDIRListContainer();

	UINT GetCount();
	//返回链表中指定位置元素
	CDoubleDIRList<T> * at(UINT x);	//x 从零开始计数,当输入位置值大于链表长度时返回NULL
	bool GetIsEmpty();
	//void Insert();
	void PopBack();
	void PopFront();
	void PushBack(T tItem);
	void PushFront(T tItem);
	void clear();

	CDoubleDIRList<T> * GetBegin();
	CDoubleDIRList<T> * GetEnd();

private:
	CDoubleDIRList<T> * m_Begin;
	CDoubleDIRList<T> * m_End;
	UINT m_unCount;

	CCriticalSection m_Critical;
	void Init();
};

template<typename T>
CDoubleDIRList<T> * CDoubleDIRListContainer<T>::at(UINT x)
{
	CDoubleDIRList <T> * pDoubleDIRListItem;
	m_Critical.Lock();
	if (x < m_unCount)
	{
		CDoubleDIRList<T> *pDoubleDIRList;

		pDoubleDIRList = m_End;
		for (int i = 0; i <= x; i++)
		{
			pDoubleDIRList = pDoubleDIRList->GetNext();
		}
		pDoubleDIRListItem = pDoubleDIRList;
	} 
	else
	{
		pDoubleDIRListItem = NULL;
	}
	m_Critical.Unlock();
	return pDoubleDIRListItem;
}

template<typename T>
void CDoubleDIRListContainer<T>::PushFront(T  tItem)
{
	m_Critical.Lock();
	CDoubleDIRList<T> *pDoubleDIRList;
	pDoubleDIRList = new CDoubleDIRList<T>;

	pDoubleDIRList->SetData(tItem);

	if (0 == m_unCount)
	{
		m_Begin = pDoubleDIRList;
		m_End = pDoubleDIRList;
		pDoubleDIRList->SetNext(pDoubleDIRList);
		pDoubleDIRList->SetPrevious(pDoubleDIRList);
	}
	else
	{
		pDoubleDIRList->SetPrevious(m_End);
		m_End->SetNext(pDoubleDIRList);
		pDoubleDIRList->SetNext(m_Begin);
		m_Begin->SetPrevious(pDoubleDIRList);
		m_Begin = pDoubleDIRList;
	}

	m_unCount++;
	m_Critical.Unlock();
}

template<typename T>
void CDoubleDIRListContainer<T>::PushBack(T tItem)
{
	m_Critical.Lock();
	CDoubleDIRList<T> *pDoubleDIRList;
	pDoubleDIRList = new CDoubleDIRList<T>;

	pDoubleDIRList->SetData(tItem);

	if (0 == m_unCount)
	{
		m_Begin = pDoubleDIRList;
		m_End = pDoubleDIRList;
		pDoubleDIRList->SetNext(pDoubleDIRList);
		pDoubleDIRList->SetPrevious(pDoubleDIRList);
	} 
	else
	{
		pDoubleDIRList->SetPrevious(m_End);
		m_End->SetNext(pDoubleDIRList);
		m_End = pDoubleDIRList;

		pDoubleDIRList->SetNext(m_Begin);
		m_Begin->SetPrevious(pDoubleDIRList);
	}

	m_unCount++;
	m_Critical.Unlock();
}

template<typename T>
void CDoubleDIRListContainer<T>::clear()
{
	m_Critical.Lock();
	while (m_unCount > 0)
	{
		PopFront();
	}
	m_Critical.Unlock();
}

template<typename T>
bool CDoubleDIRListContainer<T>::GetIsEmpty()
{
	m_Critical.Lock();
	bool bFloag = (this->m_unCount == 0);
	m_Critical.Unlock();
	return bFloag;
}

template<typename T>
UINT CDoubleDIRListContainer<T>::GetCount()
{
	m_Critical.Lock();
	UINT nSize = this->m_unCount;
	m_Critical.Unlock();
	return nSize;
}

template<typename T>
void CDoubleDIRListContainer<T>::PopBack()
{
	m_Critical.Lock();
	if (NULL != m_End)
	{
		if (m_End == m_Begin)
		{
			delete m_End;
			Init();
		}
		else
		{
			CDoubleDIRList<T> *pDoubleDIRList;
			pDoubleDIRList = m_End->GetPrevious();
			delete m_End;

			m_End = pDoubleDIRList;
			m_Begin->SetPrevious(m_End);
			m_End->SetNext(m_Begin);
			m_unCount--;
		}
	}
	else
	{
	}
	m_Critical.Unlock();
}

template<typename T>
void CDoubleDIRListContainer<T>::Init()
{
	m_Begin = NULL;
	m_End = NULL;
	m_unCount = 0;
}

template<typename T>
void CDoubleDIRListContainer<T>::PopFront()
{
	m_Critical.Lock();
	if (NULL != m_Begin )
	{
		if (m_End == m_Begin)
		{
			delete m_Begin;
			Init();
		} 
		else
		{
			CDoubleDIRList<T> *pDoubleDIRList;
			pDoubleDIRList = m_Begin->GetNext();
			delete m_Begin;

			m_Begin = pDoubleDIRList;
			m_Begin->SetPrevious(m_End);
			m_End->SetNext(m_Begin);
			m_unCount--;
		}
	} 
	else
	{
	}
	m_Critical.Unlock();
}

template<typename T>
CDoubleDIRList<T> * CDoubleDIRListContainer<T>::GetEnd()
{
	CDoubleDIRList <T> * pDoubleDIRListItem;
	m_Critical.Lock();
	pDoubleDIRListItem = m_End;
	m_Critical.Unlock();
	return pDoubleDIRListItem;
}

template<typename T>
CDoubleDIRList<T> * CDoubleDIRListContainer<T>::GetBegin()
{
	CDoubleDIRList <T> * pDoubleDIRListItem;
	m_Critical.Lock();
	pDoubleDIRListItem = m_Begin;
	m_Critical.Unlock();
	return pDoubleDIRListItem;
}

template<typename T>
CDoubleDIRListContainer<T>::~CDoubleDIRListContainer()
{
	clear();
}

template<typename T>
CDoubleDIRListContainer<T>::CDoubleDIRListContainer()
	:m_Begin(NULL),
	m_End(NULL),
	m_unCount(0)
{

}

