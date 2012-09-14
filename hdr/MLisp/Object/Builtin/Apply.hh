#ifndef INCLUDED_MLISP_OBJECT_BUILTIN_APPLY_HH
#define INCLUDED_MLISP_OBJECT_BUILTIN_APPLY_HH

#include "MLisp/Object/IBuiltin.hh"

namespace MLisp {
  namespace Object {
    namespace Builtin {
      class Apply : public IBuiltin {
      private:
        // Constructors & Destructors
        NOT_COPYABLE(Apply);
        Apply(StaticLeafTag _) : IBuiltin(_) {}

      private:
        // Static variables
        static Apply ms_instance;
        
      public:
        // Apply interface
        static WeakRef<Apply> instance() {
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
          return "builtin:Apply";
        }
      };
    }
  }
}

#endif // INCLUDED_MLISP_OBJECT_BUILTIN_APPLY_HH
