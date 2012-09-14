#include "MLisp/Environment.hh"
#include "MLisp/Operation/Close.hh"
#include "MLisp/Object/Lambda.hh"

using namespace MLisp;
using namespace Operation;
using namespace Object;

const OpCode     Close::s_opCode=CLOSE;
const OperationType  Close::s_instance=Close::call;

void Close::call(int _arg,bool _tail) {
  Ref<Lambda> ret=WeakRef<Lambda::Closure>(s_curEnv->frame().object(_arg))->close();

  if(_tail)
    s_curEnv->returnWith(ret);
  else
   s_curEnv->pushStack(ret);
}

