#ifndef CHAINHASHTABLE_H
#define CHAINHASHTABLE_H
#include "stdafx.h"
#include "SortedChain.h"
#include "Define.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

//键值k唯一
template<class K, class V>
class ChainHashTable
{
public:
	ChainHashTable(int divisor = 11);
	ChainHashTable(const ChainHashTable<K, V>& h);
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
	SortedChain<K, V>* sc;//有序链表数组，每个数组元素为一条有序链表
	int hashFunc(const K& k)const;//散列（映射）函数
};

template<class K, class V>
ChainHashTable<K, V>::ChainHashTable(int divisor)
{
	D = divisor;
	sc = new SortedChain<K, V>[D];
}

template<class K, class V>
ChainHashTable<K, V>::ChainHashTable(const ChainHashTable<K, V>& h)
{
	D = h.D;
	sc = new SortedChain<K, V>[D];
	for (int i = 0; i < D; i++)
	{
		SortedChainNode<K, V>* pCur = h.sc[i].GetFirst();
		SortedChainNode<K, V>* pPre = new SortedChainNode<K, V>();
		if (pCur)
		{
			*pPre = *pCur;
			sc[i].SetFirst(pPre);
			pCur = pCur->next;
		}
		else
		{
			delete pPre;
			pPre = NULL;
		}
		while (pCur)
		{
			SortedChainNode<K, V>* pNode = new SortedChainNode<K, V>();
			*pNode = *pCur;
			pPre->next = pNode;
			pPre = pNode;
			pCur = pCur->next;
		}
		if (pPre)
		{
			pPre->next = NULL;
		}
	}
}

template<class K, class V>
ChainHashTable<K, V>::~ChainHashTable()
{
	D = 0;
    delete[] sc;
	sc = NULL;
}

//只要empty数组有一个不为空，哈希表就不为空
template<class K, class V>
bool ChainHashTable<K, V>::IsEmpty() const
{
	for (int i = 0; i < D; i++)
	{
		if (sc[i].IsEmpty() == false)
		{
			return false;
		}
	}
	return true;
}

//遍历计算哈希表中不为空元素个数
template<class K, class V>
int ChainHashTable<K, V>::Length() const
{
	int length = 0;
	for (int i = 0; i < D; i++)
	{
		length += sc[i].Length();
	}
	return length;
}

template<class K, class V>
bool ChainHashTable<K, V>::Find(const K& k, V& v) const
{
	int i = hashFunc(k);
	SortedChainNode<K,V>* node = NULL;
	//链地址法解决键值冲突，通过键值k找到有序链表数组中对应链表，然后在该链表中通过k找到元素
    bool bRet = sc[i].Search(k, node);
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
    sc[i].Insert(k,v);
	return *this;
}

template<class K, class V>
ChainHashTable<K, V>& ChainHashTable<K, V>::Delete(const K& k,V& v)
{
	int i = hashFunc(k);
    sc[i].Delete(k,v);
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
		sc[i].Output(out);
	}
}

template<class K, class V>
void ChainHashTable<K, V>::Erase()
{
	for (int i = 0; i < D; i++)
	{
		sc[i].Erase();
	}
}

#endif