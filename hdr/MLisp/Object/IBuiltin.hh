#ifndef INCLUDED_MLISP_OBJECT_I_BUILTIN_HH
#define INCLUDED_MLISP_OBJECT_I_BUILTIN_HH

#include "Utils.hh"
#include "MLisp/Object/ICallable.hh"

namespace MLisp {
  namespace Object {
    class IBuiltin : public ICallable {
      OBJECT_INTERFACE(IBuiltin,ICallable);

    public:
      // IObject interface
      virtual Ref<IObject> call(WeakRef<ICstList>) const abstract;

    public:
      // ICallable interface
      void call(WeakRef<ICstList>,bool) const;
      
    public:
      // IObject interface
      void pushChildren(ObjectQueue*) const {}
      void print() const;
    };
  }
}

#include "MLisp/Object/IBuiltin.def.hh"

#endif // INCLUDED_MLISP_OBJECT_I_BUILTIN_HH
