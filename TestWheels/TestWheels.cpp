#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Sequence.h"
#include "Chain.h"
#include "CircularChain.h"
#include "DCChain.h"
#include "FreeList.h"
#include "SimChain.h"
#include "CircularQueue.h"
#include "QueueChain.h"
#include "DoubleStack.h"
#include "StackChain.h"
#include "StackSequence.h"
#include "ChainHashTable.h"
#include "HashTable.h"
#include "SortedList.h"
#include "SortedChain.h"
#include "SkipList.h"
#include "MaxHeap.h"
#include "Jstring.h"

using std::cin;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;
using std::to_string;

enum structType
{
	sequenceType,
	chainType,
	circularChainType,
	dcChainType,
	simSpaceType,
	freeListType,
	circularQueueType,
	queueChainType,
	doubleStackType,
	stackChainType,
	stackSequenceType,
	sortedListType,
	sortedChainType,
	skipListType,
	chainHashTableType,
	hashTableType
};

void TestLinList(structType st)
{
	Sequence<int> sequence;
	Chain<int> chain;
	ChainNode<int>* chainNode = new ChainNode<int>();
	CircularChain<int> circularChain;
	CircularChainNode<int>* circularChainNode = new CircularChainNode<int>();
	DCChain<int> dcChain;
	DCChainNode<int>* dcChainNode = new DCChainNode<int>();
	string strIndex, strVal, strCmd;
	stringstream ss;
	int index, value, length;
	bool bRet = false;
	while (true)
	{
		cout << "Please enter the command:" << endl;
		getline(cin, strCmd);
		if (strCmd == "insert")
		{
			cout << "Please enter the index:" << endl;
			getline(cin, strIndex);
			ss.clear();
			ss << strIndex;
			ss >> index;
			cout << "Please enter the value:" << endl;
			getline(cin, strVal);
			ss.clear();
			ss << strVal;
			ss >> value;
			try
			{
				switch (st)
				{
				case sequenceType:
					sequence.Insert(index, value);
					break;
				case chainType:
                    chain.Insert(index, value);
					break;
				case circularChainType:
					circularChain.Insert(index, value);
					break;
				case dcChainType:
					dcChain.Insert(index, value);
					break;
				default:
					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
		}
		else if (strCmd == "delete")
		{
			cout << "Please enter the index:" << endl;
			getline(cin, strIndex);
			ss.clear();
			ss << strIndex;
			ss >> index;
			try
			{
				switch (st)
				{
				case sequenceType:
					sequence.Delete(index, value);
					break;
				case chainType:
					chain.Delete(index, value);
					break;
				case circularChainType:
					circularChain.Delete(index, value);
					break;
				case dcChainType:
					dcChain.Delete(index, value);
					break;
				default:
					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
			cout << "Delete value is: " + to_string(value) << endl;
		}
		else if (strCmd == "find")
		{
			cout << "Please enter the index:" << endl;
			getline(cin, strIndex);
			ss.clear();
			ss << strIndex;
			ss >> index;
			switch (st)
			{
			case sequenceType:
				bRet = sequence.Find(index, value);
				break;
			case chainType:
				bRet = chain.Find(index, value);
				break;
			case circularChainType:
				bRet = circularChain.Find(index, value);
				break;
			case dcChainType:
				bRet = dcChain.Find(index, value);
				break;
			default:
				bRet = false;
				break;
			}
			if (!bRet)
			{
				cout << "Not Find!" << endl << endl;
			}
			else
			{
                cout << "The value of index " + to_string(index) + " is: " + to_string(value) << endl;
			}
		}
		else if (strCmd == "search")
		{
			cout << "Please enter the value:" << endl;
			getline(cin, strVal);
			ss.clear();
			ss << strVal;
			ss >> value;
			switch (st)
			{
			case sequenceType:
				bRet = sequence.Search(value, index);
				break;
			case chainType:
				bRet = chain.Search(value, chainNode);
				break;
			case circularChainType:
				bRet = circularChain.Search(value, circularChainNode);
				break;
			case dcChainType:
				bRet = dcChain.Search(value, dcChainNode);
				break;
			default:
				bRet = false;
				break;
			}
			
            if(!bRet)
			{
				cout << "Not Find!" << endl << endl;
			}
			else
			{
				cout << "Find!" << endl;
				if (st == sequenceType)
				{
					cout << "Index is " + to_string(index) << endl << endl;
				}
			}
		}
		else if (strCmd == "is empty")
		{
		    switch (st)
		    {
		    case sequenceType:
		    	bRet = sequence.IsEmpty();
		    	break;
		    case chainType:
				bRet = chain.IsEmpty();
		    	break;
		    case circularChainType:
				bRet = circularChain.IsEmpty();
		    	break;
		    case dcChainType:
				bRet = dcChain.IsEmpty();
		    	break;
		    default:
				bRet = true;
		    	break;
		    }
			if (bRet)
			{
				cout << "Empty!" << endl;
			}
			else
			{
				cout << "Not Empty!" << endl;
			}
		}
		else if (strCmd == "length")
		{
		    switch (st)
		    {
		    case sequenceType:
		    	length = sequence.Length();
		    	break;
		    case chainType:
				length = chain.Length();
		    	break;
		    case circularChainType:
				length = circularChain.Length();
		    	break;
		    case dcChainType:
				length = dcChain.Length();
		    	break;
		    default:
				length = 0;
		    	break;
		    }
		    cout << "The length is " + to_string(length) << endl;
		}
		else if (strCmd == "erase")
		{
		    switch (st)
		    {
		    case sequenceType:
		    	sequence.Erase();
		    	break;
		    case chainType:
		    	chain.Erase();
		    	break;
		    case circularChainType:
		    	circularChain.Erase();
		    	break;
		    case dcChainType:
		    	dcChain.Erase();
		    	break;
		    default:

		    	break;
		    }
		}
		else if (strCmd == "copy")
		{
			switch (st)
			{
			case sequenceType:
			{
                Sequence<int> sequence_copy(sequence);
				cout << "Values in the sequence_copy:" << endl << endl;
				sequence_copy.Output(cout);
				break;
			}
			case chainType:
			{
                Chain<int> chain_copy(chain);
				cout << "Values in the chain_copy:" << endl << endl;
				chain_copy.Output(cout);
				break;
			}	
			case circularChainType:
			{
                CircularChain<int> circularChain_copy(circularChain);
				cout << "Values in the circularChain_copy:" << endl << endl;
				circularChain_copy.Output(cout);
                break;
			}	
			case dcChainType:
			{
                DCChain<int> dcChain_copy(dcChain);
				cout << "Values in the dcChain_copy:" << endl << endl;
				dcChain_copy.Output(cout);
				break;
			}
			default:

				break;
		    }
        }
		else if (strCmd == "back")
		{
		    break;
		}
		else
		{
		    cout << "Bad Command!" << endl << endl;
        }

		switch (st)
		{
		case sequenceType:
			cout << "Values in the Sequence:" << endl << endl;
			sequence.Output(cout);
			break;
		case chainType:
			cout << "Values in the Chain:" << endl << endl;
			chain.Output(cout);
			break;
		case circularChainType:
			cout << "Values in the CircularChain:" << endl << endl;
			circularChain.Output(cout);
			break;
		case dcChainType:
			cout << "Values in the DoublyChain:" << endl << endl;
			dcChain.Output(cout);
			break;
		default:
			break;
		}
		
	}
}

void TestMemAlloc(structType st)
{
	int index;
    string strCmd;
	while (true)
	{
		FreeList<int> freeList;
		SimSpace<int> simSpace;
		cout << "Please enter the command:" << endl;
		getline(cin, strCmd);
		if (strCmd == "alloc")
		{
			try
			{
				switch (st)
				{
				case freeListType:
					freeList.Allocate();
					break;
				case simSpaceType:
					simSpace.Allocate();
					break;
				default:
					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
		}
		else if (strCmd == "dealloc")
		{
			try
			{
				switch (st)
				{
				case freeListType:
					//freeList.Deallocate();
					break;
				case simSpaceType:
					//simSpace.Deallocate();
					break;
				default:
					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
		}
		else if (strCmd == "back")
		{
			break;
		}
		else
		{
			cout << "Bad Command!" << endl;
		}
	}
}

void TestQueue(structType st)
{
	CircularQueue<int> circularQueue;
	QueueChain<int> queueChain;
	string strVal, strCmd;
	stringstream ss;
	int value;
	bool bRet = false;
	while (true)
	{
		cout << "Please enter the command:" << endl;
		getline(cin, strCmd);
		if (strCmd == "is empty")
		{
			switch (st)
			{
			case circularQueueType:
				bRet = circularQueue.IsEmpty();
				break;
			case queueChainType:
				bRet = queueChain.IsEmpty();
				break;
			default:
				bRet = false;
				break;
			}
			if (bRet)
				cout << "The queue is empty" << endl;
			else
				cout << "The queue is not empty" << endl;
		}
		else if (strCmd == "is full")
		{
			switch (st)
			{
			case circularQueueType:
				bRet = circularQueue.IsFull();
				break;
			case queueChainType:
				bRet = queueChain.IsFull();
				break;
			default:
				bRet = false;
				break;
			}
			if(bRet)
			    cout << "The queue is full" << endl;
			else
				cout << "The queue is not full" << endl;
		}
		else if (strCmd == "enqueue")
		{
			cout << "Please enter the value:" << endl;
			getline(cin, strVal);
			ss.clear();
			ss << strVal;
			ss >> value;
			try
			{
				switch (st)
				{
				case circularQueueType:
					circularQueue.EnQueue(value);
					break;
				case queueChainType:
					queueChain.EnQueue(value);
					break;
				default:

					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
		}
		else if (strCmd == "dequeue")
		{
			try
			{
				switch (st)
				{
				case circularQueueType:
					circularQueue.DeQueue(value);
					break;
				case queueChainType:
					queueChain.DeQueue(value);
					break;
				default:

					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
			cout << "Dequeue value is " + to_string(value) << endl;
		}
		else if (strCmd == "erase")
		{
		    switch (st)
		    {
		    case circularQueueType:
				circularQueue.Erase();
		    	break;
		    case queueChainType:
				queueChain.Erase();
		    	break;
		    default:
		    
		    	break;
		    }
		}
		else if (strCmd == "copy")
		{
			switch (st)
			{
			case circularQueueType:
			{
				CircularQueue<int> circularQueue_copy(circularQueue);
				cout << "Values in the circularQueue_copy:" << endl << endl;
				circularQueue_copy.Output(cout);
				break;
			}
			case queueChainType:
			{
				QueueChain<int> queueChain_copy(queueChain);
				cout << "Values in the queueChain_copy:" << endl << endl;
				queueChain_copy.Output(cout);
				break;
			}
			default:

				break;
			}
		}
		else if (strCmd == "back")
		{
		    break;
		}
		else
		{
		    cout << "Bad Command!" << endl << endl;
		}

		switch (st)
		{
		case circularQueueType:
			cout << "Values in the Circular Queue:" << endl << endl;
			circularQueue.Output(cout);
			break;
		case queueChainType:
			cout << "Values in the Queue Chain:" << endl << endl;
			queueChain.Output(cout);
			break;
		default:
			break;
		}

	}
}

void TestStack(structType st)
{
	StackSequence<int> stackSequence;
	StackChain<int> stackChain;
	DoubleStack<int> doubleStack;
	string strVal, strCmd, strStackNum;
	stringstream ss;
	int value, stackNum;
	bool bRet = false;
	while (true)
	{
		cout << "Please enter the command:" << endl;
		getline(cin, strCmd);
		if (strCmd == "is empty")
		{
			switch (st)
			{
			case stackSequenceType:
				bRet = stackSequence.IsEmpty();
				break;
			case stackChainType:
				bRet = stackChain.IsEmpty();
				break;
			case doubleStackType:
				bRet = doubleStack.IsEmpty();
				break;
			default:
				bRet = false;
				break;
			}
			if (bRet)
				cout << "The stack is empty" << endl;
			else
				cout << "The stack is not empty" << endl;
		}
		else if (strCmd == "is full")
		{
			switch (st)
			{
			case stackSequenceType:
				bRet = stackSequence.IsFull();
				break;
			case stackChainType:
				bRet = stackChain.IsFull();
				break;
			case doubleStackType:
				bRet = doubleStack.IsFull();
				break;
			default:
				bRet = false;
				break;
			}
			if (bRet)
				cout << "The stack is full" << endl;
			else
				cout << "The stack is not full" << endl;
		}
		else if (strCmd == "push")
		{
			cout << "Please enter the value:" << endl;
			getline(cin, strVal);
			ss.clear();
			ss << strVal;
			ss >> value;
			try
			{
				switch (st)
				{
				case stackSequenceType:
					stackSequence.Push(value);
					break;
				case stackChainType:
					stackChain.Push(value);
					break;
				case doubleStackType:
					cout << "Please enter the stack number:" << endl;
					getline(cin, strStackNum);
					ss.clear();
					ss << strStackNum;
					ss >> stackNum;
					if (stackNum != 1 && stackNum != 2)
					{
						cout << "Wrong stack number!" << endl;
						break;
					}	
					doubleStack.Push(value, stackNum);
					break;
				default:

					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
		}
		else if (strCmd == "pop")
		{
			try
			{
				switch (st)
				{
				case stackSequenceType:
					stackSequence.Pop(value);
					break;
				case stackChainType:
					stackChain.Pop(value);
					break;
				case doubleStackType:
					cout << "Please enter the stack number:" << endl;
					getline(cin, strStackNum);
					ss.clear();
					ss << strStackNum;
					ss >> stackNum;
					if (stackNum != 1 && stackNum != 2)
					{
						cout << "Wrong stack number!" << endl;
						break;
					}
					doubleStack.Pop(value, stackNum);
					break;
				default:

					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
			cout << "Pop value is " + to_string(value) << endl;
		}
		else if (strCmd == "erase")
		{
		    switch (st)
		    {
		    case stackSequenceType:
				stackSequence.Erase();
		    	break;
		    case stackChainType:
				stackChain.Erase();
		    	break;
			case doubleStackType:
				cout << "Please enter the stack number:" << endl;
				getline(cin, strStackNum);
				ss.clear();
				ss << strStackNum;
				ss >> stackNum;
				if (stackNum != 1 && stackNum != 2)
				{
					cout << "Wrong stack number!" << endl;
					break;
				}
				doubleStack.Erase(stackNum);
				break;
		    default:
		    
		    	break;
		    }
		}
		else if (strCmd == "copy")
		{
			switch (st)
			{
			case stackSequenceType:
			{
				StackSequence<int> stackSequence_copy(stackSequence);
				cout << "Values in the stackSequence_copy:" << endl << endl;
				stackSequence_copy.Output(cout);
				break;
			}
			case stackChainType:
			{
				StackChain<int> stackChain_copy(stackChain);
				cout << "Values in the stackChain_copy:" << endl << endl;
				stackChain_copy.Output(cout);
				break;
			}
			case doubleStackType:
			{
				DoubleStack<int> doubleStack_copy(doubleStack);
				cout << "Values in the doubleStack_copy1:" << endl << endl;
				doubleStack_copy.Output(cout, 1);
				cout << "Values in the doubleStack_copy2:" << endl << endl;
				doubleStack_copy.Output(cout, 2);
				break;
			}
			default:

				break;
			}
		}
		else if (strCmd == "back")
		{
		    break;
		}
		else
		{
		    cout << "Bad Command!" << endl << endl;
		}

		switch (st)
		{
		case stackSequenceType:
			cout << "Values in the Stack Sequence:" << endl << endl;
			stackSequence.Output(cout);
			break;
		case stackChainType:
			cout << "Values in the Stack Chain:" << endl << endl;
			stackChain.Output(cout);
			break;
		case doubleStackType:
			cout << "Values in the Stack1:" << endl << endl;
			doubleStack.Output(cout, 1);
			cout << "Values in the Stack2:" << endl << endl;
			doubleStack.Output(cout, 2);
		default:
			break;
		}

	}
}

void TestDictionary(structType st)
{
	SortedList<int, int> sortedList;
	SortedChain<int, int> sortedChain;
	SortedChainNode<int, int>* sortedChainNode = new SortedChainNode<int, int>();
	SkipList<int, int> skipList;
	SkipNode<int, int>* skipNode = new SkipNode<int, int>(10);;
	HashTable<int, int> hashTable;
	ChainHashTable<int, int> chainHashTable;
	string strKey, strVal, strCmd;
	stringstream ss;
	int key, value, length, index;
	bool bRet = false;
	while (true)
	{
		cout << "Please enter the command:" << endl;
		getline(cin, strCmd);
		if (strCmd == "insert")
		{
			cout << "Please enter the key:" << endl;
			getline(cin, strKey);
			ss.clear();
			ss << strKey;
			ss >> key;
			cout << "Please enter the value:" << endl;
			getline(cin, strVal);
			ss.clear();
			ss << strVal;
			ss >> value;
			try
			{
				switch (st)
				{
				case sortedListType:
					sortedList.Insert(key, value);
					break;
				case sortedChainType:
					sortedChain.Insert(key, value);
					break;
				case skipListType:
					skipList.Insert(key, value);
					break;
				case hashTableType:
					hashTable.Insert(key, value);
					break;
				case chainHashTableType:
					chainHashTable.Insert(key, value);
					break;
				default:
					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
		}
		else if (strCmd == "delete")
		{
			cout << "Please enter the key:" << endl;
			getline(cin, strKey);
			ss.clear();
			ss << strKey;
			ss >> key;
			try
			{
				switch (st)
				{
				case sortedListType:
					sortedList.Delete(key, value);
					break;
				case sortedChainType:
					sortedChain.Delete(key, value);
					break;
				case skipListType:
					skipList.Delete(key, value);
					break;
				case hashTableType:
					hashTable.Delete(key, value);
					break;
				case chainHashTableType:
					chainHashTable.Delete(key, value);
					break;
				default:
					break;
				}
			}
			catch (OutOfBounds outOfBounds)
			{
				cout << "Out of Bounds!" << endl << endl;
			}
			catch (NoMem noMem)
			{
				cout << "No Memory!" << endl << endl;
			}
			catch (BadInput badInput)
			{
				cout << "Bad Input!" << endl << endl;
			}
			catch (BadCall badCall)
			{
				cout << "Bad Call!" << endl << endl;
			}
			cout << "Delete value is: " + to_string(value) << endl;
		}
		else if (strCmd == "find")
		{
			cout << "Please enter the key:" << endl;
			getline(cin, strKey);
			ss.clear();
			ss << strKey;
			ss >> key;
			switch (st)
			{
			case sortedListType:
				cout << "Wrong Command!" << endl << endl;
				break;
			case sortedChainType:
				cout << "Wrong Command!" << endl << endl;
				break;
			case skipListType:
				cout << "Wrong Command!" << endl << endl;
				break;
			case hashTableType:
				bRet = hashTable.Find(key, value);
				if (bRet)
				{
					cout << "The value is: " + to_string(value) << endl;
				}  
				else
				{
					cout << "Not Find!" << endl << endl;
				}
				break;
			case chainHashTableType:
				bRet = chainHashTable.Find(key, value);
				if (bRet)
				{
					cout << "The value is: " + to_string(value) << endl;
				}
				else
				{
					cout << "Not Find!" << endl << endl;
				}
				break;
			default:
				break;
			}
		}
		else if (strCmd == "search")
		{
			cout << "Please enter the key:" << endl;
			getline(cin, strKey);
			ss.clear();
			ss << strKey;
			ss >> key;
			switch (st)
			{
			case sortedListType:
				bRet = sortedList.Search(key, value, index);
				
				if (bRet)
				{
					cout << "Find! The value and index is : " + to_string(value) + " and " + to_string(index) << endl;
				}
				else
				{
					cout << "Not Find!" << endl << endl;
				}
				break;
			case sortedChainType:
				bRet = sortedChain.Search(key, sortedChainNode);
				if (bRet)
				{
					cout << "Find!" << endl;
				}
				else
				{
					cout << "Not Find!" << endl << endl;
				}
				break;
			case skipListType:
				bRet = skipList.Search(key, skipNode);
				if (bRet)
				{
					cout << "Find!" << endl;
				}
				else
				{
					cout << "Not Find!" << endl << endl;
				}
				break;
			case hashTableType:
				cout << "Wrong Command!" << endl << endl;
				break;
			case chainHashTableType:
				cout << "Wrong Command!" << endl << endl;
				break;
			default:
				break;
			}
		}
		else if (strCmd == "is empty")
		{
			switch (st)
			{
			case sortedListType:
				bRet = sortedList.IsEmpty();
				break;
			case sortedChainType:
				bRet = sortedChain.IsEmpty();
				break;
			case skipListType:
				bRet = skipList.IsEmpty();
				break;
			case hashTableType:
				bRet = hashTable.IsEmpty();
				break;
			case chainHashTableType:
				bRet = chainHashTable.IsEmpty();
				break;
			default:
				break;
			}
			if (bRet)
			{
				cout << "Empty!" << endl;
			}
			else
			{
				cout << "Not Empty!" << endl;
			}
		}
		else if (strCmd == "length")
		{
			switch (st)
			{
			case sortedListType:
				length = sortedList.Length();
				break;
			case sortedChainType:
				length = sortedChain.Length();
				break;
			case skipListType:
				length = skipList.Length();
				break;
			case hashTableType:
				length = hashTable.Length();
				break;
			case chainHashTableType:
				length = chainHashTable.Length();
				break;
			default:
				break;
			}
			cout << "The length is " + to_string(length) << endl;
		}
		else if (strCmd == "erase")
		{
			switch (st)
			{
			case sortedListType:
				sortedList.Erase();
				break;
			case sortedChainType:
				sortedChain.Erase();
				break;
			case skipListType:
				skipList.Erase();
				break;
			case hashTableType:
				hashTable.Erase();
				break;
			case chainHashTableType:
				chainHashTable.Erase();
				break;
			default:
				break;
			}
		}
		else if (strCmd == "copy")
		{
			switch (st)
			{	
			case sortedListType:
			{
				SortedList<int, int> sortedList_copy(sortedList);
				cout << "Values in the sortedList_copy:" << endl << endl;
				sortedList_copy.Output(cout);
				break;
			}
			case sortedChainType:
			{
				SortedChain<int, int> sortedChain_copy(sortedChain);
				cout << "Values in the sortedChain_copy:" << endl << endl;
				sortedChain_copy.Output(cout);
				break;
			}
			case skipListType:
			{
				SkipList<int, int> skipList_copy(skipList);
				cout << "Values in the skipList_copy:" << endl << endl;
				skipList_copy.Output(cout);
				break;
			}
			case hashTableType:
			{
				HashTable<int, int> hashTable_copy(hashTable);
				cout << "Values in the hashTable_copy:" << endl << endl;
				hashTable_copy.Output(cout);
				break;
			}
			case chainHashTableType:
			{
				ChainHashTable<int, int> chainHashTable_copy(chainHashTable);
				cout << "Values in the chainHashTable_copy:" << endl << endl;
				chainHashTable_copy.Output(cout);
				break;
			}
			default:

				break;
			}
		}
		else if (strCmd == "back")
		{
		    break;
        }
		else
		{
		    cout << "Bad Command!" << endl << endl;
		}

		switch (st)
		{
		case sortedListType:
			cout << "Values in the Sorted List:" << endl << endl;
			sortedList.Output(cout);
			break;
		case sortedChainType:
			cout << "Values in the Sorted Chain:" << endl << endl;
			sortedChain.Output(cout);
			break;
		case skipListType:
			cout << "Values in the Skip List:" << endl << endl;
			skipList.Output(cout);
			break;
		case hashTableType:
			cout << "Values in the Hash Table" << endl << endl;
			hashTable.Output(cout);
			break;
		case chainHashTableType:
			cout << "Values in the Chain Hash Table:" << endl << endl;
			chainHashTable.Output(cout);
			break;
		default:
			break;
		}

	}

}

bool StringToArr(const string& strVals, int* arrVals)
{
	int k = 1;
	int val = 0;
	int j = 1;//数组下标从1开始
	for (int i = strVals.length() - 1; i >= 0; i--)
	{
		if (',' == strVals[i])
		{
			arrVals[j++] = val;
			k = 1;
			val = 0;
		}
		else if(strVals[i] >= 48 && strVals[i] <= 57)
		{
			int tempVal = (int)(strVals[i] - 48);
			val += k * tempVal;
			k *= 10;
		}
		else
		{
			return false;
		}
	}
	arrVals[j++] = val;
	return true;
}

void TestMaxHeap()
{
	MaxHeap<int> maxHeap;
	int values[11] = { 0 };
	string strValues, strCmd;
	int val = 0;
	while (true)
	{
		strCmd.clear();
		strValues.clear();
		for (int i = 0; i < 11; i++)
		{
			values[i] = 0;
		}
		maxHeap.Erase();
		cout << "Please enter the command:" << endl;
		getline(cin, strCmd);
		if (strCmd == "sort")
		{
			//目前只能输入正整数
			cout << "Please enter the values, separated by commas:" << endl;
			getline(cin, strValues);
			if (!StringToArr(strValues, values))
			{
				cout << "Values wrong! Please enter again!" << endl;
				continue;
			}
			maxHeap.Initialize(values, 10);
			cout << "Values from big to small: ";
			while (maxHeap.Length() > 0)
			{
				maxHeap.DeleteMax(val);
				cout << val << " ";
			}
			cout << endl;
		}
		else if (strCmd == "copy")
		{
			//目前只能输入正整数
			cout << "Please enter the values, separated by commas:" << endl;
			getline(cin, strValues);
			if (!StringToArr(strValues, values))
			{
				cout << "Values wrong! Please enter again!" << endl;
				continue;
			}
			maxHeap.Initialize(values, 10);
			MaxHeap<int> maxHeap_copy(maxHeap);
		    cout << "Values in the maxHeap_copy:" << endl << endl;
			maxHeap_copy.Output(cout);
		}
		else if (strCmd == "back")
		{
			break;
		}
		else
		{
			cout << "Bad Command!" << endl << endl;
		}

	}
}

void TestJstring()
{
	Jstring jstrVal(NULL), jstrCmd(NULL), jstr1(NULL), jstr2(NULL);
	while (true)
	{
		Jstring jsOutput("Please enter the command:");
		cout << jsOutput << endl;
		cin >> jstrCmd;
		if (jstrCmd == "input")
		{
			jsOutput = "Please enter the string:";
			cout << jsOutput << endl;
			cin >> jstrVal;//不能有空格
		}
		else if (jstrCmd == "output")
		{
			jsOutput = "Output jstrVal:";
			cout << jsOutput << endl;
			cout << jstrVal << endl;
		}
		else if (jstrCmd == "compare")
		{
			jsOutput = "Please enter string1:";
			cout << jsOutput << endl;
			cin >> jstr1;//不能有空格
			jsOutput = "Please enter string2:";
			cout << jsOutput << endl;
			cin >> jstr2;//不能有空格
			if (jstr1 == jstr2)
			{
				jsOutput = "jstr1 == jstr2";
				cout << jsOutput << endl;
			}
			else if (jstr1 > jstr2)
			{
				jsOutput = "jstr1 > jstr2";
				cout << jsOutput << endl;
			}
			else if(jstr1 < jstr2)
			{
				jsOutput = "jstr1 < jstr2";
				cout << jsOutput << endl;
			}
			else
			{

			}
		}
		else if (jstrCmd == "connect")
		{
			jsOutput = "Please enter string1:";
			cout << jsOutput << endl;
			cin >> jstr1;//不能有空格
			jsOutput = "Please enter string2:";
			cout << jsOutput << endl;
			cin >> jstr2;//不能有空格
			Jstring jstr = jstr1 + jstr2;
			jsOutput = "Connected string is:";
			cout << jsOutput << endl;
			cout << jstr << endl;
		}
		else if (jstrCmd == "back")
		{
			break;
		}
		else
		{
			cout << "Bad Command!" << endl << endl;
		}
	}
}

void TestSequence()
{
	TestLinList(sequenceType);
}

void TestChain()
{
	TestLinList(chainType);
}

void TestCircularChain()
{
	TestLinList(circularChainType);
}

void TestDCChain()
{
	TestLinList(dcChainType);
}

void TestCircularQueue()
{
	TestQueue(circularQueueType);
}

void TestQueueChain()
{
	TestQueue(queueChainType);
}

void TestStackSequence()
{
	TestStack(stackSequenceType);
}

void TestStackChain()
{
	TestStack(stackChainType);
}

void TestDoubleStack()
{
	TestStack(doubleStackType);
}

void TestSortedList()
{
	TestDictionary(sortedListType);
}

void TestSortedChain()
{
	TestDictionary(sortedChainType);
}

void TestSkipList()
{
	TestDictionary(skipListType);
}

void TestHashTable()
{
	TestDictionary(hashTableType);
}

void TestChainHashTable()
{
	TestDictionary(chainHashTableType);
}

void TestFreeList()
{
	TestMemAlloc(freeListType);
}

void TestSimSpace()
{
	TestMemAlloc(simSpaceType);
}

int main()
{
	while (true)
	{
		cout << "Please enter the struct name:" << endl;
		string strName;
		getline(cin, strName);
		if (strName == "sequence")
		{
		    TestSequence();
		}
		else if (strName == "chain")
		{
		    TestChain();
        }
		else if (strName == "circular chain")
		{
			TestCircularChain();
		}
		else if (strName == "dc chain")
		{
			TestDCChain();
		}
		else if (strName == "circular queue")
		{
			TestCircularQueue();
		}
		else if (strName == "queue chain")
		{
			TestQueueChain();
		}
		else if (strName == "stack sequence")
		{
			TestStackSequence();
		}
		else if (strName == "stack chain")
		{
			TestStackChain();
		}
		else if (strName == "double stack")
		{
			TestDoubleStack();
		}
		else if (strName == "sorted list")
		{
			TestSortedList();
		}
		else if (strName == "sorted chain")
		{
			TestSortedChain();
		}
		else if (strName == "skip list")
		{
			TestSkipList();
		}
		else if (strName == "hash table")
		{
			TestHashTable();
		}
		else if (strName == "chain hash table")
		{
			TestChainHashTable();
		}
		else if (strName == "max heap")
		{
			TestMaxHeap();
		}
		else if (strName == "jstring")
		{
			TestJstring();
		}
		else
		{
			cout << "Struct Name Wrong!" << endl;
		}
	}
}