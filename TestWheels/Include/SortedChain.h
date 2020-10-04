#ifndef SORTEDCHAIN_H
#define SORTEDCHAIN_H

#include "stdafx.h"
#include "Define.h"
#include "Exception.h"
#include <iostream>
#include "ChainHashTable.h"

using std::ostream;
using std::endl;

template<class K,class V>
class SortedChain;

//有序链节点,k唯一
template<class K, class V>
class SortedChainNode
{
public:
    friend class SortedChain<K, V>;//使有序链可以访问节点数据成员
public :
	K key;//关键字
    V value;//数据
	SortedChainNode<K, V>* next;//指向下一个节点
};

template<class K, class V>
class SortedChain
{
public:
	SortedChain();
	SortedChain(const SortedChain<K, V>& c);
	~SortedChain();
	bool IsEmpty() const;
	int Length() const;
	SortedChainNode<K, V>* GetFirst() const;
	void SetFirst(SortedChainNode<K, V>* f);
	bool Search(const K& k, SortedChainNode<K, V>*& node) const;
	SortedChain<K, V>& Insert(const K& k, const V& v);
	SortedChain<K, V>& Delete(const K& k, V& v);
	void Output(ostream& out) const;
	void Erase();
private:
    SortedChainNode<K, V>* first;//非哑元结点
};

template<class K, class V>
SortedChain<K, V>::SortedChain()
{
    first = NULL;
}

template<class K, class V>
SortedChain<K, V>::SortedChain(const SortedChain<K, V>& c)
{
	SortedChainNode<K, V>* pCur = c.first;
	SortedChainNode<K, V>* pPre = new SortedChainNode<K, V>();
	if (pCur)
	{
		*pPre = *pCur;
		first = pPre;
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

template<class K, class V>
SortedChain<K, V>::~SortedChain()
{
	Erase();
}

template<class K, class V>
bool SortedChain<K, V>::IsEmpty() const
{
    return first == NULL;
}

template<class K, class V>
int SortedChain<K, V>::Length() const
{
    int length = 0;
	SortedChainNode<K, V>* pCur = first;
    while(pCur)
	{
		pCur = pCur->next ;
		length++;
	}
	return length;
}

template<class K, class V>
SortedChainNode<K, V>* SortedChain<K, V>::GetFirst() const
{
	return first;
}

template<class K, class V>
void SortedChain<K, V>::SetFirst(SortedChainNode<K, V>* f)
{
	first = f;
}

//有序链表的查找还是需要一个个找
template<class K, class V>
bool SortedChain<K, V>::Search(const K& k, SortedChainNode<K, V>*& node) const
{
    SortedChainNode<K,V>* pCur = first;
	for (; pCur && pCur->key < k; pCur = pCur->next);
    if(pCur && pCur->key == k)
	{
		node = pCur;
		return true;
	}
	return false;
}

template<class K, class V>
SortedChain<K, V>& SortedChain<K, V>::Insert(const K& k,const V& v)
{
    SortedChainNode<K,V>* pNext = first, *pPrev = NULL;
	for (; pNext && pNext->key < k; pPrev = pNext, pNext = pNext->next);
	if (pNext && pNext->value == v)
		throw BadInput();
    SortedChainNode<K,V>* pCur = new SortedChainNode<K,V>();
	pCur->key = k;
	pCur->value = v;
	pCur->next = pNext;
	
	if(pPrev)
	{
	    pPrev->next = pCur;
	}
	else
	{
        first = pCur;
	}
	return *this;
}

template<class K, class V>
SortedChain<K, V>& SortedChain<K, V>::Delete(const K& k, V& v)
{
    SortedChainNode<K,V>* pNext = first, *pPrev = NULL;
	for (; pNext && pNext->key < k; pPrev = pNext, pNext = pNext->next);
    if(pNext && pNext->key == k)
	{
		if (pPrev != NULL)
		{
            pPrev->next = pNext->next;
		}
		else//删除第一个结点
		{
			first = first->next;
		}
		v = pNext->value;
		delete pNext;
	}
	else
	{
        throw BadInput();
	}
	return *this; 
}

template<class K, class V>
void SortedChain<K, V>::Output(ostream& out) const
{
	SortedChainNode<K, V>* pCur = first;
	while (pCur)
	{
		out << pCur->value << " ";
		pCur = pCur->next;
	}
	out << endl;
}

//清空链表
template<class K, class V>
void SortedChain<K, V>::Erase()
{
	SortedChainNode<K, V>* pCur = NULL;
	while (first)
	{
		pCur = first->next;
		delete first;
		first = pCur;
	}
}

#endif