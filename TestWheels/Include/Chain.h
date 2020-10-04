#ifndef CHAIN_H
#define CHAIN_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

template <class T>
class Chain;

template <class T>
class ChainNode
{
public:
	friend class Chain<T>;
private:
	T data;
	ChainNode<T>* next;
};

template <class T>
class Chain
{
public:
	Chain();
	Chain(const Chain<T>& c);
	~Chain();
public:
	bool IsEmpty() const;
    int Length() const;
	bool Find(const int k, T& t) const;
	bool Search(const T& t, ChainNode<T>*& node) const;
	Chain<T>& Push_back(const T& t);
	Chain<T>& Insert(const int k, const T& t);
	Chain<T>& Delete(const int k, T& t);
	Chain<T>& Swap(const int i, const int j);
	void Output(ostream& out) const;
	void Erase();
private:
	ChainNode<T>* first;//非哑元结点
};

template<class T>
Chain<T>::Chain()
{
	first = NULL;
}

template<class T>
Chain<T>::Chain(const Chain<T>& c)
{
	ChainNode<T>* pCur = c.first;
	ChainNode<T>* pPre = new ChainNode<T>();
	if (pCur)
	{
		*pPre = *pCur;
		first = pPre;
		pCur = pCur->next;
	}
	else
	{
		delete pPre;
		pPre = NULL;
	}
	while (pCur)
	{
		ChainNode<T>* pNode = new ChainNode<T>();
		*pNode = *pCur;
		pPre->next = pNode;
		pPre = pNode;
		pCur = pCur->next;
	}
	if (pPre)
	{
		pPre->next = NULL;
	}
}

template<class T>
Chain<T>::~Chain()
{
	Erase();
}

template<class T>
bool Chain<T>::IsEmpty() const
{
	return first == NULL;
}

template<class T>
int Chain<T>::Length() const
{
	int length = 0;
    ChainNode<T>* pCur = first;
    while(pCur)
	{
		pCur = pCur->next;
		length++;
	}
	return length;
}

//寻找第k个位置的元素，位置从1开始
template<class T>
bool Chain<T>::Find(const int k, T& t) const
{
    if(k < 1)
		return false;
	int index = 1;
	ChainNode<T>* pCur = first;
	//元素不为空且位置小于k
	while(pCur && index < k)
	{
		pCur = pCur->next;
		index++;
	}
	if(pCur)
	{
        t = pCur->data;
		return true;
	}
	else 
		return false;
}

//寻找元素t所在结点指针
template<class T>
bool Chain<T>::Search(const T& t, ChainNode<T>*& node) const
{
    ChainNode<T>* pCur = first;
	int index = 1;
	while(pCur)
	{
		if (pCur->data == t)
		{
            node = pCur;
			return true;
		}
		pCur = pCur->next;
		index++;
	}
	return false;
}

template<class T>
Chain<T>& Chain<T>::Push_back(const T& t)
{
	ChainNode<T>* pCur = first;
	ChainNode<T>* pLast = first;
	ChainNode<T>* pNew = new ChainNode<T>();
	pNew->data = t;
	pNew->next = NULL;
	if (!pCur)
		first = pNew;
	while (pCur)
	{
		pLast = pCur;
		pCur = pCur->next;
	}
	pLast->next = pNew;
	return *this;
}

//在第k个元素的位置插入t，原元素后移
template<class T>
Chain<T>& Chain<T>::Insert (const int k, const T& t)
{
    if(k < 1)//从位置1开始
		throw OutOfBounds();
    ChainNode<T>* pPrev = first;
    int index = 1;
	//插入位置移动到k-1
	while(pPrev && index < k - 1)
	{
		pPrev = pPrev->next;
		index++;
	}
	if(k > 1 && !pPrev)//考虑链表中插入第一个元素的情况
		throw OutOfBounds();

    ChainNode<T>* pCur = new ChainNode<T>();
	pCur->data = t;
	if(k == 1)
	{
		pCur->next = first;
		first = pCur;
	}
	else
	{
		pCur->next = pPrev->next;
		pPrev->next = pCur;
	}
	return *this;
}

//删除第k个位置的元素，位置从1开始
template<class T>
Chain<T>& Chain<T>::Delete(const int k, T& t)
{
	if (k < 1)
		throw OutOfBounds();
	if (first == NULL)//空链表报错
		throw BadCall();
	ChainNode<T>* pPrev = first;
	int index = 1;
	//删除位置移动到k-1
    while (pPrev && index < k - 1)
	{
		pPrev = pPrev->next;
		index++;
	}
    if (!pPrev || !pPrev->next)//如果k-1或k位置元素为空，报错
		throw OutOfBounds();
    ChainNode<T>* pCur = pPrev->next;
	if (k == 1)
	{
		t = pPrev->data;
		first = pPrev->next;
		delete pPrev;
	}
	else
	{
		t = pCur->data;
	    pPrev->next = pCur->next;
	    delete pCur;
	}
	return *this;
}

template<class T>
Chain<T>& Chain<T>::Swap(const int i, const int j)
{

}

//所有链表实现方式相同
template<class T>
void Chain<T>::Output(ostream& out) const
{
	ChainNode<T>* pCur = first;
	while (pCur)
	{
		out << pCur->data << " ";
		pCur = pCur->next;
	}
	out << endl;
}

//清空链表
template<class T>
void Chain<T>::Erase()
{
    ChainNode<T>* pCur = NULL;
	while(first)
	{
		pCur = first->next;
	    delete first;
	    first = pCur;
	}
}

#endif