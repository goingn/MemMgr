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

void memmgr_free(void* ap);
void* memmgr_malloc(int nbytes);
void memmgr_init(void* pheapStart, void* pheapEnd, FILE* logFile);
int memmgr_get_remaining_space(void);
int memmgr_get_number_of_fragments(void);
int memmgr_get_allocated_space(void);
int memmgr_get_maximum_allocated_space(void);
int memmgr_get_malloc_count(void);
int memmgr_get_free_count(void);
void logMemoryFree(void* address);
void logMemoryAllocate(void* address, int size);

#endif /* MEMMGR_H_ */
