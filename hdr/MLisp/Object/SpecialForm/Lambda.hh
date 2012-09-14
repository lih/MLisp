#ifndef INCLUDED_MLISP_OBJECT_SPECIAL_FORM_LAMBDA_HH
#define INCLUDED_MLISP_OBJECT_SPECIAL_FORM_LAMBDA_HH

#include "Utils.hh"
#include "MLisp/Object/ISpecialForm.hh"
#include "MLisp/Ref.hh"

namespace MLisp {
  namespace Object {
    namespace SpecialForm {
      class Lambda : public ISpecialForm {
        NOT_COPYABLE(Lambda);
        Lambda(StaticLeafTag _)  : ISpecialForm(_) {}

        static Lambda ms_instance;
        
      public:
        // Lambda interface
        static WeakRef<Lambda> instance() {
          return weakRef(&ms_instance);
        }

      public:
        // ICompileCallable interface
        void compileCall(WeakRef<ICstList>,CompileState*) const;
      
      public:
        // IObject interface
        const char* typeName() const {
          return "special:lambda";
        }
      };
    }
  }
}

#endif // INCLUDED_MLISP_OBJECT_SPECIAL_FORM_LAMBDA_HH
