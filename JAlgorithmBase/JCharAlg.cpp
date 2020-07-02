#include "JCharAlg.h"



JCharAlg::JCharAlg()
{
}


JCharAlg::~JCharAlg()
{
}

char JCharAlg::FindFreqChar(string str)
{
	map<char, int> m_map;
	map<char, int>::iterator it;
	pair<char, int> m_pair;
	for (char c : str)
	{
		it = m_map.find(c);
		if (it != m_map.end())
			(it->second)++;
		else
		   m_map.insert(std::make_pair(c, 0));
	}
	it = m_map.begin();
	for (map<char, int>::iterator i = m_map.begin(); i != m_map.end(); i++)
		if (i->second > it->second)
			it = i;
	
	return it->first;
}

pair<string, int> JCharAlg::FindFreqWord(const char* strFile)
{
	ifstream fs;
	fs.open(strFile,ifstream::in);
	if (!fs)
		cerr << "File Read Failed!" << endl;

	string word;
	map<string, int> word_count;
	while (fs >> word)
	{
		word_count[word]++;
	}
	typedef map<string, int>::iterator map_it;
	map_it it1, it2;
	for (it1 = it2 = word_count.begin(); it1 != word_count.end(); it1++)
	{
		if (it1->second > it2->second)
			it2 = it1;
	}
	return *it2;
}

int JCharAlg::StrToInt(const char * str)
{
	if (nullptr == str)
		throw BadInput();
	int result = 0;
	while (*str != '\0')
	{
		int tmp = (int)(*str - 48);
		if (tmp < 0 || tmp>9)
			throw BadInput();
		else
			result = 10 * result + tmp;
		str++;
	}
	return result;
}

char * JCharAlg::IntToStr(const int & n)
{
	bool bNeg = n < 0 ? true : false;
	unsigned int m = bNeg?-n:n;
	int num1 = m /10;
	int num2 = m %10;
	int i = 0;
	char result1[10] = { 0 };
	char result2[10] = { 0 };
	while (num1 > 9)
	{
		result1[i] = (char)(num2 + 48);
		num2 = num1 % 10;
		num1 /= 10;
		i++;
	}
	result1[i] = (char)(num2 + 48);
	result1[++i] = (char)(num1 + 48);
	if (bNeg)
	{
		result1[++i] = '-';
		result1[++i] = '\0';
	}
	else
		result1[++i] = '\0';
	for (int j = 0; j < i; j++)
		result2[j] = result1[i - j - 1];

	return result2;
}

unsigned int JCharAlg::Strlen(const char * str)
{
	if (NULL == str)
		throw BadInput();
	int n = 0;
	while ('\0' != *str++)
		n++;
	return n;
}

char * JCharAlg::Strcpy(char * dest, const char * source)
{
	if(NULL == source)
		throw BadInput();
	while ('\0' != *source)
		*dest++ = *source++;
	*dest = '\0';
	return dest;
}

int JCharAlg::Strcmp(const char * str1, const char * str2)
{
	if (NULL == str1 || NULL == str2)
		throw BadInput();
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	return *str1-*str2;
}
