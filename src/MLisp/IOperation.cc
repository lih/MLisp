#include "MLisp/Object/Continuation.hh"
#include "MLisp/Object/Lambda.hh"
#include "MLisp/Object/IList.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/IOperation.hh"
#include "MLisp/Operation/Val.hh"
#include "MLisp/Operation/Const.hh"
#include "MLisp/Operation/Caller.hh"
#include "MLisp/Operation/Forward.hh"
#include "MLisp/Operation/Ignore.hh"
#include "MLisp/Operation/Arg.hh"
#include "MLisp/Operation/Close.hh"

using namespace MLisp;
using namespace Operation;
using namespace Object;

const OperationType MLisp::s_ops[SIZE]={
  Caller::s_instance,
  Const::s_instance,
  ArgSym::s_instance,
  ClosedArgSym::s_instance,
  Val::s_instance,
  Arg::s_instance,
  ClosedArg::s_instance,
  Forward::s_instance,
  ForwardIfNil::s_instance,
  Ignore::s_instance,
  Close::s_instance
};

namespace {
  const char* opcodeStr(OpCode _op) {
    switch(_op) {
    case CALLER:            return "call";
    case FORWARD:           return "fwd";
    case FORWARD_IF_NIL:    return "fwdn";
    case CONST:             return "cst";
    case ARG_SYM:           return "argsym";
    case CLOSED_ARG_SYM:    return "cargsym";
    case VAL:               return "val";
    case ARG:               return "arg";
    case CLOSED_ARG:        return "carg";
    case IGNORE:            return "ign";
    case CLOSE:             return "close";
    case SIZE:              return "unknown";
    }
    throw "impossible";
  }
}
void Instruction::print() const {
  if(tail) printf(">");
  printf("%s",opcodeStr(opCode));
  if(arg!=MAX_ARG)
    printf(" %d",arg);
}
