#ifndef STRING_H
#define STRING_H

#include "stdafx.h"
#include <iostream>

class String
{
public:
    String(const char* s);
	~String();
	String(const String& other);
	String& operator=(const String& other);
	bool operator==(const String& other);
	bool operator<(const String& other);
	bool operator<=(const String& other);
	bool operator>(const String& other);
	bool operator>=(const String& other);
	inline char operator[](int i)
	{
        return str[i];
	}
	friend String operator+(const String& str1, const String& str2) const;
	String& operator+=(const String& other);
	friend &ostream operator<<(ostream& out, const String& string) const;
	friend &istream operator>>(istream& in, String& string);
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
		return str==NULL;
private:
	char* str;
	int length;
};

String::String(const char* s)
{
    if(s == NULL)//字符串为空则申请一个字节的内存放'\0'
    {
		length=0;
        str = new char[1];
		str[0] = '\0';
	}
	else
	{
        length = strlen(s);
		str = new char[length+1];
		strncpy_s(str,length+1,s,length+1);
	}
}

String::~String()
{
    delete[] str;
	str = NULL;
	length=0;
}

//复制构造函数
String::String(const String& other)
{
	length = other.length;
    str = new char[length+1];
    strncpy_s(str,length+1,other.str,length+1);//other作为String类本身的对象，可以直接访问其私有成员
}

String::String& operator=(const String& other)
{
	if(other == *this) return *this;
	delete[] str;
    length = other.length;
    str = new char[length+1];
    strncpy_s(str,length+1,other.str,length+1);
	return *this;
}

bool String::operator==(const String& other)
{
	if(length != other.length)
		return false;
	return strcmp(str,other.str)==0 ? true:false;
}

bool String::operator<(const String& other)
{
    return strcmp(str,other.str)<0 ? true:false;
}

bool String::operator<=(const String& other)
{
    return strcmp(str,other.str)<=0 ? true:false;
}

bool String::operator>(const String& other)
{
    return strcmp(str,other.str)>0 ? true:false;
}

bool String::operator>=(const String& other)
{
    return strcmp(str,other.str)>=0 ? true:false;
}

String operator+(const String& str1, const String& str2) const
{
	String strNew;
	strNew.length = strNew.length + length;
	strNew.str = new char[strNew.length+1];
	strcpy(strNew.str,str);
    strcat(strNew.str,other.str);
	return strNew;
}

String::String& operator+=(const String& other)
{
	if(NULL == other.str)
		return *this;
	if(this==&other)
	{
        String copy(other);
		return *this += copy;//嵌套
	}
    length+=other.length;
	char* strNew = str;
	str = new char[length+1];
	strcpy(str,strNew);
	strcat(str,other.str);
	delete[] strNew;
	strNew=NULL;
	return *this;
}

&ostream operator<<(ostream& out, const String& string) const
{
    out << string.str;
	return out;
}

&istream operator>>(istream& in, String& string)
{
    char temp[100];
	if(in>>temp)
	{
		delete[] string.str;
		int len = strlen(temp);
		string.str = new char[len+1];
		strcpy(string.str,temp);
	}
	return in;
}
#endif