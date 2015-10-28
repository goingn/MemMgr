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
	return NULL;
}
void memmgr_init(void* pheapStart, void* pheapEnd, FILE* logFile) {
}
int memmgr_get_remaining_space(void) {
	return 0;
}
int memmgr_get_number_of_fragments(void) {
	return 0;
}
int memmgr_get_allocated_space(void) {
	return 0;
}
int memmgr_get_maximum_allocated_space(void) {
	return 0;
}
int memmgr_get_malloc_count(void) {
	return 0;
}
int memmgr_get_free_count(void) {
	return 0;
}
void logMemoryFree(void* address) {
}
void logMemoryAllocate(void* address, int size) {
}
