#ifndef CIRCULARCHAIN_H
#define CIRCULARCHAIN_H
#include "stdafx.h"
#include "Exception.h"

template <class T>
class CircularChain;

template <class T>
class CircularChainNode
{
public:
	friend class CircularChain<T>;
private:
	T data;
	CircularChainNode<T>* next;
};

//循环链表
template <class T>
class CircularChain
{
public:
	CircularChain();
	CircularChain(const CircularChain<T>& c);
	~CircularChain();
public:
	bool IsEmpty() const;
	int Length() const;
	bool Find(const int k, T& t) const;
	bool Search(const T& t, CircularChainNode<T>*& node) const;
	CircularChain<T>& Push_back(const T& t);
	CircularChain<T>& Insert(const int k, const T& t);
	CircularChain<T>& Delete(const int k, T& t);
	CircularChain<T>& Swap(const int i, const int j);
	void Output(ostream& out) const;
	void Erase();
private:
	CircularChainNode<T>* first;//哑元头结点，方便编程
	int length;//长度变量可以简化程序
};

template<class T>
CircularChain<T>::CircularChain()
{
	first = new CircularChainNode<T>();
	first->next = first;
	length = 0;
}

template<class T>
CircularChain<T>::CircularChain(const CircularChain<T>& c)
{
	CircularChainNode<T>* pCur = c.first;
	CircularChainNode<T>* pPre = new CircularChainNode<T>();
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
		CircularChainNode<T>* pNode = new CircularChainNode<T>();
		*pNode = *pCur;
		pPre->next = pNode;
		pPre = pNode;
		pCur = pCur->next;
	}
	if (pPre)
	{
		pPre->next = first;
	}
}

template<class T>
CircularChain<T>::~CircularChain()
{
	Erase();
	delete first;
	first = NULL;
}

template<class T>
bool CircularChain<T>::IsEmpty() const
{
	return length == 0;
}

template<class T>
int CircularChain<T>::Length() const
{
	return length;
}

template<class T>
bool CircularChain<T>::Find(const int k, T& t) const
{
	//从位置1开始
	if (k < 1 || k > length || first->next == first)
		return false;
	CircularChainNode<T>* pCur = first->next;//从哑元结点的后一个元素开始
	for(int i = 1;i < k;i++)
	{
		pCur = pCur->next;
	}
	t = pCur->data;
	return true;
}

template<class T>
bool CircularChain<T>::Search(const T& t, CircularChainNode<T>*& node) const
{
	if (first->next == first)
		return false;
	CircularChainNode<T>* pCur = first->next;//从哑元结点的后一个元素开始
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
CircularChain<T>& CircularChain<T>::Push_back(const T& t)
{
	CircularChainNode<T>* pCur = first->next;//从哑元结点的后一个元素开始
	CircularChainNode<T>* pLast = pCur;
	CircularChainNode<T>* pNew = new CircularChainNode<T>();
	pNew->data = t;
	pNew->next = first;
	if (pCur == first)
	{
        first->next = pNew;
		pNew->next = first;
	}
	while (pCur != first)
	{
		pLast = pCur;
		pCur = pCur->next;
	}
	pLast->next = pNew;
	length++;
	return *this;
}

//在第k个元素的位置插入t，原元素后移
template<class T>
CircularChain<T>& CircularChain<T>::Insert(const int k, const T& t)
{
	//从位置1开始，位置length+1是在最后一个元素后面插入新元素
	if (k < 1 || k > length + 1)
		throw OutOfBounds();
	CircularChainNode<T>* pPrev = first->next;//从哑元结点的后一个元素开始
	//插入位置移动到k-1
	for (int i = 1; i < k - 1; i++)
	{
		pPrev = pPrev->next;
	}
	CircularChainNode<T>* pCur = new CircularChainNode<T>();
	pCur->data = t;
	if (k == 1)
	{
		pCur->next = first->next;
		first->next = pCur;
	}
	else
	{
        pCur->next = pPrev->next;
	    pPrev->next = pCur;
	}
	length++;
	return *this;
}

template<class T>
CircularChain<T>& CircularChain<T>::Delete(const int k, T& t)
{
	//从位置1开始
	if (k < 1 || k > length)
		throw OutOfBounds();
	if (first->next == first)//空链表
	    throw BadCall();
	CircularChainNode<T>* pPrev = first->next;//从哑元结点的后一个元素开始
    for (int i = 1; i < k - 1; i++)
	{
		pPrev = pPrev->next;
	}
    CircularChainNode<T>* pCur = pPrev->next;
	if (k == 1)
	{
		t = pPrev->data;
		first->next = pPrev->next;
		delete pPrev;
	}
	else
	{
		t = pCur->data;
        pPrev->next = pCur->next;
	    delete pCur;
	}
	length--;
	return *this;
}

template<class T>
CircularChain<T>& CircularChain<T>::Swap(const int i, const int j)
{
	
}

//所有链表实现方式相同
template<class T>
void CircularChain<T>::Output(ostream& out) const
{
	CircularChainNode<T>* pCur = first->next;//从哑元结点的后一个元素开始
	while (pCur != first)
	{
		out << pCur->data << " ";
		pCur = pCur->next;
	}
	out << endl;
}

//清空链表
template<class T>
void CircularChain<T>::Erase()
{
	CircularChainNode<T>* pTemp = NULL;
	CircularChainNode<T>* pCur = first->next;//从哑元结点的后一个元素开始
	while (pCur != first)
	{
		pTemp = pCur;
        pCur = pCur->next;
        delete pTemp;
	}
	first->next = first;
	length = 0;
}

#endif

