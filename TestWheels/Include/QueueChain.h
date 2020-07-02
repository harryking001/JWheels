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

//���������ָ����Ϊβ��
template<class T>
class QueueChain
{
public:
	QueueChain();
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
	if(front)//���ǿն��еĻ��ڶ�β��Ԫ��
	    rear->next = pCur;
	else
		front = pCur;
    rear = pCur;//����Ҫ��˳�������������һ��Ԫ�صĿռ䣬ֻ��һ������ʱ��ͷβָ��ͬһ�����
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