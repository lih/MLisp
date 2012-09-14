#include "MLisp/CompileState.hh"
#include "MLisp/Object/Pair.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/Object/ICallable.hh"
#include "MLisp/Operation/Caller.hh"

using namespace MLisp;
using namespace Operation;
using namespace Object;

int  Pair::length() const {
  WeakRef<const Pair> cur(this);
  int ret=0;

  while(!cur.isNull()) {
    ++ret;
    cur=cur->tail();
  }

  return ret;
}
Ref<ICstList> Pair::reverse() const {
  Ref<ICstList> ret=Nil::instance();
  WeakRef<const IList> cur(this);
  
  while(!cur.isNull()) {
    ret=create(cur->head(),ret);
    cur=cur->tail();
  }
    
  return ret;
}
Ref<IObject>  Pair::append(WeakRef<IObject> _obj) const {
  Ref<ICstList> rev=reverse();
  Ref<IObject> ret=_obj;
  
  while(!rev->is<Nil>()) {
    ret=create(rev->head(),ret);
    rev=rev->tail();
  }

  return ret;
}

void Pair::compile(CompileState* _st) const {
  if(m_head->is<ICompileCallable>())
    WeakRef<ICompileCallable>(m_head)->compileCall(tail(),_st);
  else {
    Ref<IList> cur=reverse();
    bool tail=_st->tail;
    _st->tail=false;

    while(!cur.isNull()) {
      cur->head()->compile(_st);
      cur=cur->tail();
    }
 
    _st->code.pushBack(Caller::s_opCode,length()-1,tail);
    _st->tail=tail;
  }
}

void Pair::print() const {
  printf("(");
  
  head()->print();
  WeakRef<IObject> tail=this->tail(); 
  while(tail->is<Pair>()) {
    printf(" ");
    WeakRef<Pair>(tail)->head()->print();
    tail=WeakRef<Pair>(tail)->tail();
  }
  
  if(!tail->is<Nil>()) {
    printf(" . ");
    tail->print();
  }
  printf(")");
}
bool Pair::operator==(const IObject& _other) const {
  WeakRef<const Pair> other(&_other);
  if(other.isNull())
    return false;
  else {
    return *other->m_head==*m_head && *other->m_tail==*m_tail;
  }
}
