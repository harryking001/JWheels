#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>
#include "time.h"

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
	SkipList(int MaxLevel = 100, int TailKey = 100);
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
	int maxLevel;//最大级数
	int level;//级数
	float P;//概率
	int tailKey;//队尾键值极大
	SkipNode<K, V>* head;//头结点
	SkipNode<K, V>* tail;//尾结点
	SkipNode<K, V>** last;//存放目标结点每一级的前一个结点指针
};

template<class K, class V>
SkipList<K, V>::SkipList(int MaxLevel, int TailKey)
{
	srand((int)time(0));//利用时间产生随机种子
	maxLevel = MaxLevel;
	level = 0;
	P = 0.5;
	tailKey = TailKey;
	head = new SkipNode<K, V>(MaxLevel+1);//级数从0开始
	tail = new SkipNode<K, V>(0);
    tail->key = tailKey;
	last = new SkipNode<K,V>*[MaxLevel+1];

	for (int i = 0; i <= maxLevel; i++)//初始情况下头结点每一级的下一个结点都为尾结点
		head->link[i] = tail;
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

//头尾除外
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
	//从最上级开始逐级往下找到目标结点的在0级的上一个结点pCur，并且将每一级目标结点的上一个结点的地址存放到last数组
	for (int i = level; i >= 0; i--)
	{
		while (pCur->link[i]->key < k)
			pCur = pCur->link[i];
		last[i] = pCur;
	}
	if (pCur->link[0]->key == k)//是否找到
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
	int lev = Level();//随机获取级数
	if (lev > level)//如果比现有级数大，最多只能大一级
	{
		lev = ++level;
		last[lev] = head;//产生新级数的插入结点的上一个结点为头结点
	}
	pCur = new SkipNode<K, V>(maxLevel + 1);
	pCur->key = k;
	pCur->value = v;
	for (int i = 0; i <= level; i++)//逐级插入结点
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
	for (int i = 0; i <= level && last[i]->link[i] == pCur; i++)//逐级删除结点
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

//保留head和tail，删除其他节点
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
