#ifndef SORTEDCHAIN_H
#define SORTEDCHAIN_H

#include "stdafx.h"
#include "Define.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

template<class K,class V>
class SortedChain;

//�������ڵ�,kΨһ
template<class K, class V>
class SortedChainNode
{
public:
    friend class SortedChain<K, V>;//ʹ���������Է��ʽڵ����ݳ�Ա
public :
	K key;//�ؼ���
    V value;//����
	SortedChainNode<K, V>* next;//ָ����һ���ڵ�
};

template<class K, class V>
class SortedChain
{
public:
	SortedChain();
	~SortedChain();
	bool IsEmpty() const;
	int Length() const;
	bool Search(const K& k, SortedChainNode<K, V>*& node) const;
	SortedChain<K, V>& Insert(const K& k, const V& v);
	SortedChain<K, V>& Delete(const K& k, V& v);
	void Output(ostream& out) const;
	void Erase();
private:
    SortedChainNode<K, V>* first;//����Ԫ���
};

template<class K, class V>
SortedChain<K, V>::SortedChain()
{
    first = NULL;
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
		else//ɾ����һ�����
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

//�������
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