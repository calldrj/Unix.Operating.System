Cache_Simulation
Objective:

To write a C program that simulates reading and writing to a custom-sized direct-mapped cache, involving a custom-sized main memory.

Main Menu Options:

The program simulates reading from and writing to a cache based on choosing from a menu of choices, where each choice calls the appropriate procedure, where the choices are:

Enter Configuration Parameters Read from Cache Write to Cache Quit Program Note that when you read from ZyLab, the input values are not displayed on the screen as they are in the sample run at the end of this document.

Inputs:

Enter Parameters The total size of accessible main memory (in words) The total size of the cache (in words) The block size (words/block) Read from Cache The main memory address to read Write to Cache The main memory address to write The contents of the address for writing to the cache Input Value Checks:

All the parameter values must be powers of 2. The block size must never be larger than the size of accessible main memory. The total cache size must be some multiple of the block size. Your program should verify that all input variables are within limits as they are entered. Output Messages:

All messages should be display EXACTLY as shown in the sample run; that is, prefixed by three asterisks, a space and hyphen and one more space. The message should be followed by a blank line.

Data Accepted Message is comprised of two sentences: *** All Input Parameters Accepted.

 Starting to Process Write/Read Requests
Error Messages are preceded by “*** Error –“. A list of possible errors is given below. Note that one message has been deleted from previous versions of this Specification and three new ones have been added.

*** Error - Main Memory Size is not a Power of 2

*** Error - Block Size is not a Power of 2

*** Error - Cache Size is not a Power of 2

*** Error – Block size is larger than cache size

Deleted Error Message *** Error – Cache Size is not a multiple of Block Size

Newly Added Error Messages *** Error – Read Address Exceeds Memory Address Space

*** Error – Write Address Exceeds Memory Address Space (The write value following the invalid address value should be read and then discarded)

*** Error – Invalid Menu Option Selected (Until configuration data has been accepted, the only valid menu options that can be entered are “1” or “4.”)

Whenever any one of these errors occurs, the program should loop back to the Main Menu.

Content Message resulting from reading/writing to the cache *** Word WW of Cache Line LL with Tag TT contains Value VV

This message should appear after all successful reads or writes

WW is the word number in the cache line, LL is the line number in the cache, TT is the line’s tag value and VV is the content value in the cache.

All values are in decimal.

Read Messages (two possible messages) *** Read Miss - First Load Block from Memory (followed on the next line by the Content Message above)

*** Cache Hit (followed on the next line by the Content Message above)

Write Messages *** Write Miss - First Load Block from Memory (followed on the next line by the Content Message above)

*** Cache Hit (followed on the next line by the Content Message above)

Quit Program Message *** Memory Freed Up – Program Terminated Normally

When option 4 is entered, the memory should be freed up and the message “Memory Freed Up – Program Terminated Normally”, followed by a blank line, should be displayed before exiting the program.
