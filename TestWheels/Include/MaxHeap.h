#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

//最大堆，父结点的值始终大于子结点
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

//插入的新结点，从最下层开始，逐层和自己的父结点比较，如果大于父结点，则父结点下移
template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& t)
{
    if(length == maxSize)
		throw NoMem();
	int i = ++length;//从数组下标1开始
    while(i != 1 && t > heap[i/2])//插入的值大于其父结点
	{
        heap[i] = heap[i/2];//父结点值放到子结点
		i = i/2;//往上一层
	}
    heap[i] = t;
	return *this;

}

//从最大堆删除最大结点并返回最大结点值，可用于排序
template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& t)
{
    if(length == 0)
		throw OutOfBounds();
	//尾结点放到tail
	T tail = heap[length];
	t = heap[1];//根结点放到x，从下标1开始
	length--;//总结点数减1
	
	int i = 1;
	if(length == 1)//原本有2个结点的情况下
	{
        heap[1] = heap[2];
	}
	//从根结点到尾结点的父结点
	while(i <= length / 2)
	{
		if(2 * i + 1 > length)//若i结点的右孩子结点数大于总结点数，说明i结点只有左孩子
		{
			if (heap[2 * i] > tail)//i结点的左孩子大于尾结点
			{
				heap[i] = heap[2 * i];//i结点的左孩子放到i
				heap[2 * i] = tail;//尾结点放到i的左孩子
			}
		    break;
		}
        if(heap[2 * i] > heap[2 * i + 1])//i结点的左孩子大于右孩子
		{
			if(heap[2 * i] > tail)//i结点的左孩子大于尾结点
			{
                heap[i] = heap[2 * i];//i结点的左孩子放到i结点
    	        heap[2 * i] = tail;//尾结点放到i结点的左孩子
			}
		    i = i * 2;//i结点变成原左孩子结点
	    }
	    else//i结点的左孩子小于等于右孩子
	    {
			if(heap[2 * i + 1] >= tail)//i结点的右孩子大于尾结点
			{
                heap[i] = heap[2 * i + 1];//i结点的右孩子放到i结点
		        heap[2 * i + 1] = tail;//尾结点放到i结点的右孩子
			}
		    i = i * 2 + 1;//i结点变成原右孩子结点
	    }
	
	}
	return *this;
}

//输入任意顺序数组，将其生成为最大堆
template<class T>
void MaxHeap<T>::Initialize(T arr[], int nSize)
{
	if (true == copy)
	{
		delete[] heap;
	}
	heap = arr;
    length = nSize;
	//从尾结点的父结点开始
	for(int i = length / 2; i >= 1; i--)
	{
        int c = i * 2;//c为尾结点或尾结点的兄弟结点
		T father = heap[i];//获取父结点的值
		while(c <= length)
		{
			if (c < length && heap[c] < heap[c + 1])//找出大的孩子，把序号赋给c
			{
                c++;
			}   
			if (heap[c] <= father)
			{
                break;
			}	
            heap[c / 2] = heap[c];//较大的孩子大于其父结点的话将其赋给父亲
			c *= 2;//下移一层
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