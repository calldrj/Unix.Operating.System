#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define DEFVAL -2019

// Structure to represent a cache line (tag, word)
struct node {
    int  tag;          // determined by location of main memory block
    int* block;        // points to a dynamically allocated line-block
} *cache = NULL;

// Declare an individual cache type
typedef struct node nd;

// Function to return true if n is a power of 2, false otherwise
bool is_power_2(int n) {
    return (n > 0) && (floor(log2(1.0 * n)) == ceil(log2(1.0 * n)));
}

// Function to convert a decimal address to binary in array form
int* dec_to_bin(int address, int mem) {
    int* bit_arr = (int*)malloc(mem * sizeof(int));
    for (int i = mem  - 1; i >= 0 ; address >>= 1, i--)
        bit_arr[i] = address & 1;
    return bit_arr;
}

// Fuction to calculate the index of word, line, and tag in a binary array
int index_calculate(int* bin_arr, int size, int start, int end) {
    int index = 0;
    for (int i = size - start - 1; i >= size - start - end; i--)
        index += bin_arr[i] * pow(2, size - start - 1 - i);
    return index;
}

int main() {
    // Declare local variables
    int  task, mem_size, cache_size, block_size, num_line, val,
    mem, line, word, tag, mem_address, word_index, line_index, tag_index;
    bool params_accepted = false;
    int* mem_arr  = NULL;
    int* word_arr = NULL;
    int* mem_bit  = NULL;
   
    // Until user chooses to quit, prompt for choice and select appropriate function
    do {
        printf("\nMain Menu - Main Memory to Cache Memory Mapping\n");
        printf("------------------------------------------------\n");
        printf("\n1) Enter Configuration Parameters");
        printf("\n2) Read from Cache");
        printf("\n3) Write to Cache");
        printf("\n4) Quit Program");
        printf("\n\nEnter selection: ");
        scanf("%d", &task);
        
        switch (task) {
                // Process Configuration Parameters
            case 1:
                // Prompt for main memory size from user
                printf("\nEnter main memory size (words): ");
                scanf("%d", &mem_size);
                
                // Prompt for cache size from user
                printf("\nEnter cache size (words): ");
                scanf("%d", &cache_size);
                
                // Prompt for block size (words/block) from user
                printf("\nEnter block size (words/block): ");
                scanf("%d", &block_size);
                
                // Validate memory sise power of 2
                if (!is_power_2(mem_size)) {
                    printf("\n\n*** Error - Main Memory Size is not a Power of 2\n"); break;
                }
                
                // Validate cache size power of 2
                if (!is_power_2(cache_size)) {
                    printf("\n\n*** Error - Cache Size is not a Power of 2\n"); break;
                }
                
                // Validate block size power of 2
                if (!is_power_2(block_size)) {
                    printf("\n\n*** Error - Block Size is not a Power of 2\n"); break;
                }
                
                // Validate block size <= cache_size
                if (block_size > cache_size) {
                    printf("\n\n*** Error - Block Size is Larger than Cache Size\n"); break;
                }
                
                params_accepted = true;
                printf("\n\n*** All Input Parameters Accepted.\nStarting to Process Write/Read Requests\n");
                
                // Allocate space for memory and initialize
                mem_arr = (int*)malloc(mem_size * sizeof(int));
                for (int i = 0; i < mem_size; i++) mem_arr[i] = mem_size - i;
                
                // Allocate space for cache and initialize
                num_line = cache_size / block_size;
                cache = (nd*)malloc(num_line * sizeof(nd));
                for (int i = 0; i < num_line; i++) {
                    cache[i].tag = DEFVAL;
                    cache[i].block = (int*)malloc(block_size * sizeof(int));
                    for (int w = 0; w < block_size; w++)
                        cache[i].block[w] = DEFVAL;
                }
                
                // Calculate numer of bits for memory, word offset, line address, and tag field
                mem  = (int)log2(1.0 * mem_size);
                word = (int)log2(1.0 * block_size);
                line = (int)log2(1.0 * num_line);
                tag  = mem - word - line;
                
                break;
                
                // Read from Cache
            case 2:
                // Verify if all input parameters are accepted
                if (!params_accepted) {
                    printf("\n\n*** Error - Invalid Menu Option Selected\n"); break;
                }
                
                // Prompt for memory address to read from user
                printf("\nEnter Main Memory Address to Read: ");
                scanf("%d", &mem_address);
                printf("\n");
                
                // Validate  0 <= memory address < mem_size
                if (mem_address < 0) {
                    printf("\n\n*** Error – Read Address is a negative number\n");
                    break;
                }
                
                if (mem_address >= mem_size) {
                    printf("\n\n*** Error – Read Address Exceeds Memory Address Space\n");
                    break;
                }
                
                // Covert decimal memory address to address bit pattern
                mem_bit = dec_to_bin(mem_address, mem);
                
                // Calculate word index, line index, tag index
                word_index = index_calculate(mem_bit, mem, 0, word);
                line_index = index_calculate(mem_bit, mem, word, line);
                tag_index  = index_calculate(mem_bit, mem, word + line, tag);
                
                if (cache[line_index].tag == tag_index)
                    printf("\n*** Cache Hit\n");
                else {
                    printf("\n*** Read Miss - First Load Block from Memory\n");
                    cache[line_index].tag = tag_index;
                    cache[line_index].block[word_index] = mem_arr[mem_address];
                }
                
                // Print the content message
                printf("\n*** Word %d of Cache Line %d with Tag %d contains the Value %d\n",
                       word_index, line_index, cache[line_index].tag, cache[line_index].block[word_index]);
                break;
                
                // Write to Cache
            case 3:
                // Verify if all input parameters are accepted
                if (!params_accepted) {
                    printf("\n\n*** Error - Invalid Menu Option Selected\n"); break;
                }
                
                // Prompt for main memory address and value to write from user
                printf("\nEnter Main Memory Address to Write: ");
                scanf("%d", &mem_address);
                
                // Validate  0 <= memory address < mem_size
                if (mem_address < 0) {
                    printf("\n\n*** Error – Read Address is a negative number\n");
                    scanf("%d", &val); break;
                }
                if (mem_address >= mem_size) {
                    printf("\n\n*** Error – Write Address Exceeds Memory Address Space\n");
                    scanf("%d", &val); break;
                }
                
                printf("\nEnter Value to Write: ");
                scanf("%d", &val);
                printf("\n");
                
                // Covert decimal memory address to address bit pattern
                mem_bit = dec_to_bin(mem_address, mem);
                
                // Calculate word index, line index, tag index
                word_index = index_calculate(mem_bit, mem, 0, word);
                line_index = index_calculate(mem_bit, mem, word, line);
                tag_index  = index_calculate(mem_bit, mem, word + line, tag);
                
                // Check cache's tag and block's value to find hit or miss then print out a message
                if (cache[line_index].tag == tag_index)
                    printf("\n*** Cache Hit\n");
                else {
                    printf("\n*** Write Miss - First load block from memory\n");
                    cache[line_index].tag = tag_index;
                }
                
                // Write the data to cache
                cache[line_index].block[word_index] = val;
                
                // Write the data back to main memory
                mem_arr[mem_address] = val;
                
                // Print the content message
                printf("\n*** Word %d of Cache Line %d with Tag %d contains the Value %d\n",
                       word_index, line_index, cache[line_index].tag, cache[line_index].block[word_index]);
                break;
                
                // Quit if menu task == 4
            case 4:
                break;
            default:    // Value other than 1, 2, 3, 4 receive, print out the message and return main menu
                printf("\n\n*** Error - Invalid Menu Option Selected\n");
                break;
        }
    } while(task != 4);
    
    // Free all memmory
    if (mem_arr != NULL) free(mem_arr);
    if (cache != NULL) free(cache);
    if (word_arr != NULL) free(word_arr);
    if (mem_bit != NULL) free(mem_bit);
    
    // Message to terminate the program
    printf("\n\n*** Memory Freed Up - Program Terminated Normally\n\n");
    
    return 1;
}


/*
 // Test print
 printf("\nbits for word offset = %d\t bits for line address = % d\t bits for tag = %d\n", word, line, tag);
 for (int i = 0; i < mem; i++)
 printf("%d", mem_bit[i]);
 
 printf("\n*** Word %d of Cache Line %d with Tag %d contains the Value %d\n",
 word_index, line_index, tag_index, val);
 
 printf("\ncache[line_index].tag = %d\tcache[line_index].block[word_index] = %d\n",
 cache[line_index].tag, cache[line_index].block[word_index]);
 
 */
