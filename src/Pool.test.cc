#include "Pool.test.hh"
#include "Pool.hh"

#include "TestMacros.hh"

#define TEST_SIZE 15000

namespace {
  void testIntegrity() {
    Pool   test(sizeof(int));
    int*   tmp[TEST_SIZE];
    int    tmpVals[TEST_SIZE];
     
    ENTER_TEST("allocation integrity");
    
    for(int i=0;i<TEST_SIZE;++i)
      tmpVals[i]=rand();

    // Allocate 10000
    for(int i=0;i<10000;++i) {
      tmp[i]=static_cast<int*>(test.alloc());
      *(tmp[i])=tmpVals[i];
    }
        
    // Deallocate 5000
    for(int i=0;i<5000;++i) {
      TEST(*(tmp[i])==tmpVals[i]); 
      test.free(tmp[i]);
    }
        
    // Allocate 10000 more
    for(int i=0;i<10000;++i) {
      tmp[5000+i]=static_cast<int*>(test.alloc());
      *(tmp[i+5000])=tmpVals[i+5000];
    }
     
    // Free them
    for(int i=0;i<15000;++i)
      test.free(tmp[i]);
  }
  void testListAllocated() {
    ENTER_TEST("listing of allocated objects");

    Pool test(sizeof(int));
    int* ptrs[TEST_SIZE];

    for(int i=0;i<TEST_SIZE;++i) {
      ptrs[i]=static_cast<int*>(test.alloc());
      *ptrs[i]=i;
    }

    Pool::Iterator tmp=test.allocated();
    int i=0;
    
    for(;tmp;++tmp,++i)
      TEST(*static_cast<int*>(*tmp)<=TEST_SIZE);
    TEST(i==test.allocCount());
  }
}

void pool_test() {
  ENTER_TEST("class Pool");
  
  testIntegrity();
  testListAllocated();
}
