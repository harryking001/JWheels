#ifndef SIMCHAIN_H
#define SIMCHAIN_H
#include "stdafx.h"
#include "Exception.h"

template<class T>
class SimSpace;
template<class T>
class SimChain;

//模拟指针（静态链表）
template<class T>
class SimNode
{
public:
    friend class SimSpace<T>;
private:
	T data;
	int link;
};

template<class T>
class SimSpace
{
	friend SimChain<T>;
public:
	SimSpace(int maxSpaceSize = 100);
	SimSpace(SimSpace<T>& s) = delete;//不允许拷贝
	~SimSpace();
	int Allocate();
	void Deallocate(int i);
	SimNode<T>* GetNode(int i);
private:
	int first;//存储池中可用的第一个结点
	int capacity;
	SimNode<T>* node;
};

template<class T>
SimSpace<T>::SimSpace(int maxSpaceSize)
{
	capacity = maxSpaceSize;
	node = new SimNode<T>[capacity];
	for (int i = 0; i < capacity - 1; i++)
		node[i].link = i + 1;
	node[capacity - 1].link = -1;
	first = 0;
}
template<class T>
SimSpace<T>::~SimSpace()
{
	first = 0;
	delete[] node;
}

template<class T>
int SimSpace<T>::Allocate()
{
	if (first == -1)
	{
		int size = capacity;
		capacity *= 2;
		SimNode<T>* temp = new SimNode<T>[capacity];
		for (int i = 0; i < size; i++)
		{
            temp[i] = node[i];
			if (temp[i].link == -1)
			{
				temp[i].link = size;
			}
		}
		for (int i = size; i < capacity - 1; i++)
		{
			temp[i].link = i + 1;
		}
		node[capacity - 1].link = -1;
		first = size;
			
		delete[] node;
		node = temp;
		delete[] temp;
		temp = NULL;
	}
	int i = first;
	first = node[i].link;
	return i;
}

template<class T>
void SimSpace<T>::Deallocate(int i)
{
	//如果i是空闲内存的下标，会有问题
	node[i].link = first;
	first = i;
}

template<class T>
SimNode<T>* SimSpace<T>::GetNode(int i)
{
	return &node[i];
}


template <class T>
class SimChain
{
public:
	SimChain() { first = -1; }
	~SimChain();
	bool IsEmpty() const { return first == -1; }
	int Length() const;
	bool Find(int k, T& t) const;
	int Search(const T& t) const;
	SimChain<T>& Delete(int k, T& t);
	SimChain<T>& Insert(int k, const T& t);
	void Erase();
private:
	int first;
	static SimSpace<T> s;
};

template<class T>
SimChain<T>::~SimChain()
{
	Erase();
}

template<class T>
int SimChain<T>::Length() const
{
	int length = 0;
	int pCur = first;
	while (pCur != -1)
	{
		pCur = (s.GetNode[pCur])->link;
		length++;
	}
	return length;
}

template<class T>
bool SimChain<T>::Find(int k, T& t) const
{
	if (k < 1) return false;
	int index = 1;
	int pCur = first;
	while (pCur != -1 && index < k)
	{
		pCur = (s.GetNode[pCur])->link;
		index++;
	}
	if (pCur != -1)
	{
		t = (s.GetNode[pCur])->data;
		return true;
	}
	else
		return false;
}

template<class T>
int SimChain<T>::Search(const T& t) const
{
	int pCur = first;
	int index = 0;
	while (pCur != -1)
	{
		index++;
		if ((s.GetNode[pCur])->data)
			return index;
		pCur = (s.GetNode[pCur])->link;
	}
	return 0;
}

template<class T>
SimChain<T>& SimChain<T>::Delete(int k, T& t)
{
	if (k < 1 || first == -1)
		throw OutOfBounds();
	int pPrev = first;
	int index = 1;
	if (k == 1)
	{
		first = (s.GetNode[pPrev])->link;
		t = (s.GetNode[pPrev])->data;
		s.Deallocate(pPrev);
	}
	else
	{
		while (pPrev != -1 && index < k - 1)
		{
			index++;
			(s.GetNode[pPrev])->link;
		}
	}
	if (pPrev != -1)
		throw OutOfBounds();
	int pCur = (s.GetNode[pPrev])->link;
	t = (s.GetNode[pCur])->data;
	(s.GetNode[pPrev])->link = (s.GetNode[pCur])->link;
	s.Deallocate(pCur);
	return *this;
}

//在k个元素之后插入t
template<class T>
SimChain<T>& SimChain<T>::Insert(int k, const T& t)
{
	if (k < 0)
		throw OutOfBounds();
	int pPrev = first;
	int index = 1;
	while (pPrev != -1 && index < k)
	{
		index++;
		(s.GetNode[pPrev])->link;
	}
	if (k > 0 && pPrev != -1)
		throw OutOfBounds();

	int pCur = s.Allocate();
	(s.GetNode[pCur])->data = t;
	if (k == 0)
	{
		(s.GetNode[pCur])->link = first;
		first = pCur;
	}
	else
	{
		(s.GetNode[pCur])->link = (s.GetNode[pPrev])->link;
		(s.GetNode[pPrev])->link = pCur;
	}
	return *this;
}

//清空链表
template<class T>
void SimChain<T>::Erase()
{
	int pCur = 0;
	while (first != -1)
	{
		pCur = (s.GetNode[pCur])->link;
		s.Deallocate(first);
		first = pCur;
	}
}

#endif
