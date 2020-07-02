#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

template <class K, class V>
class SortedList;

template<class K, class V>
class ListNode
{
public:
	friend class SortedList<K, V>;//使有序链可以访问节点数据成员
private:
	K key;//关键字
	V value;//数据
};

//k唯一，不能有重复，有序表的node元素按照k值从小到大排列
template<class K, class V>
class SortedList
{
public:
	SortedList(int maxSize = 20);
	~SortedList();
	bool IsEmpty() const;
	int Length() const;
	bool Search(const K& k, V& v, int& index) const;
	SortedList<K, V>& Insert(const K& k, const V& v);
	SortedList<K, V>& Delete(const K& k, V& v);
	void Output(ostream& out) const;
	void Erase();
private:
	bool BinSearch(int head, int tail, const K k, V& v, int& index) const;
	int length;
	int capacity;
	ListNode<K, V>* node;

};

template<class K, class V>
SortedList<K,V>::SortedList(int maxSize)
{
	length = 0;
	capacity = maxSize;
	node = new ListNode<K, V>[capacity];
}

template<class K, class V>
SortedList<K, V>::~SortedList()
{
	delete[] node;
	node = NULL;
	capacity = 0;
	length = 0;
}

template<class K, class V>
bool SortedList<K, V>::IsEmpty() const
{
	return length == 0;
}

template<class K, class V>
int SortedList<K, V>::Length() const
{
	return length;
}

template<class K, class V>
bool SortedList<K, V>::Search(const K& k, V& v, int& index) const
{
	int head = 0;
	int tail = length - 1;
	if (BinSearch(head, tail, k, v, index))
		return true;
	else
		return false;
}

template<class K, class V>
SortedList<K, V>& SortedList<K, V>::Insert(const K& k, const V & v)
{
	if (length == capacity)
	{
		capacity *= 2;
		ListNode<K, V>* temp = new ListNode<K, V>[capacity];
		for (int i = 0; i < length; i++)
			temp[i] = node[i];
		delete[] node;
		node = temp;
		delete[] temp;
	}
	int i = length - 1;
	for (; i >= 0; i--)
	{
		if (k < node[i].key)
		{
            node[i + 1] = node[i];
		}    
		else
		{
			break;
		}
	}
    node[i+1].key = k;
	node[i+1].value = v;
	length++;

	return *this;
}

template<class K, class V>
SortedList<K, V>& SortedList<K, V>::Delete(const K& k, V & v)
{
	int index = 0;
	bool bRet = Search(k, v, index);
	if (bRet)
	{
		for (int i = index; i < length - 1; i++)
		{
			node[i] = node[i + 1];
		}
		length--;
	}
	else
	{
	    throw BadInput();
	}

	return *this;
}

template<class K, class V>
bool SortedList<K, V>::BinSearch(int head, int tail, const K k, V& v, int& index) const
{
	if (head > tail)
	{
		if (node[tail].key < k)
			index = tail;
		else
			index = tail - 1;
        return false;
	}	
	int mid = (head + tail) / 2;
	if (node[mid].key > k)
	{
		return BinSearch(head, mid - 1, k, v, index);
	}
	else if (node[mid].key < k)
	{
		return BinSearch(mid + 1, tail, k, v, index);
	}
	else
	{
		index = mid;
        v = node[mid].value;
	}
	return true;
}

template<class K, class V>
void SortedList<K, V>::Output(ostream& out) const
{
	for (int i = 0; i < length; i++)
	{
		out << node[i].value << " ";
	}
	out << endl;
}

template<class K, class V>
void SortedList<K, V>::Erase()
{
	length = 0;
}

#endif
