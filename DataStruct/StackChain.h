#ifndef STACK_CHAIN_H
#define STACK_CHAIN_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

using std::ostream;
using std::endl;

template <class T>
class StackChain;

template<class T>
class StackChainNode
{
public:
    friend class StackChain<T>;
private:
	T data;
	StackChainNode<T>* next;
};

template<class T>
class StackChain
{
public:
	StackChain();
	StackChain(const StackChain<T>& s);
	~StackChain();
	bool IsEmpty() const;
	bool IsFull() const;
	T Top() const;
	StackChain<T>& Push(const T& t);
	StackChain<T>& Pop(T& t);
	void Output(ostream& out) const;
	void Erase();
private:
	StackChainNode<T>* top;//将栈的top指针和链表的first指针合二为一
};

template<class T>
StackChain<T>::StackChain()
{ 
	top = NULL;
}

template<class T>
StackChain<T>::StackChain(const StackChain<T>& s)
{
	StackChainNode<T>* pCur = s.top;
	StackChainNode<T>* pPre = new StackChainNode<T>();
	if (pCur)
	{
		*pPre = *pCur;
		top = pPre;
		pCur = pCur->next;
	}
	else
	{
		delete pPre;
		pPre = NULL;
	}
	while (pCur)
	{
		StackChainNode<T>* pNode = new StackChainNode<T>();
		*pNode = *pCur;
		pPre->next = pNode;
		pPre = pNode;
		pCur = pCur->next;
	}
	if (pPre)
	{
		pPre->next = NULL;
	}
}

template<class T>
StackChain<T>::~StackChain()
{
	StackChainNode<T>* pCur = NULL;
    while(top)
	{
		pCur = top->next;
        delete top;
		top = pCur;
	}
}

template<class T>
bool StackChain<T>::IsEmpty() const
{ 
	return top == NULL;//类似链表的first == NULL 
}

template<class T>
bool StackChain<T>::IsFull() const
{
    try
	{
		StackChainNode<T>* pCur = new StackChainNode<T>();
		delete pCur;
        return false;
	}
	catch(...)
	{
		return true;
	}

}

template<class T>
T StackChain<T>::Top() const
{
	if(IsEmpty()) 
		throw BadCall();
    return top->data;
}

//栈元素的增加方向和单链表的方向相反
template<class T>
StackChain<T>& StackChain<T>::Push(const T& t)
{
	StackChainNode<T>* pCur = new StackChainNode<T>();
	pCur->data = t;
	pCur->next = top;
	top = pCur;
	return *this;
}

template<class T>
StackChain<T>& StackChain<T>::Pop(T& t)
{
	if (IsEmpty())
		throw BadCall();
    t = top->data;
	top = top->next;
	return *this;
}

template<class T>
void StackChain<T>::Output(ostream& out) const
{
	StackChainNode<T>* pCur = top;
	while (pCur)
	{
		out << pCur->data << " ";
		pCur = pCur->next;
	}
	out << endl;
}

//清空链表
template<class T>
void StackChain<T>::Erase()
{
	StackChainNode<T>* pCur = NULL;
	while (top)
	{
		pCur = top->next;
		delete top;
		top = pCur;
	}
}

#endif