#include "MLisp/Environment.hh"
#include "MLisp/CompileState.hh"
#include "MLisp/Object/Macro.hh"
#include "MLisp/Object/Continuation.hh"

using namespace MLisp;
using namespace Object;

void Macro::compileCall(WeakRef<ICstList> _args,CompileState* _st) const {
  Ref<Continuation> cc=Continuation::create();

  s_curEnv->resetFrame();
  m_lambda->call(_args,false);
  Ref<IObject> ret=s_curEnv->eval();
  // printf("\nExpansion : "); ret->print(); printf("\n");
  ret->compile(_st);
  cc->call();
}

void Macro::print() const {
  printf("#(macro "); m_lambda->print(); printf(")");
}
