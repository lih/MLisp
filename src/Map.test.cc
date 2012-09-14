#include "Map.test.hh"
#include "Map.hh"

#include "TestMacros.hh"

#include <cstdlib>

using namespace Utils;

namespace {
  void test_Element() {
    ENTER_TEST("element assignation and retrieval");

#define NELEMS 1000    
    Map<int,int> map;
    int indices[NELEMS];
    int values[NELEMS];

    for(int i=0;i<NELEMS;++i) {
      indices[i]=rand();
      values[i]=(map.contains(indices[i])?0:rand());
      map[indices[i]]=values[i];
    }

    for(int i=0;i<NELEMS;++i)
      if(values[i]!=0)
        TEST(map[indices[i]]==values[i]);
#undef NELEMS
  }
}

void map_test() {
  ENTER_TEST("template class Map<U,V> (with U=V=int)");

  test_Element();
}
