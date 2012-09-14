#ifndef INCLUDED_MLISP_OBJECT_SPECIAL_FORM_IF_HH
#define INCLUDED_MLISP_OBJECT_SPECIAL_FORM_IF_HH

#include "Utils.hh"
#include "MLisp/Object/ISpecialForm.hh"
#include "MLisp/Ref.hh"

namespace MLisp {
  namespace Object {
    namespace SpecialForm {
      class If : public ISpecialForm {
        NOT_COPYABLE(If);
        If(StaticLeafTag _)  : ISpecialForm(_) {}

        static If ms_instance;
        
      public:
        // If interface
        static WeakRef<If> instance() {
          return weakRef(&ms_instance);
        }

      public:
        // ICompileCallable interface
        void compileCall(WeakRef<ICstList>,CompileState*) const;
        
      public:
        // IObject interface
        const char* typeName() const {
          return "special:if";
        }
      };
    }
  }
}

#endif // INCLUDED_MLISP_OBJECT_SPECIAL_FORM_IF_HH
