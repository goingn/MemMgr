/*
 * Authors: Noah Going, Noel Mrowiec
 * Course: CS3841
 * Assignment: Lab 8
 * Date: 10/28/15
 *
 * Implementation of memmgr
 */

#include <stddef.h>
#include <stdio.h>
#include "memmgr.h"

void memmgr_free(void* ap) {
}

void* memmgr_malloc(int nbytes) {
	HEADER* nxt;
	HEADER* prev;
	int nunits;
	nunits = (nbytes + sizeof(HEADER) - 1) / sizeof(HEADER) + 1;

	for (prev = NULL, nxt = frhd; nxt; nxt = nxt->ptr) {
		if (nxt->size >= nunits) {
			if (nxt->size > nunits) {
				nxt->size -= nunits;
				nxt += nxt->size;
				nxt->size = nunits;
			} else {
				if (!prev) {
					frhd = nxt->ptr;
				} else {
					prev->ptr = nxt->ptr;
				}

			}
			memleft -= nunits;
			maxallocatedspace += nunits;
			mallocCount++;
			return ((char*) (nxt + 1));
		}
	}

	return NULL;
}

void memmgr_init(void* pheapStart, void* pheapEnd, FILE* log) {
	maxallocatedspace = 0;
	mallocCount = 0;
	freeCount = 0;
	if ((pheapStart) && (pheapEnd)) {

		heapstart = (char*) pheapStart;
		heapend = (char*) pheapEnd;
		frhd = (HEADER*) &heapstart;
		frhd->ptr = NULL;
		frhd->size = ((char*) &heapend - (char*) &heapstart) / sizeof(HEADER);
		memleft = frhd->size;

	}
	if (log) {
		logFile = log;
	}
}

int memmgr_get_remaining_space(void) {
	return memleft;
}

int memmgr_get_number_of_fragments(void) {
	return frhd -> size -1;
}

int memmgr_get_allocated_space(void) {
	return 0;
}

int memmgr_get_maximum_allocated_space(void) {
	return maxallocatedspace;
}

int memmgr_get_malloc_count(void) {
	return mallocCount;
}

int memmgr_get_free_count(void) {
	return freeCount;
}

void logMemoryFree(void* address) {
	if (logFile) {
		fprintf(logFile, "\nFreeing address: %x.", (unsigned int) address);
	}
}

void logMemoryAllocate(void* address, int size) {
	if (logFile) {
		fprintf(logFile, "\nAllocating %u bytes at %x.", size,
				(unsigned int) address);
	}
}
