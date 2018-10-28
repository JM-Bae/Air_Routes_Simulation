// CS_302 Section 1001
// Assignment 11
// Junho Bae
// Due: 04-25-17
// priorityQueue header/implementation file (template class)
// Description: Creates a priority Queue data structure 

#ifndef priorityQueue_h
#define priorityQueue_h

// includes and prototypes
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
namespace pQue
{	
	class priorityQueue
	{
	public:
		// constructor
		priorityQueue()
		{
			myHeap = new heapNode[initialSize];
		};				
		~priorityQueue();	// destructor
		void insert(const int, const int); // inserts an element into the heap
		bool deleteMin(int &, int &); // removes an element in the heap
		
		// returns true if heap is empty
		bool isEmpty() const 
		{
			if(count == 0)
				return true;
			else 
				return false;
		};

	private:
		void reheapUp(int);			// maintains order property (botton->top)
		void reheapDown(int);			// maintains order property (top->bottom)

		// sub data structure to store elements for the heap
		struct heapNode
		{
			int priority;
			int item;
		};
		heapNode tmp;
		int count;					// # of elements in the heap
		static constexpr unsigned int initialSize = 5000;
		heapNode *myHeap;			// pointer to the heap

	};

// Function Implementation -----------------------------------------------------

priorityQueue::~priorityQueue()
// destructor, deallocates heap memory
{
	delete [] myHeap;
	myHeap = NULL;
}

void priorityQueue::insert(const int name, const int rank)
// inserts item and priority into the heap data structure
// parameters: priority & item to be inserted
{
	int exists = 0;
	for(int i=0; i<count; i++)
		if(myHeap[i].item == name)
			exists = i;
	if(exists != 0)
		myHeap[exists].priority = rank;
	else
	{
		count++;
		myHeap[count].priority = rank;
		myHeap[count].item = name;

		// maintains order property
		reheapUp(count);		
	}
}

bool priorityQueue::deleteMin(int &name, int &rank)
// removes an elements from the heap
// returns the item and priority of deleted node via reference
// if successful, return true; else false
// parameters: variables to return item & priority via reference
{
	if(count == 0)
		return false;
	name = myHeap[1].item;
	rank = myHeap[1].priority;

	// replaces orphaned element to the top
	myHeap[1].priority = myHeap[count].priority;
	myHeap[1].item = myHeap[count].item;
	count--;
	// maintains order property
	reheapDown(1);
	return true;
}

// Private Functions -----------------------------------------------------------

void priorityQueue::reheapUp(int last)
// recursively ensures the heap order property is maintained. 
// starts at tree leaf and worsk up to root
// parameters: the leaf node to start
{
	int parent, lchild, rchild;

	if(last > 1)
	{
		parent = last/2;
		lchild = parent * 2;
		rchild = parent*2 + 1;

		if(myHeap[last].priority < myHeap[parent].priority)
		{
			if(rchild <= count)
			{
				if(myHeap[rchild].priority < myHeap[lchild].priority)
				{
					tmp = myHeap[parent];
					myHeap[parent] = myHeap[rchild];
					myHeap[rchild] = tmp;
				}
				else
				{
					tmp = myHeap[parent];
					myHeap[parent] = myHeap[lchild];
					myHeap[lchild] = tmp;
				}
				reheapUp(parent);
			}
			else
			{
				tmp = myHeap[parent];
				myHeap[parent] = myHeap[lchild];
				myHeap[lchild] = tmp;
				reheapUp(parent);
			}	
		}
	}
}

void priorityQueue::reheapDown(int parent)
// recursively ensures the heap order property is maintained.
// starts at the passed node and works down to the applicable leaf.
// parameters: the node to start
{
	int lchild, rchild;
	lchild = parent*2;
	rchild = parent*2 + 1;

	// checks if both children nodes exists
	if(rchild <= count)
	{	
		// if either children values are less than parent's, update heap
		if((myHeap[lchild].priority < myHeap[parent].priority) && (myHeap[rchild].priority < myHeap[parent].priority))
		{
			if(myHeap[rchild].priority < myHeap[lchild].priority)
			{
				tmp = myHeap[rchild];
				myHeap[rchild] = myHeap[parent];
				myHeap[parent] = tmp;
				reheapDown(rchild);
			}
			else // if right child is less than left child, bring right child up
			{
				tmp = myHeap[lchild];
				myHeap[lchild] = myHeap[parent];
				myHeap[parent] = tmp;
				reheapDown(lchild);
			}
		}
		else if(myHeap[lchild].priority < myHeap[parent].priority)
		{
			tmp = myHeap[lchild];
			myHeap[lchild] = myHeap[parent];
			myHeap[parent] = tmp;
			reheapDown(lchild);
		}
		else if(myHeap[rchild].priority < myHeap[parent].priority)
		{
			tmp = myHeap[rchild];
			myHeap[rchild] = myHeap[parent];
			myHeap[parent] = tmp;
			reheapDown(rchild);
		}
	}
	else if(lchild <= count) // if only left child exists, update
	{	
		// if left child is less than parent, swap
		if(myHeap[lchild].priority < myHeap[parent].priority)
		{
			tmp = myHeap[lchild];
			myHeap[lchild] = myHeap[parent];
			myHeap[parent] = tmp;
			reheapDown(lchild);			
		}
	// if neither children exists, exit
	}
}

}
#endif // priorityQueue_h