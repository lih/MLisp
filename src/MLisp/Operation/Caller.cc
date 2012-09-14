#include <cstdio>
#include "MLisp/Environment.hh"
#include "MLisp/Operation/Caller.hh"
#include "MLisp/Object/Continuation.hh"

using namespace MLisp;
using namespace Operation;
using namespace Object;

const OpCode    Caller::s_opCode=CALLER;
const OperationType Caller::s_instance=Caller::call;

namespace {
  class NotCallable : public Error {
    char m_data[256];
    
  public:
    NotCallable(WeakRef<IObject> _obj) {
      snprintf(m_data,256,"Cannot call non-callable type %s.",_obj->typeName());
    }
    
    const char* what() const throw() {
      return m_data;
    }
  };
}

void Caller::call(int _nargs,bool _tail) {
  Ref<IObject>       obj=s_curEnv->popStack();
  WeakRef<ICallable> fun=obj;
  
  if(!fun.isNull()) {
    Ref<ICstList> args=s_curEnv->popStack(_nargs);
    fun->call(args,_tail);
  }
  else
    throw NotCallable(obj);
}

