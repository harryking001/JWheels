#ifndef QUEUECHAIN_H
#define QUEUECHAIN_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

template<class T>
class QueueChain;

template<class T>
class QueueChainNode
{
public:
    friend class QueueChain<T>;
private:
	T data;
	QueueChainNode<T>* next;
};

//单链表，结点指向方向为尾巴
template<class T>
class QueueChain
{
public:
	QueueChain();
	QueueChain(const QueueChain<T>& q);
	~QueueChain();
	bool IsEmpty() const;
	bool IsFull() const;
    QueueChain<T>& EnQueue(const T& t);
	QueueChain<T>& DeQueue(T& t);
	void Output(ostream& out) const;
	void Erase();
private:
	QueueChainNode<T>* front;
	QueueChainNode<T>* rear;
};

template<class T>
QueueChain<T>::QueueChain()
{
	front = rear = NULL;
}

template<class T>
QueueChain<T>::QueueChain(const QueueChain<T>& q)
{
	QueueChainNode<T>* pCur = q.front;
	QueueChainNode<T>* pPre = new QueueChainNode<T>();
	if (pCur)
	{
		*pPre = *pCur;
		front = pPre;
		pCur = pCur->next;
	}
	else
	{
		delete pPre;
		pPre = NULL;
	}
	while (pCur)
	{
		QueueChainNode<T>* pNode = new QueueChainNode<T>();
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
QueueChain<T>::~QueueChain()
{
	QueueChainNode<T>* pCur = NULL;
	while(front)
	{
		pCur = front->next;
		delete front;
		front = pCur;
	}
}

template<class T>
bool QueueChain<T>::IsEmpty() const
{ 
	return (front == NULL) ? true : false;
}

//链表队列正常情况下不会满，除非机器内存耗尽
template<class T>
bool QueueChain<T>::IsFull() const
{
    try
	{
		QueueChainNode<T>* pCur = new QueueChainNode<T>;
		delete pCur;
		return false;
	}
	catch(...)
	{
		return true;
	}
}

template<class T>
QueueChain<T>& QueueChain<T>::EnQueue(const T& t)
{
    if(IsFull())
		throw NoMem();
	QueueChainNode<T>* pCur = new QueueChainNode<T>;
	pCur->data = t;
	pCur->next = NULL;
	if(front)//不是空队列的话在队尾加元素
	    rear->next = pCur;
	else
		front = pCur;
    rear = pCur;//不需要像顺序队列那样多留一个元素的空间，只有一个结点的时候头尾指向同一个结点
	return *this;
}

template<class T>
QueueChain<T>& QueueChain<T>::DeQueue(T& t)
{
    if(IsEmpty()) 
		throw BadCall();
	t = front->data;
	QueueChainNode<T>* pCur;
	pCur = front;
	front = front->next;
    delete pCur;
	return *this;
}

template<class T>
void QueueChain<T>::Output(ostream& out) const
{
	QueueChainNode<T>* pCur = front;
	while (pCur)
	{
		out << pCur->data << " ";
		pCur = pCur->next;
	}
	out << endl;
}

template<class T>
void QueueChain<T>::Erase()
{
	QueueChainNode<T>* pCur = NULL;
	while (front)
	{
		pCur = front->next;
		delete front;
		front = pCur;
	}
}

#endif