#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

template<class T>
class Sequence
{
public:
	Sequence(int maxSize = 20);
	~Sequence();
	T& operator[](int i) const;
	Sequence<T>& operator=(const Sequence<T>& s);
public:
	bool IsEmpty() const;
	int Length() const;
	bool Find(const int k, T& t) const;
	bool Search(const T& t, int& index) const;
	Sequence<T>& Push_back(const T& t);
	Sequence<T>& Insert(const int k, const T& t);
	Sequence<T>& Delete(const int k, T& t);
	Sequence<T>& Swap(const int i, const int j);
	void Output(ostream& out) const;
	void Erase();
private:
	int length;
	int capacity;
	T* element;
};

template<class T>
Sequence<T>::Sequence(int maxSize)
{
	length = 0;
	capacity = maxSize;
	element = new T[capacity];
}

template<class T>
Sequence<T>::~Sequence()
{
	Erase();
}

template<class T>
T& Sequence<T>::operator[](int i) const
{ 
	return element[i]; 
}

template<class T>
Sequence<T>& Sequence<T>::operator=(const Sequence<T>& s)
{
	if (*this == s)
		return *this;
	length = s.length;
	capacity = s.capacity;
	delete[] element;
	element = new T[capacity];
	for (int i = 0; i < length; i++)
		element[i] = s.element[i];
	return *this;
}

template<class T>
bool Sequence<T>::IsEmpty() const
{
	return length == 0; 
}

template<class T>
int Sequence<T>::Length() const
{ 
	return length; 
}

template<class T>
bool Sequence<T>::Find(const int k, T& t) const
{
	if(k < 0 || k >= length) 
		return false;
	t = element[k];
    return true;
}

template<class T>
bool Sequence<T>::Search(const T& t, int& index) const
{
	for(int i = 0;i < length;i++)
	{
		if (element[i] == t)
		{
			index = i;
            return true;
		}	
	}
	return false;
}

template<class T>
Sequence<T>& Sequence<T>::Push_back(const T& t)
{
	if (length == capacity)
	{
		capacity *= 2;
		T* temp = new T[capacity];
		for (int i = 0; i < length; i++)
			temp[i] = element[i];
		delete[] element;
		element = temp;
		delete[] temp;
	}
	element[length++] = t;
	return *this;
}

//ÔÚÎ»ÖÃk²åÈët
template<class T>
Sequence<T>& Sequence<T>::Insert(const int k, const T& t)
{
	if (k < 0 || k > length)
		throw OutOfBounds();
	if (length == capacity)
	{
		capacity *= 2;
		T* temp = new T[capacity];
		for (int i = 0; i < length; i++)
			temp[i] = element[i];
		delete[] element;
		element = temp;
		delete[] temp;
		temp = NULL;
	}
    for(int i = length -1;i >= k;i--)
	{
		element[i+1] = element[i];
	}
	element[k] = t;
	length++;
	return *this;
}

template<class T>
Sequence<T>& Sequence<T>::Delete(const int k, T& t)
{
	if (Find(k, t))
	{
		for (int i = k; i < length; i++)
			element[i] = element[i + 1];
		length--;
		return *this;
	}
	else
	{
		throw BadInput();
	}
}

template<class T>
Sequence<T>& Sequence<T>::Swap(const int i, const int j)
{
	if (i < 0 || i >= length || j < 0 || j >= length)
		throw OutOfBounds();
	T temp;
	temp = element[i];
	element[i] = element[j];
	element[j] = temp;
	return *this;
}

template<class T>
void Sequence<T>::Output(ostream& out) const
{
	for (int i = 0; i < length; i++)
	{
		out << element[i] << " ";
	}
	out << endl;
}

template<class T>
void Sequence<T>::Erase()
{
	length = 0;
}

#endif