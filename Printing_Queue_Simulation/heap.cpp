// Implementation of heap
// Header file heap.cpp
// Project Priority for Printer Queue
#include "heap.h"
#include "printjob.h"
#include <iostream>
using namespace std;
// Description of Swap function
template < class ItemType >
void Swap(ItemType &a, ItemType &b) { ItemType temp = a; a = b; b = temp; }
		// Description of ReheapUp and Reheapdown functions //
// Restore the order property to the heap from bottom up to root
template< class ItemType >
void HeapType< ItemType >::ReheapUp(int root, int bottom) {
	// Construct index of a parent node
	int parent;
	// If bottom's index of a subtree > root's index
	if (bottom > root) {
		parent = (bottom - 1) / 2;	// determine parent's index of bottom node
		// Swap then reheap up if value in parent node < value in its child
		if (elements[bottom] > elements[parent]) {
			// Swap values in parent and its child
			Swap(elements[parent], elements[bottom]);
			// Recursively reheap up from bottom of a subtree to a new parent
			ReheapUp(root, parent);
		}
	}
}
// Restore order property of a heap from root down to bottom
template< class ItemType >
void HeapType< ItemType >::ReheapDown(int root, int bottom) {
	// Construct index of left child and right child node
	int maxChild, rightChild = 2 * root + 2, leftChild = 2 * root + 1;
	if (leftChild <= bottom) {
		// Set maxChild to the index of the greater value in the children's nodes
		maxChild = leftChild == bottom ? leftChild :	// if there only one child
			// If there are both children and elements[leftChild] < elements[rightChild]
			// OR if there are both children and elements[leftChild] > elements[rightChild]
			elements[rightChild] > elements[leftChild] ? rightChild : leftChild;
		// Swap then reheap down if value in root node < value in its child
		if (elements[maxChild] > elements[root]) {
			// Swap values in root and maxChild
			Swap(elements[root], elements[maxChild]);
			// Recursively reheap down from root of a subtree to a new bottom
			ReheapDown(maxChild, bottom);
		}
	}
}
