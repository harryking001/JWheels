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
    while(i!=1 && x>Heap[i/2])//�����ֵ�����丸���
	{
        Heap[i] = Heap[i/2];//�����ֵ�ŵ��ӽ��
		i = i/2;//����һ��
	}
    Heap[i] = x;
	return *this;

}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x)
{
    if(nCurrentSize == 0)
		throw OutOfBounds();
	//��С���ŵ�temp
	T temp = Heap[nCurrentSize];
	x = Heap[1];//�����ŵ�x
	nCurrentSize--;//�ܽ������1
	
	int i = 1;
	if(nCurrentSize==1)//ԭ����2�����������
	{
        Heap[1] = Heap[2];
	}
	while(i<=nCurrentSize/2)
	{
		if(2*i+1>nCurrentSize)//��2*i+1�������i�����Һ��ӽ�����������ܽ����
		{
            Heap[i] = Heap[2*i];//β���ŵ��丸���
	        Heap[2*i] = temp;
		    break;
		}
        if(Heap[2*i]>Heap[2*i+1])//i�������Ӵ����Һ���
		{
			if(Heap[2*i]>temp)//���Ӵ���β���
			{
                Heap[i] = Heap[2*i];//���ӷŵ��丸�׽��
    	        Heap[2*i] = temp;//β���ŵ�ԭ���ӽ��
			}
		    i=i*2;//�����ӽ��
	    }
	    else//i��������С�ڵ����Һ���
	    {
			if(Heap[2*i+1]>temp)//�Һ��Ӵ���β���
			{
                Heap[i] = Heap[2*i+1];//�Һ��ӷŵ��丸�׽��
		        Heap[2*i+1] = temp;//β���ŵ�ԭ�Һ��ӽ��
			}
		    i=i*2+1;//���Һ��ӽ��
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
	//��β���ĸ���㿪ʼ
	for(int i=nCurrentSize/2;i>=1;i--)
	{
        int c = i*2;//cΪβ����β�����ֵܽ��
		T y = Heap[i];
		while(c<=nCurrentSize)
		{
            if(c<nCurrentSize&&Heap[c]<Heap[c+1])//�ҳ���ĺ��ӣ�����Ÿ���c
				c++;
			if(Heap[c]<=y) break;
            Heap[c/2]=Heap[c];//�ϴ�ĺ��Ӵ����丸���Ļ����丳������
			c*=2;//����һ��
		}
		Heap[c/2] = y;
	}
}

#endif