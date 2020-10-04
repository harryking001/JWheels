#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

//���ѣ�������ֵʼ�մ����ӽ��
template<class T>
class MaxHeap
{
public:
	MaxHeap(int MaxSize = 10);
	MaxHeap(const MaxHeap<T>& h);
	~MaxHeap();
	int Length() const;
    MaxHeap<T>& Insert(const T& t);
	MaxHeap<T>& DeleteMax(T& t);
	void Initialize(T arr[], int nSize);
	void Output(ostream& out) const;
	void Erase();
private:
    T* heap;
	int length;
	int maxSize;
	bool copy;
};

template<class T>
MaxHeap<T>::MaxHeap(int MaxSize)
{
	maxSize = MaxSize;
	heap = NULL;
	length = 0;
	copy = false;
}

template<class T>
MaxHeap<T>::MaxHeap(const MaxHeap<T>& h)
{
	maxSize = h.maxSize;
	length = h.length;
	heap = new T[maxSize];
	for (int i = 0; i < maxSize; i++)
	{
		heap[i] = h.heap[i];
	}
	copy = true;
}

template<class T>
MaxHeap<T>::~MaxHeap()
{
	if (true == copy)
	{
        delete[] heap;
	}
	maxSize = 0;
	heap = NULL;
	length = 0;
	copy = false;
}

template<class T>
int MaxHeap<T>::Length() const
{
	return length;
}

//������½�㣬�����²㿪ʼ�������Լ��ĸ����Ƚϣ�������ڸ���㣬�򸸽������
template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& t)
{
    if(length == maxSize)
		throw NoMem();
	int i = ++length;//�������±�1��ʼ
    while(i != 1 && t > heap[i/2])//�����ֵ�����丸���
	{
        heap[i] = heap[i/2];//�����ֵ�ŵ��ӽ��
		i = i/2;//����һ��
	}
    heap[i] = t;
	return *this;

}

//������ɾ������㲢���������ֵ������������
template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& t)
{
    if(length == 0)
		throw OutOfBounds();
	//β���ŵ�tail
	T tail = heap[length];
	t = heap[1];//�����ŵ�x�����±�1��ʼ
	length--;//�ܽ������1
	
	int i = 1;
	if(length == 1)//ԭ����2�����������
	{
        heap[1] = heap[2];
	}
	//�Ӹ���㵽β���ĸ����
	while(i <= length / 2)
	{
		if(2 * i + 1 > length)//��i�����Һ��ӽ���������ܽ������˵��i���ֻ������
		{
			if (heap[2 * i] > tail)//i�������Ӵ���β���
			{
				heap[i] = heap[2 * i];//i�������ӷŵ�i
				heap[2 * i] = tail;//β���ŵ�i������
			}
		    break;
		}
        if(heap[2 * i] > heap[2 * i + 1])//i�������Ӵ����Һ���
		{
			if(heap[2 * i] > tail)//i�������Ӵ���β���
			{
                heap[i] = heap[2 * i];//i�������ӷŵ�i���
    	        heap[2 * i] = tail;//β���ŵ�i��������
			}
		    i = i * 2;//i�����ԭ���ӽ��
	    }
	    else//i��������С�ڵ����Һ���
	    {
			if(heap[2 * i + 1] >= tail)//i�����Һ��Ӵ���β���
			{
                heap[i] = heap[2 * i + 1];//i�����Һ��ӷŵ�i���
		        heap[2 * i + 1] = tail;//β���ŵ�i�����Һ���
			}
		    i = i * 2 + 1;//i�����ԭ�Һ��ӽ��
	    }
	
	}
	return *this;
}

//��������˳�����飬��������Ϊ����
template<class T>
void MaxHeap<T>::Initialize(T arr[], int nSize)
{
	if (true == copy)
	{
		delete[] heap;
	}
	heap = arr;
    length = nSize;
	//��β���ĸ���㿪ʼ
	for(int i = length / 2; i >= 1; i--)
	{
        int c = i * 2;//cΪβ����β�����ֵܽ��
		T father = heap[i];//��ȡ������ֵ
		while(c <= length)
		{
			if (c < length && heap[c] < heap[c + 1])//�ҳ���ĺ��ӣ�����Ÿ���c
			{
                c++;
			}   
			if (heap[c] <= father)
			{
                break;
			}	
            heap[c / 2] = heap[c];//�ϴ�ĺ��Ӵ����丸���Ļ����丳������
			c *= 2;//����һ��
		}
		heap[c / 2] = father;
	}
}

template<class T>
void MaxHeap<T>::Output(ostream& out) const
{
	for (int i = 0; i < length; i++)
	{
		out << heap[i] << " ";
	}
	out << endl;
}

template<class T>
void MaxHeap<T>::Erase()
{
	for (int i = 0; i < length; i++)
	{
		heap[i] = 0;
	}
	length = 0;
}

#endif