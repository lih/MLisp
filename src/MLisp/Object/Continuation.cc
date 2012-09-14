#include "MLisp/Environment.hh"
#include "MLisp/Object/Continuation.hh"
#include "MLisp/Object/Nil.hh"

using namespace MLisp;
using namespace Object;

Continuation::Continuation() : 
  Environment::Continuation(*s_curEnv) {}

void Continuation::pushChildren(ObjectQueue* _q) const {
  _q->push(m_frame.ptr());
  _q->push(m_stack.ptr());
}

void Continuation::call(WeakRef<ICstList> _args,bool) const {
  Ref<IObject> arg=_args->head();
  Environment::Continuation::call();
  s_curEnv->pushStack(arg);
}
