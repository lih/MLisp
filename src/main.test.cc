#include "main.test.hh"

#include "Pool.test.hh"
#include "FlaggedPtr.test.hh"
#include "Array.test.hh"
#include "Stack.test.hh"
#include "Queue.test.hh"
#include "AVLTree.test.hh"
#include "Set.test.hh"
#include "Map.test.hh"
#include "MLisp/Environment.test.hh"

#include <cstdio>

void MLisp_test() {
  pool_test();
  flaggedPtr_test();
  array_test();
  stack_test();
  queue_test();
  AVLTree_test();
  set_test();
  map_test();
  environment_test();
  
  printf(">>>>>>>>>>>>>>> ALL PASSED !!! <<<<<<<<<<<<<<<<\n");
}
