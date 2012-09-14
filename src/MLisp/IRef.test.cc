#include "MLisp/IRef.test.hh"
#include "MLisp/IRef.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Object/Integer.hh"
#include "MLisp/Object/Pair.hh"
#include "MLisp/Object/Nil.hh"

#include "TestMacros.hh"

using namespace MLisp;
using namespace Object;

namespace {
  void testCycleCollection() {
    ENTER_TEST("cycle collection");
    
    int  objCount=IObject::countAllocated();
    Ref<ICstList> cur=Pair::create(Integer::create(10),Nil::instance());
    Ref<IList>    tail=cur;
    
    for(int i=0;i<10;++i)
      cur=Pair::create(Integer::create(i),cur);
    tail->setTail(cur);
    
    cur.reset(NULL);
    tail.reset(NULL);
    
    IRef::collectCycles();

    TEST(objCount==IObject::countAllocated());
  }
}

void IRef_test () {
  ENTER_TEST("internal reference type");

  testCycleCollection();
}
