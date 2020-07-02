#include "JSort.h"


//冒泡排序（升序）
void Sort::BubbleSort(LinearList<int>* L)
{
	int nLen = L->Length();
	for (int i = 0; i < nLen; i++)
	{
		for (int j = nLen - 1; j > i; j--)
		{
			if (L->Get(j - 1) > L->Get(j))
			{
				L->Swap(j - 1, j);
			}
		}
	}
}

//冒泡排序升级版（升序）
void Sort::BubbleSortPlus(LinearList<int>* L)
{
	int nLen = L->Length();
	bool flag = true;
	for (int i = 0; i < nLen && flag; i++)
	{
		flag = false;
		for (int j = nLen - 1; j > i; j--)
		{
			if (L->Get(j - 1) > L->Get(j))
			{
				L->Swap(j - 1, j);
				flag = true;
			}
		}
	}
}

//选择排序（升序）
void Sort::SelectSort(LinearList<int>* L)
{
	int nLen = L->Length();
	int nMin = 0;
	for (int i = 0; i < nLen - 1; i++)
	{
		nMin = i;//依次获取需要比较的待定数据序号
		for (int j = i + 1; j < nLen; j++)//依次将待定数据和它之后的所有数据进行比较
		{
			if (L->Get(nMin) > L->Get(j))//若发现比待定数据小的则两者交换，新数据成为待定数据
			{
				nMin = j;
			}
		}
		L->Swap(i, nMin);
	}
}

//直接插入排序（升序）
void Sort::InsertSort(LinearList<int>* L)
{
	int nLen = L->Length();
	for (int i = 1; i < nLen; i++)//需要插入的新数据序号
	{
		int j;
		int temp = L->Get(i);//把新数据放入临时变量
		for (j = i; j > 0; j--)
		{
			int a = L->Get(j - 1);
			if (temp < a)//新数据和已插入并排序好的旧数据依次比较
			{
				L->Put(j, a);//若新数据比旧数据小则将此旧数据向后移一位
			}
			else
			{
				break;
			}
		}
		L->Put(j, temp);//将新数据插入移位结束后的空余位
	}
}

//希尔排序（升序）
//首先设定一个间隔，一般为1/2或1/3数据长度
//将间隔数据分组，比如，数据为1,2,3,4,5,6,7,8,9，间隔为3，则1,4,7为一组，2,5,8为一组，3,6,9为一组
//每一组分别采用直接插入排序
//减小间隔长度，一般为原间隔的1/2，继续上述过程
void Sort::ShellSort(LinearList<int>* L)
{
	int nLen = L->Length();
	//逐步减小增量
	for (int gap = nLen / 2; gap > 0; gap /= 2)
	{
		for (int j = 0; j < gap; j++)
			for (int i = j + gap; i < nLen; i += gap)//将间隔数据分组
			{
				int k;
				int temp = L->Get(i);
				for (k = i; k > 0; k -= gap)//每组数据进行直接插入排序
				{
					int a = L->Get(k - gap);
					if (temp < a)
					{
						L->Put(k, a);
					}
					else
					{
						break;
					}
				}
				L->Put(k, temp);
			}
	}
}

/**
 * @brief 归并排序
 * @param L 待排序数据数组
 *
 * @return 无
 */

void Sort::MergeSort(LinearList<int>* L)
{
	int nLen = L->Length();
	int nLeft = 0;
	int nRight = nLen - 1;
	LinearList<int>* temp = new LinearList<int>(nLen);
	MSort(L, nLeft, nRight, temp);
}

/**
 * @brief 分成子序列排序
 * @param L 待排序数据数组
 * @param Left 待排序数据左下标
 * @param Right 待排序数据右下标
 * @param temp 排序后的数据数组
 *
 * @return 无
 */
void Sort::MSort(LinearList<int>* L, int Left, int Right, LinearList<int>* temp)
{
	if (Left < Right)
	{
		int nMid = (Left + Right) / 2;
		MSort(L, Left, nMid, temp);
		MSort(L, nMid + 1, Right, temp);
		Merge(L, Left, nMid, Right, temp);
	}
}

/**
 * @brief 归并
 * @param L 待排序数据数组
 * @param Left 待排序数据左下标
 * @param Mid 待排序数据中间下标
 * @param Right 待排序数据右下标
 * @param temp 排序后的数据数组
 *
 * @return 无
 */
void Sort::Merge(LinearList<int>* L, int Left, int Mid, int Right, LinearList<int>* temp)
{
	int i = Left;
	int j = Mid + 1;
	int k = 0;
	//由于左右两组数据都已排序，分别从左往右比较两个子序列的数据，较小的放入temp中
	while (i <= Mid && j <= Right)
	{
		if (L->Get(j) < L->Get(i))
		{
			temp->Put(k++, L->Get(j++));
		}
		else
		{
			temp->Put(k++, L->Get(i++));
		}
	}
	//没有放完的子序列继续放入temp中
	while (i <= Mid)
	{
		temp->Put(k++, L->Get(i++));
	}
	while (j <= Right)
	{
		temp->Put(k++, L->Get(j++));
	}
	k = 0;
	//排序完成后放入原数组
	while (Left <= Right)
	{
		L->Put(Left++, temp->Get(k++));
	}
}

//快速排序（升序）
void Sort::QuickSort(LinearList<int>* L)
{
	int i = 1;
	int j = L->Length() - 1;
	QSort(L, i, j);
}

void Sort::QSort(LinearList<int>* L, int i, int j)
{
	int left = i;//取左边第二个数为左哨兵
	int right = j;//取右边第一个数为右哨兵
	int key = i - 1;//取左边第一个数为基准值
	if (i > j)
		return;
	while (i < j)//左哨兵序号在右哨兵左边的情况下
	{
		while (L->Get(j) >= L->Get(key) && i < j)//右哨兵的值若大于等于基准值，哨兵向左移动
			j--;
		while (L->Get(i) <= L->Get(key) && i < j)//左哨兵的值若小于等于基准值，哨兵向右移动
			i++;
		if (i < j)//左哨兵序号在右哨兵左边的情况下交换两者的值
			L->Swap(i, j);
	}
	if (L->Get(key) > L->Get(i))//基准的值大于左右哨兵的值则交换两者的值
	{
		L->Swap(key, i);
	}
	else
	{
		i--;
	}
	QSort(L, left, i - 1);//基准值的左边重复以上过程
	QSort(L, i + 2, right);//基准值的右边重复以上过程
}
