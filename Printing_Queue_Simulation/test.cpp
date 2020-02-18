// Implementation of driver program for print job queue
// test.cpp
// Designed by Tuan Nguyen
// Project Priority for Printer Queue
/*********************************************************************************************************
* This program demonstrates the applications of priority queue implementation in a print job simulation. *
* The program performs a simulation of adding a print job to a priority queue.                           *
* It performs a simulation of removing a print job out of the queue in priority order.                   *
* The programs can print out a list of current print jobs on queue in priority order for users' review.  *
 ********************************************************************************************************/
#include "heap.cpp"
#include "pqtype.cpp"
#include "printjob.h"
#include <iostream>
#include <string>
using namespace std;
int main() {
	// The last print jod number added into the priority queue
	int lastJob;
	// Declare a variable to hold user input for menu option
	char option;
	// Create a priority queue of 1000 PrintJobs
	PQType< PrintJob >  pQueue(1000);
	// Keep displaying the menu options and execute each of user's choice until
	// the user no longer enters either 1 or 2 or 3
	do {
		if (pQueue.isEmpty()) lastJob = 0; // reset print job order when the queue is empty
		// Display menu choices
		cout << "\nMAIN MENU\n"
			 << "1. Add job\n" << "2. Print job\n"
			 << "3. View jobs\n" << "4. Exit\n"
			 << "Enter your options [0-4]: ___\b";
		// Get a menu choice from the user
		cin >> option;
		// Process the menu choice
		switch (option) {
		case('1'):			// Simulate addition a print job to priority queue
			cout << "Instructor [I or i]\t" << "TA [T or t]\t" << "Student [S or s]___\b";
			// Get the rank of a print job (instructor, TA , or student) from user
			char ranking; cin >> ranking;
			PrintJob  pJob;  // construct a new print job
			// Assign rank of instructor (I), TA (T), or student (S) to the new print job's rank
			pJob.rank = (tolower(ranking) == 'i' ? I : tolower(ranking) == 't' ? T : S);
			// Assign a number (last print job++) to the new print job's number
			pJob.jobNum = ++lastJob;
			// Try to enqueue a print job; if the queue is full, throw an exception 
			try { 
					if (pQueue.isFull()) 
						throw string("ERROR: Full queue! Cannot perfom enqueue.\n");
					pQueue.Enqueue(pJob);
			}
			// Catch the thrown exception then display the error message
			catch (string xception) { cout << xception; }
			break;
		case('2'):		// Simulate printing (removal)a job from priority queue
			// Try to dequeue a print job; if the queue is empty, throw an exception 
			try {
					if (pQueue.isEmpty()) 
						throw string("ERROR: Empty queue! Cannot perfom dequeue.\n");
					PrintJob topJob;		// construct a new print job
					pQueue.Dequeue(topJob);	// call dequeue the top print job in queue
					// Notify user the current print job is out
					cout << "The current print job is out:\t" << topJob;
			}
			catch (string xception) { cout << xception; }
			break;
		case('3'):	// Display all print jobs from priority queue in order
			try {
					if (pQueue.isEmpty()) throw string("ERROR: Empty queue! Nothing to print.\n");
					// Duplicate the priority queue of 1000 PrintJobs
					PQType< PrintJob > cQueue(pQueue);
					// Print out cQueue
					cQueue.Print();
			}
			catch (string xception) { cout << xception; }
		}
	} while (option > '0' && option < '4');
	return 1;
}
