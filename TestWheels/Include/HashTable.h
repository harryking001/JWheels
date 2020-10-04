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
	friend class HashTable<K, V>;//ʹ���������Է��ʽڵ����ݳ�Ա
private:
	K key;//�ؼ���
	V value;//����
};

//��ֵkΨһ
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
    int D;//��ϣ���С
	HashNode<K, V>* ht;
	bool* empty;//bool���飬��Ӧ��ϣ����ÿ��Ԫ�أ�����Ԫ���Ƿ�Ϊ��
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

//ֻҪempty������һ����Ϊ�գ���ϣ��Ͳ�Ϊ��
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

//���������ϣ���в�Ϊ��Ԫ�ظ���
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
		//���Ŷ�ַ�������ֵ��ͻ�������ֵk�͹�ϣ��Ԫ�صļ�ֵ����Ҹ�Ԫ�ز�Ϊ�����ҵ���Ԫ��
		//�������ȣ����±�����ƶ�����Ѱ��
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
		//���Ŷ�ַ�������ֵ��ͻ�������ֵk����Ӧ��λ�ò�Ϊ�գ����±����ֱ���пյ�λ��
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
		//���Ŷ�ַ���������ֵk����Ӧ��λ��Ԫ���еļ�ֵ��k����Ȼ�Ϊ�գ����±����ֱ���ҵ���ӦԪ��
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

//��ϣ�����������ֵk�͹�ϣ���±�Ĺ�ϵΪi = k%D
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