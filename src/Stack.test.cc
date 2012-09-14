#include "Stack.test.hh"
#include "Stack.hh"

#include "TestMacros.hh"

using namespace Utils;

#define MANY 10000

namespace {
  int rand(int a,int b) {
    return a+(::rand()%(b-a+1));
  }

  void test_Empty_Push() {
    ENTER_TEST("push on empty stack");
    
    Stack<int> stack;

    fflush(stdout);
    
    stack.push(0);
  }
  void test_LIFO() {
    ENTER_TEST("LIFO property");

    int        str[MANY];
    Stack<int> stack(MANY);
    
    for(int i=0;i<MANY;++i) {
      str[i]=::rand();
      stack.push(str[i]);
    }

    for(int i=MANY;i>0;--i) {
      TEST(stack.top()==str[i-1]);
      stack.pop();
    }
  }
  void test_Size () {
    ENTER_TEST("size");

    Stack<int> stack;
    int        nRound=rand(5,15);
    int        size=0;
    
    for(int i=0;i<nRound;++i) {
      if(i%2==0) {
        int off=rand(1,1000);
        for(int j=0;j<off;++j)
          stack.push(0);
        size+=off;
      }
      else {
        int off=rand(0,size);
        for(int i=0;i<off;++i)
          stack.pop();
        size-=off;
      }
      TEST(stack.size()==size);
    }
  }
}

void stack_test() {
  ENTER_TEST("template class Stack<T> (with T=int)");
  
  test_Empty_Push();
  test_LIFO();
  test_Size();
}
