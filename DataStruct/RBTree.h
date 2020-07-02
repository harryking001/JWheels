#ifndef RBTREE_H
#define RBTREE_H

#include "stdafx.h"
#include "Exception.h"

enum NodeColor
{
	Red,
	Black
}
enum SonType
{
    None,
	LeftSon,
	RightSon
}

template<class T>
class RBTree;

template<class T>
class RBTreeNode
{
friend RBTree<T>;
public:
	RBTreeNode(T key, NodeColor nodeColor, RBTreeNode<T>* pParent, RBTreeNode<T>* pLeftSon, RBTreeNode<T>* pRightSon)
	{
       this.Key = key; 
	   this.nodeColor = Color;
	   this.pParent = parent;
	   this.pLeftSon = leftSon;
	   this.pRightSon = rightSon;
	}
	~RBTreeNode()
	{
        
	}


private:
	T Key;
	NodeColor Color;
	SonType Type;
	RBTreeNode<T>* parent;
    RBTreeNode<T>* leftSon;
	RBTreeNode<T>* rightSon;
};

template<class T>
class RBTree
{
public:
	RBTree
	{

	}
	~RBTree
	{

	}
    
    RBTree<T>* Insert(T key);
	RBTree<T>* InsertFixUp(RBTreeNode<T>* node);

private:
    RBTreeNode<T>* Root;
};

template<class T>
RBTree<T>* RBTree<T>::Insert(T key)
{
    RBTreeNode<T>* node = new RBTreeNode(key, Red, NULL, NULL, NULL);
	RBTreeNode<T>* x = Root;
	if(!x)
	{
        x->Color = Black;
		x->Type = None;
		x->Key = key;
		x->parent = NULL;
		x->leftSon = NULL;
		x->rightSon = NULL;
		node = x;
		return node;
	}
	else
	{
	    while(x)
	    {
            if(key<x->Key)
		    {
				if(x->leftSon == NULL)
				{
                    node->Type = LeftSon;
					node->parent = x;
                    x->leftSon = node;
					break;
				}
				else
				{
                    x = x->leftSon;
				}
		    }
		    else
		    {
				if(x->rightSon == NULL)
				{
                    node->Type = RightSon;
					node->parent = x;
                    x->rightSon = node;
					break;
				}
				else
				{
                    x = x->rightSon;
				}
		    }
	    }
	}
    return (InsertFixUp(node));
}

template<class T>
RBTree<T>* RBTree<T>::InsertFixUp(RBTreeNode<T>* node)
{
    RBTreeNode<T>* parent = node->parent;
    RBTreeNode<T>* grandparent = parent->parent;
	if(grandparent != NULL)
	{
	    if(parent->Type == rightSon)
	    {
            RBTreeNode<T>* uncle = grandparent->leftSon;
	    }
		else
		{
            RBTreeNode<T>* uncle = grandparent->rightSon;
		}

		if(parent->Color == Black)
		{

		}
		else if(parent->Color == Red && uncle->Color == Red)
		{

		}
		else if(parent->Color == Red && uncle->Color == Black)
		{

		}
		else
		{

		}
	}

	return *this;
    
}

#endif