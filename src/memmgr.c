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
	HEADER *nxt, *prev, *f;
	f = (HEADER *)ap -1;
	memleft += f->size;
	freeCount++;

	/*frhd is not NULL. Only NULL if memmgr_init was not called,
	  which should never happen.*/
	if(frhd > f){
		//Free-space head is higher up in memory than returnee
		nxt = frhd;
		frhd = f;
		prev = f + f->size;

		if(prev == nxt){
			f-> size += nxt->size;
			f->ptr = nxt->ptr;
		}
		else{
			f->ptr = nxt;
			return;
		}
	}

	/*Otherwise, current free-space head is lower in memory. Move back on
	 *the free-space list looking for the block being returned. If the next
	 *pointer points past the block, make a new entry and link it. If next
	 *pointer plus its size points to the block, form one contiguous block.
	*/
	nxt = frhd;
	for(nxt = frhd; nxt && nxt < f; prev=nxt, nxt=nxt->ptr){
		if(nxt+nxt->size == f){
			nxt->size += f->size;
			f = nxt + nxt->size;
			if(f == nxt->ptr){
				/*The new, larger block is contiguous to the next free block,
				 * so form a larger block. There's no need to continue this
				 * checking since if the block following this free one were
				 * free, the two would already have been combined;.
				 */
				nxt->size += f->size;
				nxt->ptr = f->ptr;
			}
			return;
		}
	}

	/*The address of the block being returned is greater than one in the free
	 *queue (nxt) or the end of the queue was reached. If at end, just link to
	 *the end of the queue. Therefore, nxt is NULL or points to a block higher
	 *up in memory than the one being returned.
	 */

	prev->ptr = f;
	prev = f + f->size;
	if(prev == nxt){
		f->size += nxt->size;
		f->ptr = nxt->ptr;
	}
	else{
		f->ptr = nxt;
		return;
	}
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
				if (prev == NULL) {
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

		heapstart = (char*)pheapStart;
		heapend = (char*)pheapEnd;
		heapsize = (char*)&heapend - (char*)&heapstart;
		frhd = (HEADER*) &heapstart;
		frhd->ptr = NULL;
		frhd->size = heapsize / sizeof(HEADER);
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
	int numOfFragments = 1;
	HEADER* nxt;

	nxt = frhd;

	while(nxt->ptr != NULL){
		numOfFragments++;
		nxt = nxt -> ptr;
	}

	return numOfFragments;
}

int memmgr_get_allocated_space(void) {
	unsigned int totalSpace = heapsize / sizeof(HEADER);
	return totalSpace - memleft;
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
