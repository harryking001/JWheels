#ifndef SORT_H
#define SORT_H

#include "stdafx.h"
#include "LinearList.h"
#include <iostream>

class Sort
{
public:
	//�򵥱Ƚ�����

	//ð������
    static void BubbleSort(LinearList<int>* L);

	//ð������������
	static void BubbleSortPlus(LinearList<int>* L);
	
	//ѡ������
    static void SelectSort(LinearList<int>* L);

	//ֱ�Ӳ�������
    static void InsertSort(LinearList<int>* L);

	//ϣ������
    static void ShellSort(LinearList<int>* L);

	//�鲢����
    static void MergeSort(LinearList<int>* L);
	static void MSort(LinearList<int>* L, int Left, int Right, LinearList<int>* temp);
	static void Merge(LinearList<int>* L, int Left, int Mid, int Right, LinearList<int>* temp);
	//��������
	static void QuickSort(LinearList<int>* L);
	static void QSort(LinearList<int>* L, int i, int j);

};

#endif