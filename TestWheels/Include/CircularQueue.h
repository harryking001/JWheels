#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

//���ݶ�β������ͷ��
template<class T>
class CircularQueue
{
public:
	CircularQueue(int maxQueueSize = 5);
	~CircularQueue();
	bool IsEmpty() const;
	bool IsFull() const;
	CircularQueue<T>& EnQueue(const T& x);
	CircularQueue<T>& DeQueue(T& x);
	void Output(ostream& out) const;
	void Erase();
private:
    int front;
	int rear;
	int maxSize;
	T* queue;
};

template<class T>
CircularQueue<T>::CircularQueue(int maxQueueSize)
{
    maxSize = maxQueueSize + 1;//ʵ�ʿռ�����ݶ�һ���������ж϶���
	queue = new T[maxSize];
	front = rear = 0;
}

template<class T>
CircularQueue<T>::~CircularQueue()
{
	delete[] queue;
	queue = NULL;
	maxSize = front = rear = 0;
}

//ͷ��β�±��������п�
template<class T>
bool CircularQueue<T>::IsEmpty() const
{
	return front == rear;
}

//β+1����ͷ�������
template<class T>
bool CircularQueue<T>::IsFull() const
{
	return (rear + 1) % maxSize == front;
}

template<class T>
CircularQueue<T>& CircularQueue<T>::EnQueue(const T& x)
{
    if(IsFull()) 
		throw NoMem();
	rear = ++rear % maxSize;
	queue[rear] = x;//��β����
	return *this;
}

template<class T>
CircularQueue<T>& CircularQueue<T>::DeQueue(T& x)
{
    if(IsEmpty()) 
		throw BadCall();
	x = queue[front + 1];
	front = ++front % maxSize;//��ͷ����
	return *this;
}

template<class T>
void CircularQueue<T>::Output(ostream& out) const
{
	int index = front;
	while (index != rear)
	{
		index = ++index % maxSize;
		out << queue[index] << " ";
	}
	out << endl;
}

template<class T>
void CircularQueue<T>::Erase()
{
	front = rear = 0;
}

#endif