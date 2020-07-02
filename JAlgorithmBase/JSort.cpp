#include "JSort.h"


//ð����������
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

//ð�����������棨����
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

//ѡ����������
void Sort::SelectSort(LinearList<int>* L)
{
	int nLen = L->Length();
	int nMin = 0;
	for (int i = 0; i < nLen - 1; i++)
	{
		nMin = i;//���λ�ȡ��Ҫ�ȽϵĴ����������
		for (int j = i + 1; j < nLen; j++)//���ν��������ݺ���֮����������ݽ��бȽ�
		{
			if (L->Get(nMin) > L->Get(j))//�����ֱȴ�������С�������߽����������ݳ�Ϊ��������
			{
				nMin = j;
			}
		}
		L->Swap(i, nMin);
	}
}

//ֱ�Ӳ�����������
void Sort::InsertSort(LinearList<int>* L)
{
	int nLen = L->Length();
	for (int i = 1; i < nLen; i++)//��Ҫ��������������
	{
		int j;
		int temp = L->Get(i);//�������ݷ�����ʱ����
		for (j = i; j > 0; j--)
		{
			int a = L->Get(j - 1);
			if (temp < a)//�����ݺ��Ѳ��벢����õľ��������αȽ�
			{
				L->Put(j, a);//�������ݱȾ�����С�򽫴˾����������һλ
			}
			else
			{
				break;
			}
		}
		L->Put(j, temp);//�������ݲ�����λ������Ŀ���λ
	}
}

//ϣ����������
//�����趨һ�������һ��Ϊ1/2��1/3���ݳ���
//��������ݷ��飬���磬����Ϊ1,2,3,4,5,6,7,8,9�����Ϊ3����1,4,7Ϊһ�飬2,5,8Ϊһ�飬3,6,9Ϊһ��
//ÿһ��ֱ����ֱ�Ӳ�������
//��С������ȣ�һ��Ϊԭ�����1/2��������������
void Sort::ShellSort(LinearList<int>* L)
{
	int nLen = L->Length();
	//�𲽼�С����
	for (int gap = nLen / 2; gap > 0; gap /= 2)
	{
		for (int j = 0; j < gap; j++)
			for (int i = j + gap; i < nLen; i += gap)//��������ݷ���
			{
				int k;
				int temp = L->Get(i);
				for (k = i; k > 0; k -= gap)//ÿ�����ݽ���ֱ�Ӳ�������
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
 * @brief �鲢����
 * @param L ��������������
 *
 * @return ��
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
 * @brief �ֳ�����������
 * @param L ��������������
 * @param Left �������������±�
 * @param Right �������������±�
 * @param temp ��������������
 *
 * @return ��
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
 * @brief �鲢
 * @param L ��������������
 * @param Left �������������±�
 * @param Mid �����������м��±�
 * @param Right �������������±�
 * @param temp ��������������
 *
 * @return ��
 */
void Sort::Merge(LinearList<int>* L, int Left, int Mid, int Right, LinearList<int>* temp)
{
	int i = Left;
	int j = Mid + 1;
	int k = 0;
	//���������������ݶ������򣬷ֱ�������ұȽ����������е����ݣ���С�ķ���temp��
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
	//û�з���������м�������temp��
	while (i <= Mid)
	{
		temp->Put(k++, L->Get(i++));
	}
	while (j <= Right)
	{
		temp->Put(k++, L->Get(j++));
	}
	k = 0;
	//������ɺ����ԭ����
	while (Left <= Right)
	{
		L->Put(Left++, temp->Get(k++));
	}
}

//������������
void Sort::QuickSort(LinearList<int>* L)
{
	int i = 1;
	int j = L->Length() - 1;
	QSort(L, i, j);
}

void Sort::QSort(LinearList<int>* L, int i, int j)
{
	int left = i;//ȡ��ߵڶ�����Ϊ���ڱ�
	int right = j;//ȡ�ұߵ�һ����Ϊ���ڱ�
	int key = i - 1;//ȡ��ߵ�һ����Ϊ��׼ֵ
	if (i > j)
		return;
	while (i < j)//���ڱ���������ڱ���ߵ������
	{
		while (L->Get(j) >= L->Get(key) && i < j)//���ڱ���ֵ�����ڵ��ڻ�׼ֵ���ڱ������ƶ�
			j--;
		while (L->Get(i) <= L->Get(key) && i < j)//���ڱ���ֵ��С�ڵ��ڻ�׼ֵ���ڱ������ƶ�
			i++;
		if (i < j)//���ڱ���������ڱ���ߵ�����½������ߵ�ֵ
			L->Swap(i, j);
	}
	if (L->Get(key) > L->Get(i))//��׼��ֵ���������ڱ���ֵ�򽻻����ߵ�ֵ
	{
		L->Swap(key, i);
	}
	else
	{
		i--;
	}
	QSort(L, left, i - 1);//��׼ֵ������ظ����Ϲ���
	QSort(L, i + 2, right);//��׼ֵ���ұ��ظ����Ϲ���
}
