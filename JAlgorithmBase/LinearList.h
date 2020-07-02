#ifndef LINEARLIST_H
#define LINEARLIST_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>
using namespace std;

template<class T>
class LinearList
{
public:
	LinearList(int nMaxSize=10);
	~LinearList(){delete[] element;}
	bool IsEmpty(){return length==0;}
	int Length(){return length;}
	bool Find(int k, T& x) const;
	int Search(const T& x) const;
	LinearList<T>& Delete(int k, T& x);
    LinearList<T>& Insert(int k, const T& x);
    void Output(ostream& out) const;
	T Get(int k) const;
	LinearList<T>& Put(int k, T x);
    LinearList<T>& Swap(int i, int j);
private:
	int length;
	int MaxSize;
	T* element;
};

template<class T>
LinearList<T>::LinearList(int nMaxSize)
{
    length = 0;
    MaxSize = nMaxSize;
	element = new T[MaxSize];
}

template<class T>
bool LinearList<T>::Find(int k, T& x) const
{
	if(k<0||k>length) return false;
	x = element[k];
    return true;
}

template<class T>
int LinearList<T>::Search(const T& x) const
{
	for(int i=0;i<length;i++)
	{
		if(element[i] == x)
			return ++i;
	}
		return 0;
}

template<class T>
LinearList<T>& LinearList<T>::Delete (int k, T& x)
{
	if(Find(k,x))
	{
		for(int i=k-1;i<length;i++)
			element[i]=element[i+1];
		length--;
		return *this;
	}
	else
	{
		throw OutOfBounds();
	}
}

//在k个元素之后插入x
template<class T>
LinearList<T>& LinearList<T>::Insert(int k, const T& x)
{
    if(k<0||k>length)
		throw OutOfBounds();
    for(int i=length-1;i>k;i--)
	{
		element[i+1]=element[i];
	}
	element[k]=x;
	length++;
	return *this;
}

template<class T>
void LinearList<T>::Output(ostream& out) const
{
	for(int i=0;i<length;i++)
	{
        out<<element[i]<<" ";
	}
}

template<class T>
T LinearList<T>::Get(int k) const
{
    return element[k];
}

template<class T>
LinearList<T>& LinearList<T>::Put(int k, T x)
{
    element[k]=x;
	return *this;
}

template<class T>
LinearList<T>& LinearList<T>::Swap(int i, int j)
{
    T temp;
	temp = element[i];
	element[i] = element[j];
	element[j] = temp;
	return *this;
}

#endif