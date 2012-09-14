#include "MLisp/IObject.hh"
#include "MLisp/Operation/Const.hh"

#include <cstdlib> // for functions malloc() and free()

#include "Pool.hh"
#include "Array.hh"

using namespace MLisp;
using namespace Utils;

namespace {
  Pool  ms_pools[7]={
    Pool(2*sizeof(void*)),
    Pool(3*sizeof(void*)),
    Pool(4*sizeof(void*)),
    Pool(5*sizeof(void*)),
    Pool(6*sizeof(void*)),
    Pool(7*sizeof(void*)),
    Pool(8*sizeof(void*))};
  
  struct BigObj {
    BigObj* prev;
    BigObj* next;
    int     val[0];
  };
  BigObj ms_bigObjs={&ms_bigObjs,&ms_bigObjs,{}};
}

const IObject::LeafTag        IObject::leafTag={};
const IObject::StaticLeafTag IObject::staticLeafTag={};
int IObject::ms_nAllocated=0;

void IObject::compile(CompileState* _st) const {
  Operation::Const::compileObject(const_cast<IObject*>(this),_st);
}
void IObject::print() const {
  printf("#<%s>",typeName());
}

void* IObject::operator new(size_t _size) {
  ++ms_nAllocated;
  int ind=_size/sizeof(void*) - 2;

  if(ind<7)
    return ms_pools[ind].allocate();
  else {
    BigObj* newObj=static_cast<BigObj*>(malloc(sizeof(BigObj)+_size));
    newObj->next=ms_bigObjs.next;
    newObj->prev=&ms_bigObjs;
    ms_bigObjs.next=newObj;
    return newObj->val;
  }
}
#pragma GCC diagnostic ignored "-Wpointer-arith"
void IObject::operator delete(void* _p,size_t _size) {
  --ms_nAllocated;
  size_t ind=_size/sizeof(void*)-2;
  if(ind<8) ms_pools[ind].free(_p);
  else {
    BigObj* cur=static_cast<BigObj*>(_p-sizeof(BigObj));
    cur->prev->next=cur->next;
    cur->next->prev=cur->prev;
    free(cur);
  }
}
#pragma GCC diagnostic warning "-Wpointer-arith"

int IObject::countAllocated() { return ms_nAllocated; }
