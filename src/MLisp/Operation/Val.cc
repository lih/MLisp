#include "MLisp/Environment.hh"
#include "MLisp/CompileState.hh"
#include "MLisp/Operation/Val.hh"
#include "MLisp/Object/Continuation.hh"

using namespace MLisp;
using namespace Operation;
using namespace Object;

const OpCode Val::s_opCode=VAL;
const OperationType Val::s_instance=Val::call;

namespace {
  class UnboundSym : public Error {
    char m_data[256];
    
  public:
    UnboundSym(WeakRef<Symbol> _sym) {
      snprintf(m_data,256,"%s : unbound symbol.",_sym->name()->data());
    }

    const char* what() const throw() {
      return m_data;
    }
  };
}

void Val::call(int _arg,bool _tail) {
  WeakRef<Symbol> sym=s_curEnv->frame().object(_arg);
  if(!sym->isBound()) 
    throw UnboundSym(sym);
  
  if(_tail)
    s_curEnv->returnWith(sym->value());
  else 
    s_curEnv->pushStack(sym->value());
}

void Val::compileObject(Symbol* _obj,CompileState* _st) {
  _st->code.pushBack(s_opCode,_st->objectsUsed[_obj],_st->tail);
}
