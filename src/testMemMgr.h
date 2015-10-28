#ifndef TESTMEMMGR_H
#define TESTMEMMGR_H

      
#include <iostream>
#include <string>

// Note 1
#include <TestFixture.h>
#include <extensions/HelperMacros.h>

extern "C" {
  #include "memmgr.h"   
}



using namespace std;

class MemMgrTestCase : public CppUnit::TestFixture { // Note 2 
  CPPUNIT_TEST_SUITE(MemMgrTestCase);

	CPPUNIT_TEST(testRawMemoryAvailable);
	CPPUNIT_TEST(testInitialAllocation);
	CPPUNIT_TEST(testDoubleAllocation);
	CPPUNIT_TEST(testMallocAndFreeCount);

  CPPUNIT_TEST(testOne);
  CPPUNIT_TEST(testTwo);
  CPPUNIT_TEST(testThree);
  CPPUNIT_TEST(testFour);
  CPPUNIT_TEST(testBigAllocation);
  CPPUNIT_TEST(testAllocation);
  CPPUNIT_TEST(testAllocationAfterFree);
  CPPUNIT_TEST(testFragmentationCount);
  CPPUNIT_TEST_SUITE_END();

 private:
  //linkedList myList;
  void setupBasicList();

public:
    void setUp();
    void tearDown();

 protected:
	void testRawMemoryAvailable();
	void testInitialAllocation();
	void testDoubleAllocation();
	void testFragmentationCount();
	void testMallocAndFreeCount();
  void testOne();
  void testTwo();
  void testThree();
  void testFour();
  void testBigAllocation();
  void testAllocation();
  void testAllocationAfterFree();
};
#endif
          
