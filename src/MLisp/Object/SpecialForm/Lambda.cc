#include "MLisp/CompileState.hh"
#include "MLisp/Object/SpecialForm/Lambda.hh"
#include "MLisp/Operation/Close.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/Object/Lambda.hh"

namespace MLisp {
  namespace Object {
    namespace SpecialForm {
      Lambda Lambda::ms_instance(staticLeafTag);
      
      typedef Object::Lambda Function;

      void Lambda::compileCall(WeakRef<ICstList> _args,CompileState* _st) const {
        WeakRef<IObject> argList=_args->head();
        _args=_args->tail();
        Ref<Function::Closure> l=Function::Closure::create(_args->head(),argList,_st);
        
        _st->newObjects.add(l);
        _st->code.pushBack(Operation::Close::s_opCode,_st->objectsUsed[l.ptr()],_st->tail);
      }
    }
  }
}
