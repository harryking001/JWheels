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
	T* element;
};

template<class T>
StackSequence<T>::StackSequence(int maxSize)
{
    maxTop = maxSize - 1;
	top = -1;
	element = new T[maxSize];
}

template<class T>
StackSequence<T>::~StackSequence()
{
	delete[] element;
	element = NULL;
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
	return element[top];
}

template<class T>
StackSequence<T>& StackSequence<T>::Push(const T& x)
{
    if(IsFull()) 
		throw NoMem();
	element[++top] = x;
	return *this;
}

template<class T>
StackSequence<T>& StackSequence<T>::Pop(T& x)
{
    if(IsEmpty()) 
		throw BadCall();
	x = element[top--];
	return *this;
}

template<class T>
void StackSequence<T>::Output(ostream& out) const
{
	for (int i = 0; i <= top; i++)
	{
		out << element[i] << " ";
	}
	out << endl;
}

template<class T>
void StackSequence<T>::Erase()
{
	top = -1;
}

#endif