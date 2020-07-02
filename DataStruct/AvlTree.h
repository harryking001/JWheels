#ifndef AVLTREE_H
#define AVLTREE_H

#include "stdafx.h"
#include "Exception.h"
#include <iostream>
#include "BinaryTree.h"

template<class K, class V>
class AvlTreeNode
{
public:
	friend class AvlTree<K, V>;
	AvlTreeNode<K, V>(K kk, V vv, int hgt) : k(kk), v(vv), height(hgt), leftChild(NULL), rightChild(NULL) {}
private:
	K k;
	V v;
	int height;
	AvlTreeNode<K, V>* leftChild;
	AvlTreeNode<K, V>* rightChild;
};

template<class K, class V>
class AvlTree
{
public:
	AvlTree();
	~AvlTree();
	int GetHeight(AvlTreeNode<K, V>* node);
	AvlTreeNode<K, V>* Search(const K k) const;
	AvlTreeNode<K, V>* MinNode(const AvlTreeNode<K, V>* const node) const;
	AvlTreeNode<K, V>* MaxNode(const AvlTreeNode<K, V>* const node) const;
	bool Insert(const K k, const V& v, AvlTreeNode<K, V>* node);
	bool Delete(const K k, V& v, AvlTreeNode<K, V>* node);
	void InOrder(AvlTreeNode<K, V>* node, void(*visit)(AvlTreeNode<K, V>* nd));
	void PreOrder(AvlTreeNode<K, V>* node, void(*visit)(AvlTreeNode<K, V>* nd));
	void PostOrder(AvlTreeNode<K, V>* node, void(*visit)(AvlTreeNode<K, V>* nd));
	void LevelOrder(AvlTreeNode<K, V>* node, void(*visit)(AvlTreeNode<K, V>* nd));
private:
	AvlTreeNode<K, V>* LLRotation(AvlTreeNode<K, V>* node);
	AvlTreeNode<K, V>* LRRotation(AvlTreeNode<K, V>* node);
	AvlTreeNode<K, V>* RRRotation(AvlTreeNode<K, V>* node);
	AvlTreeNode<K, V>* RLRotation(AvlTreeNode<K, V>* node);
	int MaxHgt(const AvlTreeNode<K, V>* const leftNode, const AvlTreeNode<K, V>* const rightNode);
	void ClearNode(AvlTreeNode<K, V>* node);
	AvlTreeNode<K, V>* root;
};


template<class K, class V>
AvlTree<K,V>::AvlTree()
{
	root = NULL;
}

template<class K, class V>
AvlTree<K,V>::~AvlTree()
{
	PostOrder(root, ClearNode);
    root = NULL;
}

template<class K, class V>
int AvlTree<K, V>::GetHeight(AvlTreeNode<K, V>* node)
{
	if(!node)
	    return 0;
	return node->height;
}

template<class K, class V>
AvlTreeNode<K, V>* AvlTree<K, V>::Search(const K k) const
{
	AvlTreeNode<K, V>* node = root;
	while (node)
	{
		if (k == node->k)
		{
			return node;
		}
		else if (k > node->k)
		{
			node = node->rightChild;
		}
		else
		{
			node = node->leftChild;
		}
	}
	return NULL;
}

template<class K, class V>
AvlTreeNode<K, V>* AvlTree<K, V>::MinNode(const AvlTreeNode<K, V>* const node) const
{
	if(!node)
	    return NULL;
    AvlTreeNode<K, V>* minNode = node;
	while(minNode->leftChild)
	{
		minNode = minNode->leftChild;
	}
	return minNode;
}

template<class K, class V>
AvlTreeNode<K, V>* AvlTree<K, V>::MaxNode(const AvlTreeNode<K, V>* const node) const
{
	if(!node)
	    return NULL;
    AvlTreeNode<K, V>* maxNode = node;
	while(maxNode->rightChild)
	{
		maxNode = maxNode->leftChild;
	}
	return maxNode;
}

template<class K, class V>
bool AvlTree<K, V>::Insert(const K k, const V& v, AvlTreeNode<K, V>* node)
{
	AvlTreeNode<K, V>* newNode = new AvlTreeNode<K, V>(k,v,0);
	if (node == NULL)
	{
		node = newNode;
	}
	else
	{
		if (k < node->k)
		{
			Insert(k, v, node->leftChild);
			if(GetHeight(node->leftChild) - GetHeight(node->rightChild) == 2)
			{
                if(k < node->leftChild->k)
				{
                    LLRotation(node);
				}
				else
				{
                    LRRotation(node);
				}
			}
		}
		else if (k > node->k)
		{
			Insert(k, v, node->rightChild);
			if(GetHeight(node->leftChild) - GetHeight(node->rightChild) == -2)
			{
                if(k > node->leftChild->k)
				{
                    RRRotation(node);
				}
				else
				{
                    RLRotation(node);
				}
			}
		}
		else
		{
			return false;
		}
	}
	node->height = MaxHgt(node->leftChild, node->rightChild) + 1;
	return true;
}

template<class K, class V>
bool AvlTree<K, V>::Delete(const K k, V& v, AvlTreeNode<K, V>* node)
{
	if(!node)
	    return false;
    if (k < node->k)
	{
		Delete(k, v, node->leftChild);
		if(GetHeight(node->leftChild) - GetHeight(node->rightChild) == 2)
		{
            if(k < node->leftChild->k)
			{
                LLRotation(node);
			}
			else
			{
                LRRotation(node);
			}
		}
	}
	else if (k > node->k)
	{
		Delete(k, v, node->rightChild);
		if(GetHeight(node->leftChild) - GetHeight(node->rightChild) == -2)
		{
            if(k > node->leftChild->k)
			{
                RRRotation(node);
			}
			else
			{
                RLRotation(node);
			}
		}
	}
	else
	{
		if(node->leftChild == NULL && node->rightChild == NULL)
		{
            delete node;
		}
        else if(GetHeight(node->leftChild) > GetHeight(node->rightChild))
		{
			AvlTreeNode<K, V>* minNode = MinNode(node->leftChild);
			node->k = minNode->k;
			node->v = minNode->v;
			Delete(minNode->k, minNode->v, node->leftChild);
		}
		else
		{
			AvlTreeNode<K, V>* maxNode = MinNode(node->rightChild);
			node->k = maxNode->k;
			node->v = maxNode->v;
			Delete(maxNode->k, maxNode->v, node->rightChild);
		}
		
	}
	return true;
}

template<class K, class V>
void AvlTree<K, V>::InOrder(AvlTreeNode<K, V>* node, void (*visit)(AvlTreeNode<K, V>* nd))
{
	if (node)
	{
		visit(node);
		InOrder(node->leftChild, visit);
		InOrder(node->rightChild, visit);
	}
}

template<class K, class V>
void AvlTree<K, V>::PreOrder(AvlTreeNode<K, V>* node, void(*visit)(AvlTreeNode<K, V>* nd))
{
	if (node)
	{
		PreOrder(node->leftChild, visit);
		visit(node);
		PreOrder(node->rightChild, visit);
	}
}

template<class K, class V>
void AvlTree<K, V>::PostOrder(AvlTreeNode<K, V>* node, void(*visit)(AvlTreeNode<K, V>* nd))
{
	if (node)
	{
		PostOrder(node->leftChild, visit);
		PostOrder(node->rightChild, visit);
		visit(node);
	}
}

template<class K, class V>
void AvlTree<K, V>::LevelOrder(AvlTreeNode<K, V>* node, void(*visit)(AvlTreeNode<K, V>* nd))
{
	if(!node)
	    return;
	Queue q(100);
	AvlTreeNode<K, V>* visitNode = node;
	q.push(visitNode);
	while(true)
	{
		try
		{
			visitNode = q.pop();
		}
		catch(BadInput)
		{
			break;
		}
	    visit(visitNode);
		if(visitNode->leftChild)
	        q.push(visitNode->leftChild);
		if(visitNode->rightChild)
	        q.push(visitNode->rightChild);
	}
    
	
}

template<class K, class V>
AvlTreeNode<K, V>* AvlTree<K, V>::LLRotation(AvlTreeNode<K, V>* node)
{
	if(!node)
	    return NULL;
    AvlTreeNode<K, V>* leftNode = node->leftChild;
	node->leftChild = leftNode->rightChild;
	leftNode->rightChild = node;
	node->height = MaxHgt(node->leftChild, node->rightChild) + 1;
	leftNode->height = MaxHgt(leftNode->leftChild, node->height) + 1;
	return leftNode;
}

template<class K, class V>
AvlTreeNode<K, V>* AvlTree<K, V>::LRRotation(AvlTreeNode<K, V>* node)
{
	if(!node)
	    return NULL;
    AvlTreeNode<K, V>* leftNode = RRRotation(node->leftChild);
	return LLRotation(node);
}

template<class K, class V>
AvlTreeNode<K, V>* AvlTree<K, V>::RRRotation(AvlTreeNode<K, V>* node)
{
	if(!node)
	    return NULL;
    AvlTreeNode<K, V>* rightNode = node->rightChild;
	node->rightChild = rightNode->leftChild;
	rightNode->leftChild = node;
	node->height = MaxHgt(node->leftChild, node->rightChild) + 1;
	rightNode->height = MaxHgt(node->height, rightNode->rightChild) + 1;
	return rightNode;
}

template<class K, class V>
AvlTreeNode<K, V>* AvlTree<K, V>::RLRotation(AvlTreeNode<K, V>* node)
{
	if(!node)
	    return NULL;
    AvlTreeNode<K, V>* rightNode = LLRotation(node->rightChild);
	return RRRotation(node);
}

template<class K, class V>
int AvlTree<K, V>::MaxHgt(const AvlTreeNode<K, V>* const leftNode, const AvlTreeNode<K, V>* const rightNode)
{
	if(leftNode == NULL && rightNode == NULL)
	    return 0;
	else if (leftNode == NULL)
	{
		return rightNode->height;
	}
	else if (rightNode == NULL)
	{
		return leftNode->height;
	}
	else
	{
		return leftNode->height > rightNode->height ? leftNode->height : rightNode->height;
	}
}

template<class K, class V>
void AvlTree<K, V>::ClearNode(AvlTreeNode<K, V>* node)
{
    if(node)
	{
		delete node;
	}
}

#endif