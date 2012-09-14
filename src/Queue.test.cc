#include "Queue.test.hh"
#include "Queue.hh"

#include "TestMacros.hh"

using namespace Utils;

#define MANY 10000

namespace {
  int rand(int a,int b) {
    return a+(::rand()%(b-a+1));
  }

  void test_Empty_Push() {
    ENTER_TEST("push on empty queue");

    Queue<int> queue;

    queue.push(0);
  }
  void test_FIFO() {
    ENTER_TEST("FIFO property");

    int        str[MANY];
    Queue<int> queue(MANY);
    
    for(int i=0;i<MANY;++i) {
      // Fill the queue
      str[i]=::rand();
      queue.push(str[i]);
    }
    for(int i=0;i<MANY/2;++i) {
      queue.pop();
      queue.push(str[i]);
    }

    for(int i=0;i<MANY;++i) {
      TEST(queue.top()==str[(i+MANY/2)%MANY]);
      queue.pop();
    }
  }
  void test_Size () {
    ENTER_TEST("size");

    Queue<int> queue;
    int        nRound=rand(5,15);
    int        size=0;
    
    for(int i=0;i<nRound;++i) {
      if(i%2==0) {
        int off=rand(1,1000);
        for(int j=0;j<off;++j)
          queue.push(0);
        size+=off;
      }
      else {
        int off=rand(0,size);
        for(int i=0;i<off;++i)
          queue.pop();
        size-=off;
      }
      TEST(queue.size()==size);
    }
  }
  void test_Shrink_OB_OA() {
    ENTER_TEST("shrinking with overflow before");
    
    Queue<int> queue(100);

    for(int i=0;i<100;++i)
      queue.push(i);
    for(int i=0;i<60;++i)
      queue.pop();
    for(int i=0;i<20;++i)
      queue.push(i+100);
    queue.resize(70);
    for(int i=60;i<120;++i) {
      TEST(queue.top()==i);
      queue.pop();
    }
  }
  void test_Shrink_NOB_OA() {
    ENTER_TEST("shrinking with overflow after and not before");
    
    Queue<int> queue(100);

    for(int i=0;i<70;++i)
      queue.push(i);
    for(int i=0;i<30;++i)
      queue.pop();
    queue.resize(60);
    for(int i=30;i<70;++i) {
      TEST(queue.top()==i);
      queue.pop();
    }
  }
  void test_Shrink_NOB_NOA() {
    ENTER_TEST("shrinking with neither overflow before nor after");
 
    Queue<int> queue(100);

    for(int i=0;i<70;++i)
      queue.push(i);
    for(int i=0;i<30;++i)
      queue.pop();
    
    queue.resize(80);
    for(int i=30;i<70;++i) {
      TEST(queue.top()==i);
      queue.pop();
    }
  }
  void test_Expand_OB() {
    ENTER_TEST("expanding with overflow before");
    
    Queue<int> queue(100);

    for(int i=0;i<40;++i) {
      queue.push();
      queue.pop();
    }
    for(int i=0;i<100;++i)
      queue.push(i);
        
    queue.resize(120);
    for(int i=0;i<100;++i) {
      TEST(queue.top()==i);
      queue.pop();
    }
  }
  void test_Expand_NOB() {
    ENTER_TEST("expanding with no overflow before");

    Queue<int> queue(100);

    for(int i=0;i<40;++i) {
      queue.push();
      queue.pop();
    }
    for(int i=0;i<50;++i)
      queue.push(i);
        
    queue.resize(120);
    for(int i=0;i<50;++i) {
      TEST(queue.top()==i);
      queue.pop();
    }
  }
}

void queue_test() {
  ENTER_TEST("template class Queue<T> (with T=int)");

  test_Empty_Push();
  test_FIFO();
  test_Size();
  test_Shrink_OB_OA();
  test_Shrink_NOB_OA();
  test_Shrink_NOB_NOA();
  test_Expand_OB();
  test_Expand_NOB();
}
