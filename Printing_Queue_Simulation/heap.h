// Implementation of heap
// Header file heap.h
// Project Priority for Printer Queue
#ifndef HEAP_H_
#define HEAP_H_
// Define a generic type ItemType as a template for Swap function
template< class ItemType >
void Swap(ItemType& a, ItemType& b);	// swap two items with a generic type
// Define a generic type ItemType as a template for Struct HeapType
template< class ItemType >
// Define struct heap
struct HeapType { 
	ItemType*	elements;		// dynamically-allocated array of heap elements
	int			numElements;	// total number of heap elements (in the array)
	// Functions to restore the order property to the heap between root and bottom
	void ReheapDown(int root, int bottom);		// Used in removal of a root
	void ReheapUp(int root, int bottom);		// Used in addition of an element
};
#endif /* HEAP_H */
#pragma once
