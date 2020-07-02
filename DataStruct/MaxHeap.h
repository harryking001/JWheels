#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "stdafx.h"
#include "Exception.h"

template<class T>
class MaxHeap
{
public:
    MaxHeap(int MaxSize = 10)
	{
		nMaxSize = MaxSize;
        Heap = new T[MaxSize];
        nCurrentSize = 0;
	}
	~MaxHeap()
	{
        delete[] Heap;
	}
    MaxHeap<T>& Insert(const T& x);
	MaxHeap<T>& DeleteMax(T& x);
	void Initialize(T a[], int nSize);

private:
    T* Heap;
	int nCurrentSize, nMaxSize;
};

template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{
    if(nCurrentSize == nMaxSize)
		throw NoMem();
	int i = ++nCurrentSize;
    while(i!=1 && x>Heap[i/2])//插入的值大于其父结点
	{
        Heap[i] = Heap[i/2];//父结点值放到子结点
		i = i/2;//往上一层
	}
    Heap[i] = x;
	return *this;

}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x)
{
    if(nCurrentSize == 0)
		throw OutOfBounds();
	//最小结点放到temp
	T temp = Heap[nCurrentSize];
	x = Heap[1];//根结点放到x
	nCurrentSize--;//总结点数减1
	
	int i = 1;
	if(nCurrentSize==1)//原本有2个结点的情况下
	{
        Heap[1] = Heap[2];
	}
	while(i<=nCurrentSize/2)
	{
		if(2*i+1>nCurrentSize)//若2*i+1结点数（i结点的右孩子结点数）大于总结点数
		{
            Heap[i] = Heap[2*i];//尾结点放到其父结点
	        Heap[2*i] = temp;
		    break;
		}
        if(Heap[2*i]>Heap[2*i+1])//i结点的左孩子大于右孩子
		{
			if(Heap[2*i]>temp)//左孩子大于尾结点
			{
                Heap[i] = Heap[2*i];//左孩子放到其父亲结点
    	        Heap[2*i] = temp;//尾结点放到原左孩子结点
			}
		    i=i*2;//到左孩子结点
	    }
	    else//i结点的左孩子小于等于右孩子
	    {
			if(Heap[2*i+1]>temp)//右孩子大于尾结点
			{
                Heap[i] = Heap[2*i+1];//右孩子放到其父亲结点
		        Heap[2*i+1] = temp;//尾结点放到原右孩子结点
			}
		    i=i*2+1;//到右孩子结点
	    }
	
	}
	return *this;
}

template<class T>
void MaxHeap<T>::Initialize(T a[], int nSize)
{
    delete[] Heap;
	Heap = a;
    nCurrentSize = nSize;
	//从尾结点的父结点开始
	for(int i=nCurrentSize/2;i>=1;i--)
	{
        int c = i*2;//c为尾结点或尾结点的兄弟结点
		T y = Heap[i];
		while(c<=nCurrentSize)
		{
            if(c<nCurrentSize&&Heap[c]<Heap[c+1])//找出大的孩子，把序号赋给c
				c++;
			if(Heap[c]<=y) break;
            Heap[c/2]=Heap[c];//较大的孩子大于其父结点的话将其赋给父亲
			c*=2;//下移一层
		}
		Heap[c/2] = y;
	}
}

#endif