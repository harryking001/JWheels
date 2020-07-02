#include "stdafx.h"
#include "MaxHeap.h"
#include <iostream>
using namespace std;
void main(void)
{
	int a[5] = {0,88,43,67,48};
	MaxHeap<int> mh(20);
    mh.Initialize (a,4);
	int i = 4;
	cout<<"Sort Result: ";
	while(i>0)
	{
        int e = 0;
		mh.DeleteMax(e);
        cout<<e;
		if(i!=1)
		{
			cout<<", ";
		}
		i--;
	}
	system("pause");
}