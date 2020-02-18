// Implementation of priority queue
// Header file pqtype.h
// Project Priority for Printer Queue
#ifndef PQTYPE_H_
#define PQTYPE_H_
#include "heap.h"
template < class ItemType >
class PQType {
private:
	int length;					// length of PQType
	HeapType< ItemType > items;	// items of PQType is defined as HeapType< ItemType >
	int maxItem;				// largest number of items in PQType
public:
	PQType(int);				// initialized constructor
	PQType(const PQType&);		// copy constructor
	~PQType();					// destructor	
	bool isEmpty() const;		// return true if PQType is empty, false otherwise
	bool isFull() const;		// return true if PQType is full, false otherwise
	void Enqueue(ItemType);		// add an item to PQType and maintain order
	void Dequeue(ItemType&);	// remove an item to PQType and maintain order
	void Print();				// print all items in PQType
};
#endif /* PQTYPE_H */
#pragma once
