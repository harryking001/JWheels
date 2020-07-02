#include "JKMP.h"

void KMP::GetNext(string T, uint* next)
{
	next[0] = 0;
	uint i = 1;
	uint j = 0;
	uint Tlen = T.length();
   	while (i < Tlen)
	{
        //�Ӵ�ǰ�������ַ��ȱȽϣ������ͬ������ָ�루i��j���ֱ�ǰ�������Ƚϣ�����ͬ�Ļ��������ָ��j���ݣ�ǰ���ָ�벻������j������ɺ�����ָ�����ǰ���Ƚ�
		if (j == 0 || T[i-1] == T[j-1])
		{
			i++;
			j++;
			next[i-1] = j;
		}
		else
		{
			j = next[j-1];//j����
		}
	}
}

uint KMP::IndexKMP(string S, string T, uint pos)
{
	uint Slen = S.length();
	uint Tlen = T.length();
	if(pos > Slen || pos > Tlen)
		return 0;
	uint i = pos;//��posλ��ʼ
	uint j = 0;
	uint next[100] = { 0 };
	GetNext(T, next);//��ȡ�Ӵ���next����
	while (i <= Slen && j <= Tlen)
	{
		if (j == 0 || S[i-1] == T[j-1])//�Ӵ����������αȽϣ���ȵĻ�������ǰ�������Ӵ�ָ�����
		{
			i++;
			j++;
		}
		else
		{
			j = next[j-1];
		}
	}
	if (j > Tlen)
		return i-Tlen;
	else
		return 0;
}