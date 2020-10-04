#ifndef STACKSEQUENCE_H
#define STACKSEQUENCE_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

template<class T>
class StackSequence
{
public:
	StackSequence(int maxSize = 5);
	StackSequence(const StackSequence<T>& s);
	~StackSequence();
	bool IsEmpty() const;
	bool IsFull() const;
	T Top() const;
	StackSequence<T>& Push(const T& x);
	StackSequence<T>& Pop(T& x);
	void Output(ostream& out) const;
	void Erase();
private:
    int top;
	int maxTop;
	T* stack;
};

template<class T>
StackSequence<T>::StackSequence(int maxSize)
{
    maxTop = maxSize - 1;//×î´óÕ»¶¥Î»ÖÃ£¨0~maxSize-1£©
	top = -1;
	stack = new T[maxSize];
}

template<class T>
StackSequence<T>::StackSequence(const StackSequence<T>& s)
{
	top = s.top;
	maxTop = s.maxTop;
	stack = new T[maxTop + 1];
	for (int i = 0; i < maxTop + 1; i++)
	{
		stack[i] = s.stack[i];
	}
}

template<class T>
StackSequence<T>::~StackSequence()
{
	delete[] stack;
	stack = NULL;
}

template<class T>
bool StackSequence<T>::IsEmpty() const
{ 
	return top == -1;
}

template<class T>
bool StackSequence<T>::IsFull() const
{ 
	return top == maxTop; 
}

template<class T>
T StackSequence<T>::Top() const
{
	if(IsEmpty())
		throw BadCall();
	return stack[top];
}

template<class T>
StackSequence<T>& StackSequence<T>::Push(const T& x)
{
    if(IsFull()) 
		throw NoMem();
	stack[++top] = x;
	return *this;
}

template<class T>
StackSequence<T>& StackSequence<T>::Pop(T& x)
{
    if(IsEmpty()) 
		throw BadCall();
	x = stack[top--];
	return *this;
}

template<class T>
void StackSequence<T>::Output(ostream& out) const
{
	for (int i = 0; i <= top; i++)
	{
		out << stack[i] << " ";
	}
	out << endl;
}

template<class T>
void StackSequence<T>::Erase()
{
	top = -1;
}

#endif