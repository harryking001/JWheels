#ifndef SORT_H
#define SORT_H

#include "stdafx.h"
#include "LinearList.h"
#include <iostream>

class Sort
{
public:
	//ºÚµ•±»Ωœ≈≈–Ú

	//√∞≈›≈≈–Ú
    static void BubbleSort(LinearList<int>* L);

	//√∞≈›≈≈–Ú…˝º∂∞Ê
	static void BubbleSortPlus(LinearList<int>* L);
	
	//—°‘Ò≈≈–Ú
    static void SelectSort(LinearList<int>* L);

	//÷±Ω”≤Â»Î≈≈–Ú
    static void InsertSort(LinearList<int>* L);

	//œ£∂˚≈≈–Ú
    static void ShellSort(LinearList<int>* L);

	//πÈ≤¢≈≈–Ú
    static void MergeSort(LinearList<int>* L);
	static void MSort(LinearList<int>* L, int Left, int Right, LinearList<int>* temp);
	static void Merge(LinearList<int>* L, int Left, int Mid, int Right, LinearList<int>* temp);
	//øÏÀŸ≈≈–Ú
	static void QuickSort(LinearList<int>* L);
	static void QSort(LinearList<int>* L, int i, int j);

};

#endif