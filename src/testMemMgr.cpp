#include "testMemMgr.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define MAX_HEAP_SIZE (1024 * 64)
#define HEADER_SIZE sizeof(hdr)
#define BASE_AVAILABLE_MEMORY (MAX_HEAP_SIZE-HEADER_SIZE)

CPPUNIT_TEST_SUITE_REGISTRATION(MemMgrTestCase);
static  char myHeap[MAX_HEAP_SIZE]; 
static FILE *fp;


void MemMgrTestCase::setUp()
{
  printf("Setup being called.");
  int index = 0;
  for (index=0; index < MAX_HEAP_SIZE; index++)
  {
    myHeap[index]=0;
  }
  fp = fopen("memoryLog.log", "w");
  memmgr_init(&myHeap[0], &myHeap[MAX_HEAP_SIZE], fp);
}

void MemMgrTestCase::tearDown()
{
  printf("Teardown being called.");
  int index = 0;
  for (index=0; index < MAX_HEAP_SIZE; index++)
  {
    myHeap[index]=0;
  }
  fclose(fp);
  fp = NULL;
}

/*
 * This test will verify if the basic memory amount is correct before any allocations are made. 
 */
void MemMgrTestCase::testRawMemoryAvailable()
{
	  CPPUNIT_ASSERT_MESSAGE("Free memory space not correct.", memmgr_get_remaining_space()==(MAX_HEAP_SIZE));
}

void MemMgrTestCase::testInitialAllocation()
{
	// Start by allocating a block of memory of 8 bytes.
	char* allocatedMemory = (char*)memmgr_malloc(8);
	
    CPPUNIT_ASSERT_MESSAGE("Wrong address allocated.", allocatedMemory==&myHeap[MAX_HEAP_SIZE]-8);
}

void MemMgrTestCase::testDoubleAllocation()
{
	// Start by allocating a block of memory of 8 bytes.
	char* allocatedMemory = (char*)memmgr_malloc(8);
	
    CPPUNIT_ASSERT_MESSAGE("Wrong address allocated.", allocatedMemory==(&myHeap[MAX_HEAP_SIZE]-8));
	
	char* allocatedMemory2 = (char*)memmgr_malloc(8);
	
    CPPUNIT_ASSERT_MESSAGE("Wrong address allocated.", allocatedMemory2==(&myHeap[MAX_HEAP_SIZE]-8-8-HEADER_SIZE));
}

void MemMgrTestCase::testMallocAndFreeCount()
{
  void* pointers[1024];
  int index = 0;

  for (index = 0; index < 1023; index++)
  {
    // Allocate a set of indicies.
    pointers[index] = memmgr_malloc(56);
	CPPUNIT_ASSERT_MESSAGE("Invalid count of mallocs.", memmgr_get_malloc_count()==index+1);
  }
  
  for (index = 0; index < 1023; index++)
  {
    // Allocate a set of indicies.
    memmgr_free(pointers[index]);
	CPPUNIT_ASSERT_MESSAGE("Invalid count of mallocs.", memmgr_get_free_count()==index+1);
  }

  
  
  
}

/*
 * This test case will verify that the proper pointers are being assigned
 * based upon the algorithm provided.  It also will verify free works properly.
 */
void MemMgrTestCase::testFragmentationCount()
{
  void* pointers[1024];
  int index = 0;

  printf("########################################################\n");
  printf("Testing allocations after free.\n");
  printf("########################################################\n");

  // Start by allocating a set of 56 bytes.
  // These should go at the end of memory.
  for (index = 0; index < 1023; index++)
  {
    // Allocate a block of 56 bytes.
    pointers[index] = memmgr_malloc(56);
  }

  // Now that we have done this, free every other one of them.
  for (index = 0; index < 1022; index+=2)
  {
    memmgr_free(pointers[index]);
	printf("Expected fragmentation count: %d Actual: %d\n", index/2+1, memmgr_get_number_of_fragments());
	CPPUNIT_ASSERT_MESSAGE("Fragmentation Count not working properly.", memmgr_get_number_of_fragments()==(index/2+1));
  }
  
  memmgr_free(pointers[1022]);
  int count = 511;
  
  // Now free some of the other lists and see what happens.
  for (index = 1; index < 1023; index+=2)
  {
    memmgr_free(pointers[index]);
	count--;
	printf("Expected fragmentation count: %d Actual: %d\n", count, memmgr_get_number_of_fragments());

	CPPUNIT_ASSERT_MESSAGE("Fragmentation Count not working properly.", memmgr_get_number_of_fragments()==count);
  }
}
	
	
	
	



/*
 * This test verifies that linear allocation of heap occurs properly.  No test of the free routine occurs.
 */
void MemMgrTestCase::testOne()
{
  printf("########################################################\n");
  printf("Test 1 running.\n");
  printf("########################################################\n");

  int index = 0;

  printf("Current heap size: %x\n", memmgr_get_remaining_space());
  CPPUNIT_ASSERT_MESSAGE("Free memory space not correct.", memmgr_get_remaining_space()==(MAX_HEAP_SIZE));

  for (index = 0; index < 1023; index++)
  {
    // Allocate a set of indicies.
    memmgr_malloc(56);
    printf("Index %d Current Heap size: %x\n", index, memmgr_get_remaining_space());
    CPPUNIT_ASSERT_MESSAGE("Free memory space not correct.", memmgr_get_remaining_space()==(int)(MAX_HEAP_SIZE - (index+1) * (56 + HEADER_SIZE)));
  }
}

/*
 * This test verifies that linear allocation of heap occurs properly.  It also tests if free works properly.
 */
void MemMgrTestCase::testTwo()
{
  void* pointers[1024];
  int index = 0;

  printf("########################################################\n");
  printf("Test 2 running.\n");
  printf("########################################################\n");

  printf("Current heap size: %x\n", memmgr_get_remaining_space());
  CPPUNIT_ASSERT_MESSAGE("Free memory space not correct.", memmgr_get_remaining_space()==(MAX_HEAP_SIZE));

  for (index = 0; index < 1023; index++)
  {
    // Allocate a set of indicies.
    pointers[index] = memmgr_malloc(56);
  }

  // Now iterate through and free the memory and make certain everything is working properly.
    for (index = 0; index < 1023; index++)
  {
    // Free the given pointer.
    memmgr_free(pointers[index]);
    printf("Index %d Current Heap size: %x\n", index, memmgr_get_remaining_space());
 
    CPPUNIT_ASSERT_MESSAGE("Problem with space after freeing memory.", 
    memmgr_get_remaining_space()==(0x80 + (index * 64)));
  }
}
  /*
 * This test will verify alternating patterns of allocation and freeing 
   to make certain that the memory size is working properly.
 */

void MemMgrTestCase::testThree()
{
  void* pointers[1024];
  int index = 0;

  printf("########################################################\n");
  printf("Test 3 running.\n");
  printf("########################################################\n");

  // Start by allocating one block of memory of size 8.
  pointers[0] = memmgr_malloc(8);
  CPPUNIT_ASSERT_MESSAGE("Problem with allocation when 8 byte allocation is made.", MAX_HEAP_SIZE-16==memmgr_get_remaining_space());
  
  for (index = 1; index < 1024; index++)
  {
    // Start by mallocing another block of a larger size.
    pointers[index] = memmgr_malloc(index * 8+8);

    CPPUNIT_ASSERT_MESSAGE("Problem with allocation of 8x byte allocation is made.", MAX_HEAP_SIZE-(2*8+index*8 + (index+1)*8)==memmgr_get_remaining_space());

    // Now free the pointer right before the allocation.
    memmgr_free(pointers[index-1]);

    CPPUNIT_ASSERT_MESSAGE("Problem with free of 8(x-1) byte allocation.", MAX_HEAP_SIZE-(1*8+ (index+1)*8)==memmgr_get_remaining_space());
  }
}


// This will test fragmentation calculations.  Essentially, if blocks are freed in a strange way, the fragmentation count should change differently.

void MemMgrTestCase::testFour()
{
  void* pointers[1024];
  int index = 0;
  int fragCount;

  printf("########################################################\n");
  printf("Test 4 running.\n");
  printf("########################################################\n");

  for (index = 0; index < 1023; index++)
  {
    // Allocate a block of 56 bytes.
    pointers[index] = memmgr_malloc(56);
  }

  fragCount = 0;
  // Now iterate through and free the memory, hitting every other allocation and make certain 
  //everything is working properly.
  for (index = 1; index < 1023; index+=2)
  {
    memmgr_free(pointers[index]);
    fragCount +=1;

    CPPUNIT_ASSERT_MESSAGE("Problem with the fragment count not being correct", fragCount==memmgr_get_number_of_fragments());
  }
  
  // Now iterate through and free the memory and make certain everything is working properly.
  // This will free the even allocations.  Since we are freeing these blocks, the size should go down.
  for (index = 1022; index > 0; index-=2)
  {
    memmgr_free(pointers[index]);
    fragCount--;

    CPPUNIT_ASSERT_MESSAGE("Problem with the fragment count not being correct", fragCount==memmgr_get_number_of_fragments());
  }
}

/*
 * This test will ensure that 
 */
void MemMgrTestCase::testBigAllocation()
{
  void* pointer;
  int index = 0;

  printf("########################################################\n");
  printf("Test Big ALlocation running.\n");
  printf("########################################################\n");

  for (index = MAX_HEAP_SIZE*2; index > MAX_HEAP_SIZE; index--)
  {
    // Allocate a block of 56 bytes.
    pointer = memmgr_malloc(index);
    CPPUNIT_ASSERT_MESSAGE("Problem: Pointer should be NULL but was not.", pointer==NULL);
  }
}

/*
 * This test case will verify that the proper pointers are being assigned
 * based upon the algorithm provided.
 */
void MemMgrTestCase::testAllocation()
{
  void* pointers[1024];
  int index = 0;

  printf("########################################################\n");
  printf("Testing allocations.\n");
  printf("########################################################\n");

  // Start by allocating a set of 56 bytes.
  // These should go at the end of memory.
  for (index = 0; index < 1023; index++)
  {
    // Allocate a block of 56 bytes.
    pointers[index] = memmgr_malloc(56);
	int expectedOffset = MAX_HEAP_SIZE - ((index+1) * 56 + index * HEADER_SIZE);
    printf("Expected Address %p Actual Address: %p\n", &myHeap[expectedOffset], pointers[index]);
	
    CPPUNIT_ASSERT_MESSAGE("Problem: Allocation to the wrong space occurred.", pointers[index]==&myHeap[expectedOffset]);
  }
}


/*
 * This test case will verify that the proper pointers are being assigned
 * based upon the algorithm provided.  It also will verify free works properly.
 */
void MemMgrTestCase::testAllocationAfterFree()
{
  void* pointers[1024];
  int index = 0;

  printf("########################################################\n");
  printf("Testing allocations after free.\n");
  printf("########################################################\n");

  // Start by allocating a set of 56 bytes.
  // These should go at the end of memory.
  for (index = 0; index < 1023; index++)
  {
    // Allocate a block of 56 bytes.
    pointers[index] = memmgr_malloc(56);
  }

  // Now that we have done this, free every other one of them.
  for (index = 0; index < 1023; index+=2)
  {
    memmgr_free(pointers[index]);
  }

  // Now try to re-allocate and make sure things work properly.
  for (index = 0; index < 1023; index+=2)
  {
	int expectedOffset = MAX_HEAP_SIZE - ((index+1) * 56 + index * HEADER_SIZE);
    printf("Expected Address %p Actual Address: %p\n", &myHeap[expectedOffset], pointers[index]);
	
    CPPUNIT_ASSERT_MESSAGE("Problem: Allocation to the wrong space occurred.", 
    pointers[index]==&myHeap[expectedOffset]);
  }
}

