~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

Specifications:
WLA Lab #007 has only one printer. Instructors, TAs and students send their print jobs to this printer. The print jobs are not done first in, first out as a normal queue. 
An instructor's favorite motto -- from George Orwell's Animal Farm -- is quoted, "[a]ll animals are equal, but some animals are more equal than others."
Therefore, students' jobs are done first in, first out. But all TAs' print jobs are to be completed before any student print job -- with the TAs' print jobs being done first in, first out. And you guessed it -- all instructors' print jobs are to be done before any TA print job, with the instructors' print jobs being done first in, first out.
The required task is to create a piece of software to manage this specified printer queue. 

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

Brief description for design and implementation: 
For the priority print job queue implementation and validation, the following files are included:
+	a HeapType struct and its member functions in heap.h and heap.cpp,
+	a PQType class and its member functions in pqtype.h and pqtype.cpp,
+	a PrintJob struct in printjob.h with a pair of overloaded operators > [greater comparision] and << [outstream] 
since templates are designed in HeapType and PQType,
+	and a test program test.cpp to validate the implementations.
Inside the deployment, the uses of enum Rank { S, T, I, } for Student, TA, and Instructor classifications, 
and exception, try, catch scheme are employed. 
The key public member function in printjob.h that determines the priority of the queue is the overloaded operator > 
for a comparision of the two print jobs' priority:
// Overloaded operator to compare two print jobs priority: top priority = the highest rank with lowest job number //
bool operator >(PrintJob other) { return (rank > other.rank || (rank == other.rank && jobNum < other.jobNum)); }

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 

Acknowledgement & Credit:
1. heap.h, heap.cpp, pqtype.h, pqtype.cpp are the implementations of Dr. Nell Dale (C++ Plus Data Structures, p.580 - 592, 6th Edition).
2. copy constructor PQType(const PQType&) and void Print() [print all items in PQType] in pqtype.cpp, printjob.h, and test.cpp are the work of Tuan Nguyen.
3. Reuse of parts or the whole of the code must accordingly include this Acknowledgement & Credit.

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ 
