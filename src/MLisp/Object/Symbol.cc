#include "MLisp/CompileState.hh"
#include "MLisp/Object/Symbol.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/Operation/Val.hh"
#include "MLisp/Operation/Caller.hh"
#include "MLisp/Operation/Arg.hh"

using namespace MLisp;
using namespace Object;
using namespace Operation;

void Symbol::compile(CompileState* _st) const {
  IObject* me=const_cast<Symbol*>(this);
  if(_st->params.contains(me))
    _st->code.pushBack(Arg::s_opCode,_st->params[me],_st->tail);
  else if(_st->closableArgs.contains(me)) 
    _st->code.pushBack(ClosedArg::s_opCode,_st->closedArgs[me],_st->tail);
  else
    _st->code.pushBack(Val::s_opCode,_st->objectsUsed[me],_st->tail);
}

void Symbol::compileCall(WeakRef<ICstList> _args,CompileState* _st) const {
  if(m_value->is<ICompileCallable>())
    WeakRef<ICompileCallable>(m_value)->compileCall(_args,_st);
  else {
    Ref<ICstList> cur=_args->reverse();
    bool tail=_st->tail;
    _st->tail=false;

    while(!cur->is<Nil>()) {
      cur->head()->compile(_st);
      cur=cur->tail();
    }
    compile(_st);
    _st->code.pushBack(Caller::s_opCode,_args->length(),tail);
    _st->tail=tail;
  }
}

void Symbol::print() const {
  printf("%s",m_name->data());
}
