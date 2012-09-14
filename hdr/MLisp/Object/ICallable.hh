#ifndef INCLUDED_MLISP_I_CALLABLE_HH
#define INCLUDED_MLISP_I_CALLABLE_HH

#include "Utils.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Object/IList.hh"

namespace MLisp {
  namespace Object {
    class ICompileCallable : public IObject {
      OBJECT_INTERFACE(ICompileCallable,IObject);
    
    public:
      virtual void compileCall(WeakRef<ICstList>,CompileState*) const abstract;
    };
  
    class ICallable : public IObject {
      OBJECT_INTERFACE(ICallable,IObject);

    public:
      virtual void call(WeakRef<ICstList>,bool) const abstract;
    };
  }
}

#endif // INCLUDED_MLISP_I_CALLABLE_HH
