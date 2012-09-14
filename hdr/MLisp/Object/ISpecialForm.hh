#ifndef INCLUDED_MLISP_I_SPECIAL_FORM_HH
#define INCLUDED_MLISP_I_SPECIAL_FORM_HH

#include "MLisp/Object/ICallable.hh"

namespace MLisp {
  namespace Object {
    class ISpecialForm : public ICompileCallable {
      OBJECT_INTERFACE(ISpecialForm,ICompileCallable);

    public:
      // IObject interface
      void pushChildren(ObjectQueue*) const {}
    };
  }
}

#endif // INCLUDED_MLISP_I_SPECIAL_FORM_HH
