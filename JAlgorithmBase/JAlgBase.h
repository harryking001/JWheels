#pragma once
class JAlgorithmBase
{
public:
	JAlgorithmBase();
	~JAlgorithmBase();

	static void Fitting(float* Vec1, float* Vec2, int StartIndex, int Count, float& Slope, float& Intercept);
};

