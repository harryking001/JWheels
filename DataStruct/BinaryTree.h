#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>

template<class T>
class TreeNode
{
public:
	friend class BinaryTree<class T>;
private:
	T data;
	TreeNode<T>* leftParent;
	TreeNode<T>* rightParent;
};

template<class T>
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();
	void Insert();
	void Delete();
private:
	TreeNode<T>* root;
};

#endif
