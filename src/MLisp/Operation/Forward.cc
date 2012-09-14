#include "MLisp/Environment.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Operation/Forward.hh"
#include "MLisp/Object/Continuation.hh"
#include "MLisp/Object/Nil.hh"

using namespace MLisp;
using namespace Operation;
using namespace Object;

const OpCode    Forward::s_opCode=FORWARD;
const OperationType Forward::s_instance=Forward::call;

const OpCode    ForwardIfNil::s_opCode=FORWARD_IF_NIL;
const OperationType ForwardIfNil::s_instance=ForwardIfNil::call;

void Forward::call(int _arg,bool) {
  s_curEnv->forward(_arg);
}

void ForwardIfNil::call(int _arg,bool) {
  if(s_curEnv->popStack()->is<Nil>())
    s_curEnv->forward(_arg);
}
