#ifndef DCCHAIN_H
#define DCCHAIN_H
#include "stdafx.h"
#include "Exception.h"

template <class T>
class DCChain;

template <class T>
class DCChainNode
{
public:
	friend class DCChain<T>;
private:
	T data;
	DCChainNode<T>* next;
	DCChainNode<T>* prev;
};

//双向循环链表
template <class T>
class DCChain
{
public:
	DCChain();
	DCChain(const DCChain<T>& c);
	~DCChain();
	bool IsEmpty() const;
	int Length() const;
	bool Find(const int k, T& t) const;
	bool Search(const T& t, DCChainNode<T>*& node) const;
	DCChain<T>& Push_back(const T& t);
	DCChain<T>& Insert(const int k, const T& t);
	DCChain<T>& Delete(const int k, T& t);
	DCChain<T>& Swap(const int i, const int j);
	void Output(ostream& out) const;
	void Erase();
private:
	DCChainNode<T>* first;//哑元结点
	int length;
};

template<class T>
DCChain<T>::DCChain()
{
	first = new DCChainNode<T>();//空链表时first的前后指针都指向自己
	first->next = first;
	first->prev = first;
	length = 0;
}

template<class T>
DCChain<T>::DCChain(const DCChain<T>& c)
{
	DCChainNode<T>* pCur = c.first;
	DCChainNode<T>* pPre = new DCChainNode<T>();
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
	while (pCur != c.first)
	{
		DCChainNode<T>* pNode = new DCChainNode<T>();
		*pNode = *pCur;
		pPre->next = pNode;
		pNode->prev = pPre;
		pPre = pNode;
		pCur = pCur->next;
	}
	if (pPre)
	{
		pPre->next = first;
		first->prev = pPre;
	}
}

template<class T>
DCChain<T>::~DCChain()
{
	Erase();
	delete first;
	first = NULL;
}

template<class T>
bool DCChain<T>::IsEmpty() const
{
	return length == 0;
}

template<class T>
int DCChain<T>::Length() const
{
	return length;
}

template<class T>
bool DCChain<T>::Find(const int k, T& t) const
{
	//从位置1开始
	if (k < 1 || k > length || first->next == first)
		return false;
	DCChainNode<T>* pCur = first->next;
	for (int i = 1; i < k; i++)//位置移动到k
	{
		pCur = pCur->next;
	}
	t = pCur->data;
	return true;
}

template<class T>
bool DCChain<T>::Search(const T& t, DCChainNode<T>*& node) const
{
	if (first->next == first)
		return false;
	DCChainNode<T>* pCur = first->next;//从哑元结点的后一个元素开始
	int index = 1;
	while (pCur != first)
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
DCChain<T>& DCChain<T>::Push_back(const T& t)
{
	DCChainNode<T>* pNew = new DCChainNode<T>();
	pNew->data = t;
	pNew->next = first;
	pNew->prev = first->prev;
	length++;
	
	return *this;
}

//在k个元素之后插入t
template<class T>
DCChain<T>& DCChain<T>::Insert(const int k, const T& t)
{
	if (k < 1 || k > length + 1)
		throw OutOfBounds();
	DCChainNode<T>* pPrev = first->next;//从哑元结点的后一个元素开始
	for (int i = 1; i < k - 1; i++)//插入位置移动到k-1
	{
		pPrev = pPrev->next;
	}
	DCChainNode<T>* pCur = new DCChainNode<T>();
	pCur->data = t;
	if (k == 1)
	{
		pCur->next = first->next;
		pCur->prev = first;
		first->next = pCur;
		pCur->next->prev = pCur;
	}
	else
	{
		pCur->next = pPrev->next;
		pCur->prev = pPrev;
		pPrev->next = pCur;
		pCur->next->prev = pCur;
	}
	length++;
	return *this;
}

template<class T>
DCChain<T>& DCChain<T>::Delete(const int k, T& t)
{
	if (k < 1 || k > length)
		throw OutOfBounds();
	if (first == NULL)
	    throw BadCall();
	DCChainNode<T>* pCur = first->next;//从哑元结点的后一个元素开始
	for (int i = 1; i < k; i++)//删除位置移动到k
	{
		pCur = pCur->next;
	}
	if (k == 1)
	{
		t = pCur->data;
		first->next = pCur->next;
		pCur->next->prev = first;
		delete pCur;
	}
	else
	{
		t = pCur->next->data;
	    pCur->prev->next = pCur->next;
	    pCur->next->prev = pCur->prev;
	    delete pCur;
	}
	length--;
	return *this;
}

template<class T>
DCChain<T>& DCChain<T>::Swap(const int i, const int j)
{
	
}

//所有链表实现方式相同
template<class T>
void DCChain<T>::Output(ostream& out) const
{
	DCChainNode<T>* pCur = first->next;//从哑元结点的后一个元素开始
	while (pCur != first)
	{
		out << pCur->data << " ";
		pCur = pCur->next;
	}
	out << endl;
}

//清空链表
template<class T>
void DCChain<T>::Erase()
{
	DCChainNode<T>* pTemp = NULL;
	DCChainNode<T>* pCur = first->next;//从哑元结点的后一个元素开始
	while (pCur != first)
	{
		pTemp = pCur;
		pCur = pCur->next;
		delete pTemp;
	}
	first->next = first;
	first->prev = first;
	length = 0;
}

#endif
