#include "Set.test.hh"
#include "Set.hh"

#include "TestMacros.hh"

#include <cstdlib>
#include <ctime>

using namespace Utils;

namespace {
  void test_Singleton() {
    ENTER_TEST("singleton set");
    
    Set<int> set;

    set.insert(23);

    TEST(set.contains(23));
  }
  void test_Pair() {
    ENTER_TEST("pair set");
    
    Set<int> set;

    set.insert(23);
    TEST(set.insert(1278));

    TEST(set.contains(23));
    TEST(set.contains(1278));
  }
  void test_Triple() {
    ENTER_TEST("triple set");

    { // insertion in 1-2-3  
      ENTER_TEST("insertion in 1-2-3");
      Set<int> set;
      set.insert(1);
      set.insert(2);
      set.insert(3);
      TEST(set.contains(1));
      TEST(set.contains(2));
      TEST(set.contains(3));
    }
    { // insertion in 1-3-2
      ENTER_TEST("insertion in 1-3-2"); 
      Set<int> set;
      set.insert(1);
      set.insert(3);
      set.insert(2);
      TEST(set.contains(1));
      TEST(set.contains(2));
      TEST(set.contains(3));
    }
    { // insertion in 2-1-3
      ENTER_TEST("insertion in 2-1-3");
      Set<int> set;
      set.insert(2);
      set.insert(1);
      set.insert(3);
      TEST(set.contains(1));
      TEST(set.contains(2));
      TEST(set.contains(3));
    }
    { // insertion in 2-3-1
      ENTER_TEST("insertion in 2-3-1");
      Set<int> set;
      set.insert(2);
      set.insert(3);
      set.insert(1);
      TEST(set.contains(1));
      TEST(set.contains(2));
      TEST(set.contains(3));
    }
    { // insertion in 3-1-2
      ENTER_TEST("insertion in 3-1-2");
      Set<int> set;
      set.insert(3);
      set.insert(1);
      set.insert(2);
      TEST(set.contains(1));
      TEST(set.contains(2));
      TEST(set.contains(3));
    }
    { // insertion in 3-2-1
      ENTER_TEST("insertion in 3-2-1");
      Set<int> set;
      set.insert(3);
      set.insert(2);
      set.insert(1);
      TEST(set.contains(1));
      TEST(set.contains(2));
      TEST(set.contains(3));
    }
  }
  void test_Insert_Many_InOrder() {
    ENTER_TEST("insertion of many elements in order");
    
    Set<int> set;

    for(int i=0;i<1000;++i)
      set.insert(i);

    for(int i=0;i<1000;++i)
      TEST(set.contains(i));

    for(int i=1000;i<2000;++i)
      TEST(!set.contains(i));
  }
  void test_Insert_Many_Random() {
    ENTER_TEST("insertion of many random elements");
    
#define MANY 1000
    int values[MANY];
    Set<int> set;

    for(int i=0;i<MANY;++i) {
      values[i]=rand();
      set.insert(values[i]);
    }

    for(int i=0;i<MANY;++i)
      TEST(set.contains(values[i]));
#undef MANY
  }
  void test_Insert_Already_Present () {
    ENTER_TEST("insertion of elements already present in the set");
    
    Set<int> set;

#define MANY 100
    for(int i=0;i<MANY;++i)
      set.insert(i);
    
    for(int i=0;i<MANY;++i)
      TEST(!set.insert(i));

#undef MANY
  }
  void test_Single_Iterator() {
    ENTER_TEST("singleton iterator");

    Set<int> set;
    set.insert(34525);
    Set<int>::Iterator it=set.begin();
    TEST(*it==34525);
  }
  void test_Pair_Iterator() {
    ENTER_TEST("pair iterator");

    { // Test in descending order
      ENTER_TEST("descending order");
      Set<int> set;
      set.insert(34525);
      set.insert(234);
      Set<int>::Iterator it=set.begin();
      TEST(*it==234);
      ++it;
      TEST(it!=set.end());
      TEST(*it==34525);
    }
    { // Test in ascending order
      ENTER_TEST("ascending order");
      Set<int> set; 
      set.insert(34525);
      set.insert(56234);
      Set<int>::Iterator it=set.begin();
      TEST(*it==34525);
      ++it;
      TEST(*it==56234);
    }
  }
  void test_Iterator() {
    ENTER_TEST("iterator");

    Set<int> set;
    
#define MANY 1000
    for(int i=0;i<MANY;++i)
      set.insert(i);

    Set<int>::Iterator it=set.begin();

    for(int i=0;i<MANY;++i) {
      TEST(it!=set.end());
      TEST(*it==i);
      ++it;
    }
#undef MANY    
  }
}

void set_test() {
  ENTER_TEST("template class Set<T> (with T=int)");

  srand(time(NULL));

  test_Singleton();
  test_Pair();
  test_Triple();
  test_Insert_Many_InOrder();
  test_Insert_Many_Random();
  test_Single_Iterator();
  test_Pair_Iterator();
  test_Iterator();
  test_Insert_Already_Present();
}
