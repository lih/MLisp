#include "MLisp/Ref.hh"
#include "MLisp/Object/Array.hh"
#include "Pool.hh"

#include <cstdlib>

using namespace MLisp;
using namespace Object;

Array::Array(int _size) : m_size(_size),m_data(new Ref<IObject>[m_size]) {}
Array::Array(WeakRef<ICstList> _l) : m_size(_l->length()),m_data(new Ref<IObject>[m_size]) {
  for(int i=0;i<m_size;++i) {
    m_data[i]=_l->head();
    _l=_l->tail();
  }
}

void Array::pushChildren(ObjectQueue* _queue) const {
  for(int i=0;i<m_size;++i)
    _queue->push(m_data[i].ptr());
}
void Array::print() const {
  printf("[");
  if(m_size>0)
    m_data[0]->print();
  for(int i=1;i<m_size;++i) {
    printf(" ");
    m_data[i]->print();
  }
  printf("]");
}

Array::~Array() {
  delete[] m_data;
}
