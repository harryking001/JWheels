#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

template <class K, class V>
class HashTable;

template<class K, class V>
class HashNode
{
public:
	friend class HashTable<K, V>;//使有序链可以访问节点数据成员
private:
	K key;//关键字
	V value;//数据
};

//键值k唯一
template<class K, class V>
class HashTable
{
public:
    HashTable(int divisor = 11);
	HashTable(const HashTable<K, V>& h);
	~HashTable();
	bool IsEmpty() const;
	int Length() const;
	bool Find(const K& k, V& v) const;
	HashTable<K, V>& Insert(const K& k, const V& v);
	HashTable<K, V>& Delete(const K& k, V& v);
	void Output(ostream& out) const;
	void Erase();
private:
    int D;//哈希表大小
	HashNode<K, V>* ht;
	bool* empty;//bool数组，对应哈希表中每个元素，表面元素是否为空
	int hashFunc(const K& k)const;
};

template<class K, class V>
HashTable<K,V>::HashTable(int divisor)
{
    D = divisor;
    ht = new HashNode<K, V>[D];
	empty = new bool[D];
	for(int i = 0;i < D;i++)
		empty[i] = true;
}

template<class K, class V>
HashTable<K, V>::HashTable(const HashTable<K, V>& h)
{
	D = h.D;
	ht = new HashNode<K, V>[D];
	empty = new bool[D];
	for (int i = 0; i < D; i++)
	{
		ht[i] = h.ht[i];
	}
	for (int i = 0; i < D; i++)
	{
		empty[i] = h.empty[i];
	}
}

template<class K, class V>
HashTable<K, V>::~HashTable()
{
	D = 0;
	delete[] ht;
	delete[] empty;
	ht = NULL;
	empty = NULL;
}

//只要empty数组有一个不为空，哈希表就不为空
template<class K, class V>
bool HashTable<K, V>::IsEmpty() const
{
	for (int i = 0; i < D; i++)
	{
		if (empty[i] == false)
		{
			return false;
		}
	}
	return true;
}

//遍历计算哈希表中不为空元素个数
template<class K, class V>
int HashTable<K, V>::Length() const
{
	int length = 0;
	for (int i = 0; i < D; i++)
	{
		if (empty[i] == false)
		{
			length++;
		}
	}
	return length;
}

template<class K, class V>
bool HashTable<K, V>::Find(const K& k, V& v) const
{
	int i = hashFunc(k);
	int j = i;
	do
	{
		//开放定址法解决键值冲突，如果键值k和哈希表元素的键值相等且该元素不为空则找到该元素
		//如果不相等，则下标向后移动继续寻找
		if (ht[j].key == k && empty[j] == false)
		{
			v = ht[j].value;
            return true;
		}
		j = ++j%D;
	} while (i != j);
	return false;
}

template<class K, class V>
HashTable<K, V>& HashTable<K, V>::Insert(const K& k, const V& v)
{
	int i = hashFunc(k);
	int j = i;
	do
	{
		//开放定址法解决键值冲突，如果键值k所对应的位置不为空，则下标后移直到有空的位置
		if (empty[j] == true)
		{
            ht[j].value = v;
			ht[j].key = k;
			empty[j] = false;
			return *this;
		}
		j = ++j%D;
	} while (i != j);
	throw BadCall();
}

template<class K, class V>
HashTable<K, V>& HashTable<K, V>::Delete(const K& k, V& v)
{
	int i = hashFunc(k);
	int j = i;
	do
	{
		//开放定址法，如果键值k所对应的位置元素中的键值和k不相等或为空，则下标后移直到找到相应元素
		if (empty[j] == false && ht[j].key == k)
		{
			v = ht[j].value;
			empty[j] = true;
			return *this;
		}
		j = ++j%D;
	} while (i != j);
	throw BadCall();
}

//哈希函数，这里键值k和哈希表下标的关系为i = k%D
template<class K, class V>
int HashTable<K, V>::hashFunc(const K & k) const
{
	return k%D;
}

template<class K, class V>
void HashTable<K, V>::Output(ostream& out) const
{
	for (int i = 0; i < D; i++)
	{
		if (empty[i] == false)
		{
            out << ht[i].value << " ";
		}
	}
	out << endl;
}

template<class K, class V>
void HashTable<K, V>::Erase()
{
	for (int i = 0; i < D; i++)
	{
		empty[i] = true;
	}
}


#endif