#ifndef LZW_H
#define LZW_H

#include "ChainHashTable.h"
#include "Define.h"
#include <fstream>
#include <iostream>

using namespace std;

class LZW;

class ComElement
{
	friend LZW;
public:
	bool operator == (const ComElement& x)
	{
        return code == x.code;
	}
private:
    unsigned int code;
	unsigned int key;
};

struct DeComElement
{
    unsigned int prefix;
	unsigned char suffix;
};

class LZW
{
public:
	LZW();
	~LZW();
	bool Compress(char* fileName);
	bool DeCompress(char* fileName);
	void ComOutPut(unsigned int code);
	void DeComOutPut(unsigned int code);
	bool GetCode(unsigned int& code);
	bool StrDiscard(char* Source, const char* strName);

private:
	static const int alpha = 256;//ASCII码总数
    static const int bytesize = 8;//8位大小
    static const int excess = 4;//4位大小
	static const int mask1 = 255;//8位全置1
    static const int mask2 = 15;//4位全置1
	ifstream infile;//输入流
	ofstream outfile;//输出流
	bool bCodesLeft;//是否有未输出的位
	int size;
	unsigned int left;//剩余4位数据
	char s[codes];//输出字符串
	DeComElement h[codes];
	
};

#endif