#include "FlaggedPtr.test.hh"
#include "FlaggedPtr.hh"

#include "TestMacros.hh"

namespace {
  void test_Assignation() {
    ENTER_TEST("assignation");
    
    bool flag=true;
    int dummy;
    int* ptr=&dummy;

    FlaggedPtr<int> fp(ptr,flag);
    FlaggedPtr<int> fp2=fp;

    TEST(flag==fp2.flag());
    TEST(ptr==fp2.ptr());
  }
}

void flaggedPtr_test() {
  ENTER_TEST("template class FlaggedPtr<T> (with T=int)");

  test_Assignation();
}
