#include "JKMP.h"

void KMP::GetNext(string T, uint* next)
{
	next[0] = 0;
	uint i = 1;
	uint j = 0;
	uint Tlen = T.length();
   	while (i < Tlen)
	{
        //子串前后两个字符先比较，如果相同，两个指针（i和j）分别前进继续比较，不相同的话，后面的指针j回溯，前面的指针不动，等j回溯完成后两个指针继续前进比较
		if (j == 0 || T[i-1] == T[j-1])
		{
			i++;
			j++;
			next[i-1] = j;
		}
		else
		{
			j = next[j-1];//j回溯
		}
	}
}

uint KMP::IndexKMP(string S, string T, uint pos)
{
	uint Slen = S.length();
	uint Tlen = T.length();
	if(pos > Slen || pos > Tlen)
		return 0;
	uint i = pos;//从pos位开始
	uint j = 0;
	uint next[100] = { 0 };
	GetNext(T, next);//获取子串的next数组
	while (i <= Slen && j <= Tlen)
	{
		if (j == 0 || S[i-1] == T[j-1])//子串和主串依次比较，相等的话继续向前，否则子串指针回溯
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