#ifndef INCLUDED_MLISP_SPECIAL_FORM_QUOTE_HH
#define INCLUDED_MLISP_SPECIAL_FORM_QUOTE_HH

#include "Utils.hh"
#include "MLisp/Object/ISpecialForm.hh"
#include "MLisp/Ref.hh"

namespace MLisp {
  namespace Object {
    namespace SpecialForm {
      class Quote : public ISpecialForm {
        NOT_COPYABLE(Quote);
        Quote(StaticLeafTag _) : ISpecialForm(_) {}

        static Quote ms_instance;
              
      public:
        // Quote interface
        static WeakRef<Quote> instance() {
          return weakRef(&ms_instance);
        }

      public:
        // ICompileCallable interface
        void compileCall(WeakRef<ICstList>,CompileState*) const;
      
      public:
        // IObject interface
        const char* typeName() const {
          return "special:quote";
        }
      };
    }
  }
}

#endif // INCLUDED_MLISP_SPECIAL_FORM_QUOTE_HH
