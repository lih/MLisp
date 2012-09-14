#include "MLisp/CompileState.hh"
#include "MLisp/Object/SpecialForm/Prog1.hh"
#include "MLisp/Operation/Ignore.hh"

using namespace MLisp;
using namespace Object;
using namespace SpecialForm;
using namespace Operation;

Prog1 Prog1::ms_instance(staticLeafTag);

void Prog1::compileCall(WeakRef<ICstList> _args,CompileState* _st) const {
  bool tail=_st->tail;
  _st->tail=false;
  
  _args->head()->compile(_st);
  _args=_args->tail();
  _args->head()->compile(_st);
  _st->code.pushBack(Ignore::s_opCode,Instruction::MAX_ARG,tail);  
  
  _st->tail=tail;
}
