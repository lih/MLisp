#include "Array.test.hh"
#include "Array.hh"

#include "TestMacros.hh"

using namespace Utils;

#define TEST_SIZE 15000

namespace {
  int randInt(int a,int b) {
    return a+(rand()%(b+1));
  }
  
  void testResize() {
    ENTER_TEST("resize");
    
    Array<int> array;
    int size;

    for(int i=0;i<TEST_SIZE;++i) {
      size=randInt(50,100);
      array.resize(size);
      TEST(array.size()==size);
    }
  }
  void testFill() {
    ENTER_TEST("fill");
    
    #define ARRAY_SIZE 100
    Array<int> array(ARRAY_SIZE);
    int val;

    for(int i=0;i<TEST_SIZE;++i) {
      val=randInt(0,100000);
      
      array.fill(val);
      for(int j=0;j<ARRAY_SIZE;++j)
        TEST(array[j]==val);
    }
    #undef ARRAY_SIZE
  }
}

void array_test() {
  ENTER_TEST("template class Array<T> (with T=int)");
  
  testResize();
  testFill();
}

