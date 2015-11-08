/*
 * Authors: Noah Going, Noel Mrowiec
 * Course: CS3841
 * Assignment: Lab 8
 * Date: 9/19/15
 *
 * Definitions for memmgr functions
 */

#ifndef MEMMGR_H_
#define MEMMGR_H_

#include <stdio.h>

typedef struct hdr {
	struct hdr* ptr;
	unsigned int size;
} HEADER;

HEADER* frhd;
int memleft;
int heapsize;
int maxallocatedspace;
HEADER heapstart;
HEADER heapend;
long int mallocCount;
long int freeCount;
FILE* logFile;

/**
 * Frees an allocated block and returns it to the memory pool
 *
 * @param void* ap : start of allocated address
 */
void memmgr_free(void* ap);

/**
 * Allocates a block of RAM of the given size
 *
 * @param int nbytes : amount of RAM to allocate
 * @return start of block or null if unable to allocate
 */
void* memmgr_malloc(int nbytes);

/**
 * Initializes dynamic memory, starting at the first location and
 * going to the second location
 *
 * @param void* pheapStart : starting location
 * @param void* pheapEnd : ending location
 * @param FILE* log : FILE pointer if log file is to be created,
 * NULL  otherwise
 */
void memmgr_init(void* pheapStart, void* pheapEnd, FILE* log);

/**
 * Gets remaining free space that can be allocated, equal to total space
 * minus the allocated space minus any additional overhead
 */
int memmgr_get_remaining_space(void);

/**
 * Counts the number of memory fragments, length of free space linked list
 * minus 1
 */
int memmgr_get_number_of_fragments(void);

/**
 * Returns the current allocated space in bytes
 */
int memmgr_get_allocated_space(void);

/**
 * Returns the maximum allocated space since initialization
 */
int memmgr_get_maximum_allocated_space(void);

/**
 * Returns the number of successful calls to malloc made
 */
int memmgr_get_malloc_count(void);

/**
 * Returns the number of successful calls to free made
 */
int memmgr_get_free_count(void);

/**
 * If log is not NULL, logs an address that is being freed to a log file
 */
void logMemoryFree(void* address);

/**
 * If log is not NULL, logs an address that is being allocated to a log
 * file, as well as the amount of memory that is being allocated
 */
void logMemoryAllocate(void* address, int size);

#endif /* MEMMGR_H_ */
