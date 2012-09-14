#include "MLisp/Environment.hh"
#include "MLisp/CompileState.hh"
#include "MLisp/Operation/Const.hh"
#include "MLisp/Object/Continuation.hh"

using namespace MLisp;
using namespace Operation;

const OpCode     Const::s_opCode=CONST;
const OperationType  Const::s_instance=Const::call;

void Const::call(int _arg,bool _tail) {
  Ref<IObject> ret=s_curEnv->frame().object(_arg);
  if(_tail)
    s_curEnv->returnWith(ret);
  else
    s_curEnv->pushStack(ret);
}

void Const::compileObject(IObject* _obj,CompileState* _st) {
  _st->code.pushBack(s_opCode,_st->objectsUsed[_obj],_st->tail);
}
