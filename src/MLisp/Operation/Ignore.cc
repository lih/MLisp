#include "MLisp/Environment.hh"
#include "MLisp/Operation/Ignore.hh"
#include "MLisp/Object/Continuation.hh"

using namespace MLisp;
using namespace Operation;
using namespace Object;

const OpCode  Ignore::s_opCode=IGNORE;
const OperationType Ignore::s_instance=Ignore::call;

void Ignore::call(int,bool _tail) {
  s_curEnv->popStack();
  if(_tail)
    s_curEnv->returnWith(s_curEnv->popStack());
}
