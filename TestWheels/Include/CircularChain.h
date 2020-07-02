#ifndef CIRCULARCHAIN_H
#define CIRCULARCHAIN_H
#include "stdafx.h"
#include "Exception.h"

template <class T>
class CircularChain;

template <class T>
class CircularChainNode
{
public:
	friend class CircularChain<T>;
private:
	T data;
	CircularChainNode<T>* next;
};

//ѭ������
template <class T>
class CircularChain
{
public:
	CircularChain();
	~CircularChain();
public:
	bool IsEmpty() const;
	int Length() const;
	bool Find(const int k, T& t) const;
	bool Search(const T& t, CircularChainNode<T>*& node) const;
	CircularChain<T>& Push_back(const T& t);
	CircularChain<T>& Insert(const int k, const T& t);
	CircularChain<T>& Delete(const int k, T& t);
	CircularChain<T>& Swap(const int i, const int j);
	void Output(ostream& out) const;
	void Erase();
private:
	CircularChainNode<T>* first;//��Ԫͷ��㣬������
	int length;
};

template<class T>
CircularChain<T>::CircularChain()
{
	first = new CircularChainNode<T>();
	first->next = first;
	length = 0;
}

template<class T>
CircularChain<T>::~CircularChain()
{
	Erase();
	delete first;
	first = NULL;
}

template<class T>
bool CircularChain<T>::IsEmpty() const
{
	return length == 0;
}

template<class T>
int CircularChain<T>::Length() const
{
	return length;
}

template<class T>
bool CircularChain<T>::Find(const int k, T& t) const
{
	//��λ��1��ʼ
	if (k < 1 || k > length || first->next == first)
		return false;
	CircularChainNode<T>* pCur = first->next;
	for(int i = 1;i < k;i++)
	{
		pCur = pCur->next;
	}
	t = pCur->data;
	return true;
}

template<class T>
bool CircularChain<T>::Search(const T& t, CircularChainNode<T>*& node) const
{
	if (first->next == first)
		return false;
	CircularChainNode<T>* pCur = first->next;
	int index = 1;
	while (pCur != first)
	{
		if (pCur->data == t)
		{
			node = pCur;
			return true;
		}	
		pCur = pCur->next;
		index++;
	}
	return false;
}

template<class T>
CircularChain<T>& CircularChain<T>::Push_back(const T& t)
{
	CircularChainNode<T>* pCur = first->next;
	CircularChainNode<T>* pLast = pCur;
	CircularChainNode<T>* pNew = new CircularChainNode<T>();
	pNew->data = t;
	pNew->next = first;
	if (pCur == first)
	{
        first->next = pNew;
		pNew->next = first;
	}
	while (pCur != first)
	{
		pLast = pCur;
		pCur = pCur->next;
	}
	pLast->next = pNew;
	length++;
	return *this;
}

//�ڵ�k��Ԫ�ص�λ�ò���t��ԭԪ�غ���
template<class T>
CircularChain<T>& CircularChain<T>::Insert(const int k, const T& t)
{
	//��λ��1��ʼ
	if (k < 1 || k > length + 1)
		throw OutOfBounds();
	CircularChainNode<T>* pPrev = first->next;
	for (int i = 1; i < k - 1; i++)
	{
		pPrev = pPrev->next;
	}
	CircularChainNode<T>* pCur = new CircularChainNode<T>();
	pCur->data = t;
	if (k == 1)
	{
		pCur->next = first->next;
		first->next = pCur;
	}
	else
	{
        pCur->next = pPrev->next;
	    pPrev->next = pCur;
	}
	length++;
	return *this;
}
template<class T>
CircularChain<T>& CircularChain<T>::Delete(const int k, T& t)
{
	//��λ��1��ʼ
	if (k < 1 || k > length)
		throw OutOfBounds();
	if (first->next == first)
	    throw BadCall();
	CircularChainNode<T>* pPrev = first->next;
    for (int i = 1; i < k - 1; i++)
	{
		pPrev = pPrev->next;
	}
    CircularChainNode<T>* pCur = pPrev->next;
	if (k == 1)
	{
		t = pPrev->data;
		first->next = pPrev->next;
		delete pPrev;
	}
	else
	{
		t = pCur->data;
        pPrev->next = pCur->next;
	    delete pCur;
	}
	length--;
	return *this;
}

template<class T>
CircularChain<T>& CircularChain<T>::Swap(const int i, const int j)
{
	
}

template<class T>
void CircularChain<T>::Output(ostream& out) const
{
	CircularChainNode<T>* pCur = first->next;
	while (pCur != first)
	{
		out << pCur->data << " ";
		pCur = pCur->next;
	}
	out << endl;
}

//�������
template<class T>
void CircularChain<T>::Erase()
{
	CircularChainNode<T>* pTemp = NULL;
	CircularChainNode<T>* pCur = first->next;
	while (pCur != first)
	{
		pTemp = pCur;
        pCur = pCur->next;
        delete pTemp;
	}
	first->next = first;
	length = 0;
}

#endif

