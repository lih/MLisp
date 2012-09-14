#include "MLisp/Object/String.hh"
#include "MLisp/Object/Integer.hh"
#include "MLisp/Operation/Const.hh"

#include <cstring>
#include <cstdio>

using namespace MLisp;
using namespace Object;

#define SMALL_STRING_THRESHOLD 64

namespace {
  Pool s_pool(SMALL_STRING_THRESHOLD);

  char* allocate(int _size) {
    if(_size<=SMALL_STRING_THRESHOLD)
      return reinterpret_cast<char*>(s_pool.allocate());
    else
      return new char[_size];
  }
  void free(char* _ptr,int _size) {
    if(_size<=SMALL_STRING_THRESHOLD)
      s_pool.free(_ptr);
    else
      delete[] _ptr;
  }
}

String::String(const char* _data) : m_size(strlen(_data)) {
  m_data = allocate(m_size+1);
  strcpy(m_data,_data);
}

Ref<IObject> String::elt(int _index) const {
  return Integer::create(m_data[_index]);
}
void         String::setElt(int _index,WeakRef<IObject> _val) {
  WeakRef<Integer> val(_val);
  
  if(val.isNull())
    throw ERROR("wrong type argument (expected integer/character)");
  else 
    m_data[_index]=val->value();
}

void  String::print() const {
  printf("\"%s\"",m_data);
}
bool  String::operator==(const IObject& _other) const {
  WeakRef<const String> other=weakRef(&_other);
  if(other.isNull())
    return false;
  else todo;
}

String::~String() {
  free(m_data,m_size+1);
}
