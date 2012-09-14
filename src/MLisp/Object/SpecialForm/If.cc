#include "MLisp/CompileState.hh"
#include "MLisp/Object/SpecialForm/If.hh"
#include "MLisp/Operation/Forward.hh"
#include "MLisp/Object/Nil.hh"

using namespace MLisp;
using namespace Object;
using namespace SpecialForm;

If If::ms_instance(staticLeafTag);

void If::compileCall(WeakRef<ICstList> _args,CompileState* _st) const {
  /* An if call looks like this :
   *   (if <cond> <then> <else>)
   *     ==> <cond>
   *         ForwardIfNil size(<then>)+(1 if tail else 0)
   *         <then>
   *         [ Forward size(else) ] if tail
   *         <else>
   */
  
  bool tail=_st->tail;
  
  // Compiles the condition
  _st->tail=false;
  _args->head()->compile(_st);
  _args=_args->tail();
  
  // Make room for the jump instruction
  int offCondJmp=_st->code.size();
  _st->code.pushBack(Operation::ForwardIfNil::s_opCode,0,false);
  
  // Compiles the then-form
  _st->tail=tail;
  _args->head()->compile(_st);
  _args=_args->tail();
  
  // Marks the place of the second jump
  if(!tail)
    _st->code.pushBack(Operation::Forward::s_opCode,0,false);
  int offThenJmp=_st->code.size();
  _st->code[offCondJmp].arg=offThenJmp-offCondJmp-1;

  // Compiles the else-form
  _args->head()->compile(_st);

  // Completes the second jump if needed
  if(!tail)
    _st->code[offThenJmp].arg=_st->code.size()-offThenJmp-1;
}
