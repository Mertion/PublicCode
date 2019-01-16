//名称：CDequeForListContainer
//功能：使用DEQUE实现的单个双向链表容器，链表中的每个元素为CDoubleDIRList类型，
//		提供链表创建、册除、插入、弹出、清空、获取首尾元素等操作。

//修改历史
//-----------------------------
//2016.08.20 1.0版 
//说明：首次发布
//-----------------------------
//2016.09.20 1.1
//在对链表的操作方法中增加临界区保护

#pragma once
#include <deque>
#include "DoubleDIRList.h"
#include <afxmt.h>

using namespace std;

template <typename T>
class CDequeForListContainer
{
private:
	typedef deque<CDoubleDIRList <T>> DEQUE_DIRLIST;

public:
	typedef CDoubleDIRList <T> iterator;
public:

	CDequeForListContainer();

	~CDequeForListContainer();

	void push_front(T _Val);
	void pop_front();
	void push_back(T _Val);
	void pop_back();
	iterator * at(int nIndex);
	iterator back();
	iterator front();
	iterator * begin();
	iterator * end();

	bool GetIsEmpty();

	void clear();
	UINT size();

private:
	DEQUE_DIRLIST m_DirList;
	CCriticalSection m_Critical;
	
};

template <typename T>
bool CDequeForListContainer<T>::GetIsEmpty()
{
	m_Critical.Lock();
	bool bFlag = (this->size() == 0);
	m_Critical.Unlock();
	return bFlag;
}

template <typename T>
void CDequeForListContainer<T>::clear()
{
	m_Critical.Lock();
	m_DirList.clear();
	m_Critical.Unlock();
}

template <typename T>
CDoubleDIRList <T> CDequeForListContainer<T>::front()
{
	CDoubleDIRList <T> DoubleDIRListItem;
	m_Critical.Lock();
	DoubleDIRListItem = m_DirList.front();
	m_Critical.Unlock();
	return DoubleDIRListItem;
}

template <typename T>
CDoubleDIRList <T> CDequeForListContainer<T>::back()
{
	CDoubleDIRList <T> DoubleDIRListItem;
	m_Critical.Lock();
	DoubleDIRListItem = m_DirList.back();
	m_Critical.Unlock();
	return DoubleDIRListItem;
}

template <typename T>
UINT CDequeForListContainer<T>::size()
{
	UINT nSize = 0;
	m_Critical.Lock();
	nSize = m_DirList.size();
	m_Critical.Unlock();
	return nSize;
}

template <typename T>
CDoubleDIRList <T> * CDequeForListContainer<T>::end()
{
	CDoubleDIRList <T> * pDoubleDIRListItem;
	m_Critical.Lock();
	pDoubleDIRListItem = &m_DirList.back();
	m_Critical.Unlock();
	return pDoubleDIRListItem;
}

template <typename T>
CDoubleDIRList <T> * CDequeForListContainer<T>::begin()
{
	CDoubleDIRList <T> * pDoubleDIRListItem;
	m_Critical.Lock();
	pDoubleDIRListItem = &m_DirList.front();
	m_Critical.Unlock();
	return pDoubleDIRListItem;
}

template <typename T>
CDoubleDIRList <T> * CDequeForListContainer<T>::at(int nIndex)
{
	CDoubleDIRList <T> * pDoubleDIRListItem;
	m_Critical.Lock();
	if (nIndex < m_DirList.size())
	{
		pDoubleDIRListItem = &m_DirList.at(nIndex);
	} 
	else
	{
		pDoubleDIRListItem = NULL;
	}
	m_Critical.Unlock();
	return pDoubleDIRListItem;
}

template <typename T>
void CDequeForListContainer<T>::pop_back()
{
	m_Critical.Lock();
	if (m_DirList.size() > 0)
	{
		if (m_DirList.size() == 1)
		{
			m_DirList.clear();
		}
		else
		{
			m_DirList.pop_back();
			m_DirList.front().SetPrevious(&m_DirList.back());
			m_DirList.back().SetNext(&m_DirList.front());
		}
	}
	else
	{
	}
	m_Critical.Unlock();
}

template <typename T>
void CDequeForListContainer<T>::pop_front()
{
	m_Critical.Lock();
	if (m_DirList.size() > 0)
	{
		if (m_DirList.size() == 1)
		{
			m_DirList.clear();
		} 
		else
		{
			m_DirList.pop_front();
			m_DirList.front().SetPrevious(& m_DirList.back());
			m_DirList.back().SetNext(&m_DirList.front());
		}
	} 
	else
	{
	}
	m_Critical.Unlock();
}

template <typename T>
void CDequeForListContainer<T>::push_front(T _Val)
{
	m_Critical.Lock();

	iterator * t_Data;
	t_Data = new iterator;

	t_Data->SetData(_Val);

	if (m_DirList.size() > 0)
	{
		iterator *t_pFrontData;

		t_pFrontData = &m_DirList.front();

		//add iterator
		m_DirList.push_front(*t_Data);
		m_DirList.front().SetData(_Val);

		//set list iterator point
		m_DirList.front().SetPrevious(&m_DirList.back());
		m_DirList.back().SetNext(&m_DirList.front());
		t_pFrontData->SetPrevious(&m_DirList.front());
		m_DirList.front().SetNext(t_pFrontData);
	}
	else
	{
		m_DirList.push_front(*t_Data);
		m_DirList.front().SetNext(&m_DirList.back());
		m_DirList.front().SetPrevious(&m_DirList.back());
		m_DirList.front().SetData(_Val);
	}

	delete t_Data;
	m_Critical.Unlock();
}

template <typename T>
CDequeForListContainer<T>::CDequeForListContainer()
{

}

template <typename T>
CDequeForListContainer<T>::~CDequeForListContainer()
{
	m_Critical.Lock();
	m_DirList.clear();
	m_Critical.Unlock();
}

template <typename T>
void CDequeForListContainer<T>::push_back(T _Val)
{
	m_Critical.Lock();
	CDequeForListContainer<T>::iterator * t_Data;
	t_Data = new iterator;

	if (m_DirList.size() > 0)
	{
		CDequeForListContainer<T>::iterator *t_pBackData;

		t_pBackData = &m_DirList.back();

		//add iterator
		m_DirList.push_back(*t_Data);
		m_DirList.back().SetData(_Val);

		//set list iterator point
		m_DirList.front().SetPrevious(&m_DirList.back());
		m_DirList.back().SetNext(&m_DirList.front());
		t_pBackData->SetNext(&m_DirList.back());
		m_DirList.back().SetPrevious(t_pBackData);
	} 
	else
	{
		m_DirList.push_back(*t_Data);
		m_DirList.back().SetNext(&m_DirList.back());
		m_DirList.back().SetPrevious(&m_DirList.back());
		m_DirList.back().SetData(_Val);
	}

	delete t_Data;
	m_Critical.Unlock();
}
