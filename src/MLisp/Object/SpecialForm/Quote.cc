#include "MLisp/CompileState.hh"
#include "MLisp/Object/SpecialForm/Quote.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/Operation/Arg.hh"
#include "MLisp/Operation/Const.hh"

using namespace MLisp;
using namespace Object;
using namespace SpecialForm;
using namespace Operation;

Quote Quote::ms_instance(staticLeafTag);

void Quote::compileCall(WeakRef<ICstList> _args,CompileState* _st) const {
  if(!_args->tail()->is<Nil>())
    throw ERROR("too many arguments for quote (expected 1).");
  if(_args->is<Nil>())
    throw ERROR("too few arguments for quote (expected 1).");
  
  if(_st->params.contains(_args->head().ptr()))
    _st->code.pushBack(ArgSym::s_opCode,
                       _st->params[_args->head().ptr()],
                       _st->tail);
  else if(_st->closableArgs.contains(_args->head().ptr()))
    _st->code.pushBack(ClosedArgSym::s_opCode,
                       _st->closedArgs[_args->head().ptr()],
                       _st->tail);
  else
    _st->code.pushBack(Const::s_opCode,
                       _st->objectsUsed[_args->head().ptr()],
                       _st->tail);
}
