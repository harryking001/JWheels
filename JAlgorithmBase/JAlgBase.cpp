#include "JAlgBase.h"



JAlgorithmBase::JAlgorithmBase()
{
}


JAlgorithmBase::~JAlgorithmBase()
{
}

//线性
//* v1 - 向量; v2 - X值向量; startIndex - 起始点序号; Count - 点数; t
void JAlgorithmBase::Fitting(float* Vec1, float* Vec2, int StartIndex, int Count, float& Slope, float& Intercept)
{
	//v1=y,v2=x 
	float A = 0, B = 0, C = 0, D = 0;
	int NUM = Count - 1;

	int i = 0;
	for (i = StartIndex; i <= StartIndex + NUM; i++)
	{
		A = A + Vec1[i] * Vec2[i]; //xi * yi 
	}
	A = Count * A;

	B = 0;
	C = 0;
	for (i = StartIndex; i <= StartIndex + NUM; i++)
	{
		B = B + Vec2[i];
		C = C + Vec1[i];
	}
	B = B * C;
	C = 0;
	for (i = StartIndex; i <= StartIndex + NUM; i++)
	{
		C = C + Vec2[i] * Vec2[i];// 
	}
	C = Count * C;
	D = 0;
	for (i = StartIndex; i <= StartIndex + NUM; i++)
	{
		D = D + Vec2[i];
	}
	D = D * D;
	Slope = (A - B) / (C - D);
	float E = 0;
	for (i = StartIndex; i <= StartIndex + NUM; i++)
	{
		E = E + Vec1[i];
	}
	E = E / Count;
	float F = 0;
	for (i = StartIndex; i <= StartIndex + NUM; i++)
	{
		F = F + Vec2[i];
	}
	F = F / Count;
	Intercept = E - Slope * F;
}

