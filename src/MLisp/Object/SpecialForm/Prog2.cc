#include "MLisp/CompileState.hh"
#include "MLisp/Object/SpecialForm/Prog2.hh"
#include "MLisp/Operation/Ignore.hh"

using namespace MLisp;
using namespace Object;
using namespace SpecialForm;
using namespace Operation;

Prog2 Prog2::ms_instance(staticLeafTag);

void Prog2::compileCall(WeakRef<ICstList> _args,CompileState* _st) const {
  bool tail=_st->tail;

  _st->tail=false;

  _args->head()->compile(_st);
  _args=_args->tail();
  _st->code.pushBack(Ignore::s_opCode);  
  
  _st->tail=tail;
  
  _args->head()->compile(_st);
}
