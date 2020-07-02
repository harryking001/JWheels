#include "stdafx.h"
#include "Chain.h"

class Node
{
public:
	int score;
	char* name;
};

void BinSort(Chain<Node>& X, int range)
{
    Chain<Node>* bin = new Chain<Node>[range];
    Node x;
	while(!X.IsEmpty ())
	{
        X.Delete(1,x);
		bin[x.score].Insert (0,x);
	}
	for(int i=0;i<range;i++)
	{
		while(!bin[i].IsEmpty ())
		{
            bin[i].Delete(1,x);
		    X.Insert (0,x);
		}
	}
	delete[] bin;
}