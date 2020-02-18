// Implementation of priority queue
// Header file printjob.h
// Designed by Tuan Nguyen
// Project Priority for Printer Queue
#ifndef PRINTJOB_H_
#define PRINTJOB_H_
#include<iostream>
using namespace std;
// Enumrate student, TA, and instructor classifications
enum Rank { S, T, I, };
// Define struct print job
struct PrintJob {
	int	jobNum;
	char	rank; // instructor[i], TA[t], student[s] in that order
	// Overloaded operator to compare two print jobs priority
	bool operator >(PrintJob other) {
		return (rank > other.rank || (rank == other.rank && jobNum < other.jobNum));
	}
	// Overloaded outstream operator to print out a print job
	friend ostream& operator <<(ostream& stream, const PrintJob pJob) {
		cout << "Job #" << pJob.jobNum << ":\t"
			 << (!pJob.rank ? "Student" : pJob.rank == 1 ? "TA" : "Instructor") << '\n';
		return stream;
	}
};
#endif /* PRINTJOB_H */
#pragma once
