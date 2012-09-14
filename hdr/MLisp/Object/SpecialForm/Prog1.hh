#ifndef INCLUDED_MLISP_OBJECT_SPECIAL_FORM_PROGN_HH
#define INCLUDED_MLISP_OBJECT_SPECIAL_FORM_PROGN_HH

#include "Utils.hh"
#include "MLisp/Object/ISpecialForm.hh"
#include "MLisp/Ref.hh"

namespace MLisp {
  namespace Object {
    namespace SpecialForm {
      class Prog1 : public ISpecialForm {
        NOT_COPYABLE(Prog1);
        Prog1(StaticLeafTag _) : ISpecialForm(_) {}

        static Prog1 ms_instance;
              
      public:
        // Progn interface
        static WeakRef<Prog1> instance() {
          return weakRef(&ms_instance);
        }

      public:
        // ICompileCallable interface
        void compileCall(WeakRef<ICstList>,CompileState*) const;
      
      public:
        // IObject interface
        const char* typeName() const {
          return "special:prog1";
        }
      };
    }
  }
}

#endif // INCLUDED_MLISP_OBJECT_SPECIAL_FORM_PROGN_HH
