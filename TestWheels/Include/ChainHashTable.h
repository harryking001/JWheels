#ifndef CHAINHASHTABLE_H
#define CHAINHASHTABLE_H
#include "stdafx.h"
#include "SortedChain.h"
#include "Define.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

template<class K, class V>
class ChainHashTable
{
public:
	ChainHashTable(int divisor = 11);
	~ChainHashTable();
	bool IsEmpty() const;
	int Length() const;
	bool Find(const K& k, V& v) const;
	ChainHashTable<K, V>& Insert(const K& k, const V& v);
    ChainHashTable<K, V>& Delete(const K& k, V& v);
	void Output(ostream& out) const;
	void Erase();
private:
	int D;//除数
	SortedChain<K, V>* ht;//有序链表数组，每个数组元素为一条有序链表
	int hashFunc(const K& k)const;//散列（映射）函数
};

template<class K, class V>
ChainHashTable<K, V>::ChainHashTable(int divisor)
{
	D = divisor;
	ht = new SortedChain<K, V>[D];
}

template<class K, class V>
ChainHashTable<K, V>::~ChainHashTable()
{
	D = 0;
    delete[] ht;
	ht = NULL;
}

template<class K, class V>
bool ChainHashTable<K, V>::IsEmpty() const
{
	for (int i = 0; i < D; i++)
	{
		if (ht[i].IsEmpty() == false)
		{
			return false;
		}
	}
	return true;
}

template<class K, class V>
int ChainHashTable<K, V>::Length() const
{
	int length = 0;
	for (int i = 0; i < D; i++)
	{
		length += ht[i].Length();
	}
	return length;
}

template<class K, class V>
bool ChainHashTable<K, V>::Find(const K& k, V& v) const
{
	int i = hashFunc(k);
	SortedChainNode<K,V>* node = NULL;
    bool bRet = ht[i].Search(k, node);
	if (bRet)
	{
		v = node->value;
	}
	return bRet;
}

template<class K, class V>
ChainHashTable<K, V>& ChainHashTable<K, V>::Insert(const K& k, const V& v)
{
	int i = hashFunc(k);
    ht[i].Insert(k,v);
	return *this;
}

template<class K, class V>
ChainHashTable<K, V>& ChainHashTable<K, V>::Delete(const K& k,V& v)
{
	int i = hashFunc(k);
    ht[i].Delete(k,v);
	return *this;
}

template<class K, class V>
int ChainHashTable<K, V>::hashFunc(const K & k) const
{
	return k%D;
}

template<class K, class V>
void ChainHashTable<K, V>::Output(ostream& out) const
{
	for (int i = 0; i < D; i++)
	{
		ht[i].Output(out);
	}
}

template<class K, class V>
void ChainHashTable<K, V>::Erase()
{
	for (int i = 0; i < D; i++)
	{
		ht[i].Erase();
	}
}

#endif