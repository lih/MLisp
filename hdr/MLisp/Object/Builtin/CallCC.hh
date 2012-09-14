#ifndef INCLUDED_MLISP_OBJECT_BUILTIN_CALL_CC_HH
#define INCLUDED_MLISP_OBJECT_BUILTIN_CALL_CC_HH

#include "MLisp/Object/IBuiltin.hh"

namespace MLisp {
  namespace Object {
    namespace Builtin {
      class CallCC : public IBuiltin {
        NOT_COPYABLE(CallCC);
        CallCC(StaticLeafTag _) : IBuiltin(_) {}
        
        static CallCC ms_instance;
        
      public:
        // CallCC interface
        static WeakRef<CallCC> instance() {
          return weakRef(&ms_instance);
        }
        
      public:
        // IBuiltin interface
        Ref<IObject> call(WeakRef<ICstList>) const noimpl;
        
      public:
        // ICallable interface
        void call(WeakRef<ICstList>,bool) const;

      public:
        // IObject interface
        const char* typeName() const {
          return "builtin:CallCC";
        }
      };
    }
  }
}

#endif // INCLUDED_MLISP_OBJECT_BUILTIN_CALL_CC_HH
