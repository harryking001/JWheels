#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

//数据队尾进，队头出
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
    maxSize = maxQueueSize + 1;//实际空间比数据多一个，用于判断队满
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

//头和尾下标相等则队列空
template<class T>
bool CircularQueue<T>::IsEmpty() const
{
	return front == rear;
}

//尾+1等于头则队列满
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
	queue[rear] = x;//从尾部加
	return *this;
}

template<class T>
CircularQueue<T>& CircularQueue<T>::DeQueue(T& x)
{
    if(IsEmpty()) 
		throw BadCall();
	x = queue[front + 1];
	front = ++front % maxSize;//从头部减
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