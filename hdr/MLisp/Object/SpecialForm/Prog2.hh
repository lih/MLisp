#ifndef INCLUDED_MLISP_OBJECT_SPECIAL_FORM_PROG2_HH
#define INCLUDED_MLISP_OBJECT_SPECIAL_FORM_PROG2_HH

#include "Utils.hh"
#include "MLisp/Object/ISpecialForm.hh"
#include "MLisp/Ref.hh"

namespace MLisp {
  namespace Object {
    namespace SpecialForm {
      class Prog2 : public ISpecialForm {
        NOT_COPYABLE(Prog2);
        Prog2(StaticLeafTag _) : ISpecialForm(_) {}

        static Prog2 ms_instance;
              
      public:
        // Prog2 interface
        static WeakRef<Prog2> instance() {
          return weakRef(&ms_instance);
        }

      public:
        // ICompileCallable interface
        void compileCall(WeakRef<ICstList>,CompileState*) const;
      
      public:
        // IObject interface
        const char* typeName() const {
          return "special:prog2";
        }
      };
    }
  }
}

#endif // INCLUDED_MLISP_OBJECT_SPECIAL_FORM_PROG2_HH
