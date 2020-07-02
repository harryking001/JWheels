#ifndef FREELIST_H
#define FREELIST_H
#include "stdafx.h"
#include "Exception.h"

template <class T>
class FreeList;

template <class T>
class FreeNode
{
public:
    friend class FreeList<T>;
private:
	T data;
	FreeNode<T>* next;
};

template <class T>
class FreeList
{
public:
	FreeList(int MaxSize = 100);
	~FreeList();
	FreeNode<T>* Allocate();
	void Deallocate(FreeNode<T>* p);
private:
	FreeNode<T>* first;
	FreeNode<T>* firstFree;
	int capacity;
};

template<class T>
FreeList<T>::FreeList(int MaxSize)
{
	capacity = MaxSize;
	FreeNode<T>* preNode = new FreeNode<T>();
	FreeNode<T>* curNode = NULL;
	first = firstFree = preNode;
	for (int i = 0; i < capacity - 1; i++)
	{
		curNode = new FreeNode<T>();
		preNode->next = curNode;
		preNode = curNode;
	}
	curNode = new FreeNode<T>();
	preNode->next = curNode;
	curNode->next = NULL;
}

template<class T>
FreeList<T>::~FreeList()
{
	FreeNode<T>* preNode = first;
	FreeNode<T>* curNode = NULL;
	while (preNode)
	{
		curNode = preNode->next;
		delete preNode;
		preNode = curNode;
	}
}

template<class T>
FreeNode<T>* FreeList<T>::Allocate()
{
	if (!firstFree)
	{
		throw NoMem();
	}
	FreeNode<T>* preNode = firstFree;
	firstFree = firstFree->next;
	return preNode;
}

template<class T>
void FreeList<T>::Deallocate(FreeNode<T>* p)
{
	p->next = firstFree;
	firstFree = p;
}

#endif