#ifndef JSTRING_H
#define JSTRING_H

#include "stdafx.h"
#include <iostream>

using std::istream;
using std::ostream;
using std::endl;

class Jstring
{
public:
    Jstring(const char* s);
	~Jstring();
	Jstring(const Jstring& other);
	bool operator==(const char* ch);
	bool operator==(const Jstring& other);
	Jstring& operator=(const char* ch);
    Jstring& operator=(const Jstring& other);
	bool operator<(const Jstring& other);
	bool operator<=(const Jstring& other);
	bool operator>(const Jstring& other);
	bool operator>=(const Jstring& other);
	inline char operator[](int i)
	{
        return str[i];
	}
	friend Jstring operator+(const Jstring& str1, const Jstring& str2);
	Jstring& operator+=(const Jstring& other);
	friend ostream& operator<<(ostream& out, const Jstring& jstr);
	friend istream& operator>>(istream& in, Jstring& jstr);
	inline int Size() const
	{
		return length;
	}

	inline const char* GetStr() const
	{
        return str;
	}

	inline bool IsEmpty() const
	{
		return str == NULL;
	}
private:
	char* str;
	int length;
};

Jstring::Jstring(const char* s)
{
    if(s == NULL)//字符串为空则申请一个字节的内存放'\0'
    {
		length = 0;
        str = new char[1];
		str[0] = '\0';
	}
	else
	{
        length = strlen(s);
		str = new char[length + 1];
		strncpy_s(str, length+1, s, length + 1);
	}
}

//复制构造函数
Jstring::Jstring(const Jstring& other)
{
	length = other.length;
    str = new char[length + 1];
    strncpy_s(str, length + 1, other.str, length + 1);//other作为Jstring类本身的对象，可以直接访问其私有成员
}

Jstring::~Jstring()
{
    delete[] str;
	str = NULL;
	length = 0;
}

bool Jstring::operator==(const char* ch)
{
	return strcmp(str, ch) == 0 ? true : false;
}

bool Jstring::operator==(const Jstring& other)
{
	if(length != other.length)
		return false;
	return strcmp(str,other.str)==0 ? true:false;
}

Jstring& Jstring::operator=(const char* ch)
{
	delete[] str;
	length = strlen(ch);
	str = new char[length + 1];
	strncpy_s(str, length + 1, ch, length + 1);
	return *this;
}

Jstring& Jstring::operator=(const Jstring& other)
{
	if(&other == this) return *this;
	delete[] str;
    length = other.length;
    str = new char[length+1];
    strncpy_s(str, length + 1, other.str, length + 1);
	return *this;
}

bool Jstring::operator<(const Jstring& other)
{
    return strcmp(str, other.str) < 0 ? true:false;
}

bool Jstring::operator<=(const Jstring& other)
{
    return strcmp(str, other.str) <= 0 ? true:false;
}

bool Jstring::operator>(const Jstring& other)
{
    return strcmp(str, other.str) > 0 ? true:false;
}

bool Jstring::operator>=(const Jstring& other)
{
    return strcmp(str, other.str) >= 0 ? true:false;
}

Jstring operator+(const Jstring& str1, const Jstring& str2)
{
	Jstring strNew(NULL);
	strNew.length = str1.length + str2.length;
	strNew.str = new char[strNew.length + 1];
	strcpy_s(strNew.str, str1.Size() + 1, str1.str);
    strcat_s(strNew.str, str1.Size() + str2.Size() + 1, str2.str);
	return strNew;
}

Jstring& Jstring::operator+=(const Jstring& other)
{
	if(NULL == other.str)
		return *this;
	if(&other == this)
	{
        Jstring copy(other);
		return *this += copy;//嵌套
	}
    length += other.length;
	char* strNew = str;
	str = new char[length + 1];
	strcpy_s(str, length + 1, strNew);
	strcat_s(str, length + other.Size() + 1, other.str);
	delete[] strNew;
	strNew = NULL;
	return *this;
}

ostream& operator<<(ostream& out, const Jstring& jstr)
{
    out << jstr.str;
	return out;
}

istream& operator>>(istream& in, Jstring& jstr)
{
    char temp[100];
	if(in >> temp)
	{
		delete[] jstr.str;
		int len = strlen(temp);
		jstr.str = new char[len+1];
		strcpy_s(jstr.str, len + 1, temp);
		jstr.length = len;
	}
	return in;
}

#endif
