#include "MLisp/Environment.hh"
#include "MLisp/Operation/Arg.hh"
#include "MLisp/Object/Continuation.hh"

using namespace MLisp;
using namespace Operation;
using namespace Object;

const OpCode    Arg::s_opCode=ARG;
const OperationType Arg::s_instance=Arg::call;

void Arg::call(int _arg,bool _tail) {
  if(_tail)
    s_curEnv->returnWith(s_curEnv->frame().param(_arg)->value());
  else
    s_curEnv->pushStack(s_curEnv->frame().param(_arg)->value());
}

const OpCode    ArgSym::s_opCode=ARG_SYM;
const OperationType ArgSym::s_instance=ArgSym::call;

void ArgSym::call(int _arg,bool _tail) {
  if(_tail)
    s_curEnv->returnWith(s_curEnv->frame().param(_arg));
  else
    s_curEnv->pushStack(s_curEnv->frame().param(_arg));
}

const OpCode       ClosedArg::s_opCode=CLOSED_ARG;
const OperationType ClosedArg::s_instance=ClosedArg::call;

void ClosedArg::call(int _arg,bool _tail) {
  if(_tail)
    s_curEnv->returnWith(s_curEnv->frame().closed(_arg)->value());
  else
    s_curEnv->pushStack(s_curEnv->frame().closed(_arg)->value());
}

const OpCode          ClosedArgSym::s_opCode=CLOSED_ARG_SYM;
const OperationType ClosedArgSym::s_instance=ClosedArgSym::call;

void ClosedArgSym::call(int _arg,bool _tail) {
  if(_tail)
    s_curEnv->returnWith(s_curEnv->frame().closed(_arg));
  else
    s_curEnv->pushStack(s_curEnv->frame().closed(_arg));
}

