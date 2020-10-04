#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>
#include "time.h"

using std::ostream;
using std::endl;

template <class K, class V>
class SkipList;

template<class K, class V>
class SkipNode
{
public:
    friend class SkipList<K, V>;
public:
	SkipNode(int size) { link = new SkipNode<K, V>*[size]; }
	~SkipNode() { delete[] link; }
private:
	K key;
	V value;
	SkipNode<K, V>** link;
};

template<class K, class V>
class SkipList
{
public:
	SkipList(int MaxLevel = 20, int TailKey = 100);
	SkipList(const SkipList<K, V>& sl);
	~SkipList();
	bool IsEmpty() const;
	int Length() const;
	bool Search(const K& k, SkipNode<K, V>*& node) const;
	SkipList<K, V>& Insert(const K& k, const V& v);
	SkipList<K, V>& Delete(const K& k, V& v);
	void Output(ostream& out) const;
	void Erase();
private:
	int Level();
	int maxLevel;//�����
	int level;//����
	float P;//����
	int tailKey;//��β��ֵ����
	SkipNode<K, V>* head;//ͷ���
	SkipNode<K, V>* tail;//β���
	SkipNode<K, V>** last;//��Ų��ҵ�Ŀ����ÿһ����ǰһ�����ָ��
};

template<class K, class V>
SkipList<K, V>::SkipList(int MaxLevel, int TailKey)
{
	srand((int)time(0));//����ʱ������������
	maxLevel = MaxLevel;
	level = 0;
	P = 0.5;
	tailKey = TailKey;
	head = new SkipNode<K, V>(maxLevel +1);//������0��ʼ
	tail = new SkipNode<K, V>(0);
    tail->key = tailKey;
	last = new SkipNode<K,V>*[maxLevel +1];//ÿһ������һ��ָ�룬ָ��ÿһ�����ҵ��Ľ���ǰһ�����

	for (int i = 0; i <= maxLevel; i++)//��ʼ�����ͷ���ÿһ������һ����㶼Ϊβ���
		head->link[i] = tail;
}

template<class K, class V>
SkipList<K, V>::SkipList(const SkipList<K, V>& sl)
{
	maxLevel = sl.maxLevel;
	level = sl.level;
	P = sl.P;
	tailKey = sl.tailKey;
	head = new SkipNode<K, V>(maxLevel + 1);
	tail = new SkipNode<K, V>(0);
	tail->key = tailKey;
	last = new SkipNode<K, V> * [maxLevel + 1];
	
	SkipNode<K, V>* curNode_copy = sl.head;
	SkipNode<K, V>* curNode = head;
    while (curNode_copy->link[0] != sl.tail)
    {
    	SkipNode<K, V>* tempNode = new SkipNode<K, V>(maxLevel + 1);
		tempNode->key = curNode_copy->link[0]->key;
		tempNode->value = curNode_copy->link[0]->value;
		curNode->link[0] = tempNode;
		curNode = tempNode;
		curNode_copy = curNode_copy->link[0];
    }
	curNode->link[0] = tail;

	for (int i = 1; i < level; i++)
	{
		curNode_copy = sl.head;
		curNode = head;
		while (curNode_copy->link[i] != sl.tail)
		{
			//TODO
		}
	}

}

template<class K, class V>
SkipList<K, V>::~SkipList()
{
	SkipNode<K, V>* pCur = head;
	while (pCur != tail)
	{
		head = head->link[0];
		delete pCur;
		pCur = head;
	}
	delete tail;
	delete[] last;
}

template<class K, class V>
bool SkipList<K, V>::IsEmpty() const
{
	return head->link[0] == tail?true:false;
}

//ͷβ����
template<class K, class V>
int SkipList<K, V>::Length() const
{
	int length = 0;
	SkipNode<K, V>* pCur = head->link[0];
	while (pCur != tail)
	{
        pCur = pCur->link[0];
		length++;
	}
	return length;
}

template<class K, class V>
bool SkipList<K, V>::Search(const K& k, SkipNode<K, V>*& node) const
{
	SkipNode<K, V>* pCur = head;
	//�����ϼ���ʼ�������ҵ�Ŀ�������0������һ�����pCur�����ҽ�ÿһ��Ŀ�������һ�����ĵ�ַ��ŵ�last����
	for (int i = level; i >= 0; i--)
	{
		while (pCur->link[i]->key < k)
			pCur = pCur->link[i];
		last[i] = pCur;
	}
	if (pCur->link[0]->key == k)//�Ƿ��ҵ�
	{
		node = pCur->link[0];
        return true;
	}	
	else
		return false;
}

template<class K, class V>
SkipList<K, V>& SkipList<K, V>::Insert(const K& k, const V & v)
{
	SkipNode<K, V>* pCur = NULL;
	bool bRet = Search(k, pCur);
	if (bRet)
		throw BadInput();
	int lev = Level();//�����ȡ����
	if (lev > level)//��������м��������ֻ�ܴ�һ��
	{
		lev = ++level;
		last[lev] = head;//�����¼����Ĳ��������һ�����Ϊͷ���
	}
	pCur = new SkipNode<K, V>(maxLevel + 1);
	pCur->key = k;
	pCur->value = v;
	for (int i = 0; i <= level; i++)//�𼶲�����
	{
		pCur->link[i] = last[i]->link[i];
		last[i]->link[i] = pCur;
	}
	return *this;
}

template<class K, class V>
SkipList<K, V>& SkipList<K, V>::Delete(const K& k, V & v)
{
	SkipNode<K, V>* pCur = NULL;
	bool bRet = Search(k, pCur);
	if (!bRet)
		throw BadInput();
	for (int i = 0; i <= level && last[i]->link[i] == pCur; i++)//��ɾ�����
	{
		last[i]->link[i] = pCur->link[i];
	}
	v = pCur->value;
	delete pCur;
	return *this;
}

template<class K, class V>
void SkipList<K, V>::Output(ostream& out) const
{
	SkipNode<K, V>* pCur = head->link[0];
	while (pCur != tail)
	{
		out << pCur->value << " ";
		pCur = pCur->link[0];
	}
	out << endl;
}

//����head��tail��ɾ�������ڵ�
template<class K, class V>
void SkipList<K, V>::Erase()
{
	SkipNode<K, V>* pCur = head->link[0];
	SkipNode<K, V>* pTemp = pCur;
	while (pCur != tail)
	{
	    pTemp = pCur->link[0];
		delete pCur;
		pCur = pTemp;
	}
	for (int i = 0; i <= maxLevel; i++)
		head->link[i] = tail;
	level = 0;
}

template<class K, class V>
int SkipList<K, V>::Level()
{
	int lev = 0;
	int cutOff = P * maxLevel;
	while (rand()% maxLevel <= cutOff)
		lev++;
	return (lev <= maxLevel) ? lev : maxLevel;
}

#endif
