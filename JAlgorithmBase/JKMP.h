#ifndef KMP_H
#define KMP_H

#include "stdafx.h"
#include <string>

using std::string;
#define uint unsigned int

class KMP
{
public:
	static void GetNext(string T, uint* next);
	static uint IndexKMP(string S, string T, uint pos);
};



#endif