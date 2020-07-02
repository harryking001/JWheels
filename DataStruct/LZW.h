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
	static const int alpha = 256;//ASCII������
    static const int bytesize = 8;//8λ��С
    static const int excess = 4;//4λ��С
	static const int mask1 = 255;//8λȫ��1
    static const int mask2 = 15;//4λȫ��1
	ifstream infile;//������
	ofstream outfile;//�����
	bool bCodesLeft;//�Ƿ���δ�����λ
	int size;
	unsigned int left;//ʣ��4λ����
	char s[codes];//����ַ���
	DeComElement h[codes];
	
};

#endif