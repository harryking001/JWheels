#pragma once
#include<string>
#include<map>
#include<iostream>
#include<fstream>
#include<sstream>
#include<exception>
#include "Exception.h"
using std::string;
using std::map;
using std::pair;
using std::size_t;
using std::ifstream;
using std::stringstream;
using std::cerr;
using std::endl;
using std::exception;

class JCharAlg
{
public:
	JCharAlg();
	~JCharAlg();
	char FindFreqChar(string str);
	pair<string,int> FindFreqWord(const char* strFile);
	int StrToInt(const char* str);
	char* IntToStr(const int& n);
	unsigned int Strlen(const char* str);
	char* Strcpy(char* dest, const char* source);
	int Strcmp(const char* str1, const char* str2);
};

