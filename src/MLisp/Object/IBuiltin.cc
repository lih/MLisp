#include "MLisp/Environment.hh"
#include "MLisp/Object/IBuiltin.hh"
#include "MLisp/Object/Continuation.hh"

using namespace MLisp;
using namespace Object;

void IBuiltin::call(WeakRef<ICstList> _args,bool _tail) const {
  if(_tail)
    s_curEnv->returnWith(call(_args));
  else
    s_curEnv->pushStack(call(_args));
}

void IBuiltin::print() const {
  printf("@%s",typeName());
}
