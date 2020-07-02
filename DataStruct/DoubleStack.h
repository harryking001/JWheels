#ifndef DOUBLESTACK_H
#define DOUBLESTACK_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

//双栈共享一块内存
//栈1从数组头开始向尾方向增加，栈2从数组尾开始向头方向增加
//当两栈的top指针相邻时，栈满
//此数据结构适用于两个栈空间需求相反的情况
template<class T>
class DoubleStack
{
public:
	DoubleStack(int MaxSize = 5);
	~DoubleStack();	
	bool IsEmpty() const;
	bool IsFull() const;
	T Top(int stackNum) const;
	DoubleStack<T>& Push(const T& t, int stackNum);
	DoubleStack<T>& Pop(T& t, int stackNum);
	void Output(ostream& out, int stackNum) const;
	void Erase(int stackNum);
private:
	T* element;
	int maxSize;
	int top1;
	int top2;
};

template<class T>
DoubleStack<T>::DoubleStack(int MaxSize)
{
	maxSize = MaxSize;
	element = new T[MaxSize];
	top1 = -1;
	top2 = maxSize;
}

template<class T>
DoubleStack<T>::~DoubleStack()
{
	delete[] element;
	element = NULL;
	top1 = -1;
	top2 = maxSize;
	maxSize = 0;
}

template<class T>
bool DoubleStack<T>::IsEmpty() const 
{ 
	return top1 == -1 && top2 == maxSize; 
}

template<class T>
bool DoubleStack<T>::IsFull() const 
{ 
	return top1 + 1 == top2; 
}

template<class T>
T DoubleStack<T>::Top(int stackNum) const
{
	if ((stackNum == 1 && top1 == -1) || (stackNum == 2 && top2 == maxSize))
	{
		throw BadCall();
	}
	if (stackNum == 1)
	{
		return element[top1];
	}
	else if (stackNum == 2)
	{
		return element[top2];
	}
}

template<class T>
DoubleStack<T>& DoubleStack<T>::Push(const T& t, int stackNum)
{
	if (IsFull())
	{
		throw NoMem();
	}
	if (stackNum == 1)
	{
		element[++top1] = t;
	}
	else if (stackNum == 2)
	{
		element[--top2] = t;
	}
	return *this;
}

template<class T>
DoubleStack<T>& DoubleStack<T>::Pop(T& t, int stackNum)
{
	if ((stackNum == 1 && top1 == -1) || (stackNum == 2 && top2 == maxSize))
	{
		throw BadCall();
	}
	if (stackNum == 1)
	{
		t = element[top1--];
	}
	else if (stackNum == 2)
	{
		t = element[top2++];
	}
	else
	{
		throw BadInput();
	}
	return *this;
}

template<class T>
void DoubleStack<T>::Output(ostream& out, int stackNum) const
{
	if (stackNum == 1)
	{
        for (int i = 0; i <= top1; i++)
        {
        	out << element[i] << " ";
        }
	}
	else if(stackNum == 2)
	{
		for (int i = maxSize - 1; i >= top2; i--)
		{
			out << element[i] << " ";
		}
	}
	else
	{
		throw BadInput();
	}
	out << endl;
}

template<class T>
void DoubleStack<T>::Erase(int stackNum)
{
	if (stackNum == 1)
	{
        top1 = -1;
	}
	else if (stackNum == 2)
	{
        top2 = maxSize;
	}
	else
	{
		throw BadInput();
	}
}

#endif