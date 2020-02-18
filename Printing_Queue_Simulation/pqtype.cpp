// Implementation of priority queue
// Header file pqtype.cpp
// Project Priority for Printer Queue
#include "pqtype.h"
#include "printjob.h"
#include <iostream>
#include <string>
using namespace std;
// Constructor to dynamically allocate an array of ItemType w/ size max
template< class ItemType>
PQType< ItemType >::PQType(int max) {
	maxItem = max;							// save value of max number of items
	items.elements = new ItemType[maxItem]; // dynamically allocate
	length = 0;								// and set its length = 0
}
// Copy constructor of PQType to create a new one
template< class ItemType >
PQType< ItemType >::PQType(const PQType& original) {
	maxItem = original.maxItem;				// copy value of max number of items			
	items.elements = new ItemType[maxItem];	// dynamically allocate for new PQType
	length = original.length;				// copy value of length	
	for (int i = 0; i < length; i++)		// copy value of items to new PQType
		items.elements[i] = original.items.elements[i];
}
// Destructor to deallocate PQType
template< class ItemType >
PQType< ItemType >::~PQType() { delete [] items.elements; }
// Function to return true if PQType is empty, false otherwise
template< class ItemType >
bool PQType< ItemType >::isEmpty() const { return !length; }
// Function to return true if PQType is full, false otherwise
template< class ItemType >
bool PQType< ItemType >::isFull() const { return length == maxItem; }
// Function to remove the root then restore the order property of PQType
template< class ItemType >
void PQType< ItemType >::Dequeue(ItemType &item) {
	// Throw an exception if PQType is empty
	if (!length) throw string("ERROR: Empty queue! Cannot perfom dequeue.");
	else {
		item = items.elements[0];			// save value of root in item returned in main()
		// Copy value of last node to root, then reduce the queue's length by 1
		items.elements[0] = items.elements[--length];
		items.ReheapDown(0, length - 1);		// restore its order property
	}
}
// Function to add a node with a value to PQType then restore its order property
template< class ItemType>
void PQType< ItemType >::Enqueue(ItemType newItem) {
	// Throw an exception if PQType is full
	if (length == maxItem) throw string("ERROR: Full queue! Cannot perfom enqueue.");
	else {
		// Add one node to PQType then copy the new value to that node
		length++; items.elements[length - 1] = newItem;
		items.ReheapUp(0, length - 1);		// restore its order property
	}	
}
// Print out all elements in priority queue in order
template< class ItemType>
void PQType< ItemType >::Print() {
	while (length > 0) {
		cout << items.elements[0]; 			// print out value of root
		// Copy value of last node to root, then reduce length by 1
        items.elements[0] = items.elements[--length];
		items.ReheapDown(0, length - 1);	// restore the order property of PQType
	}
}
