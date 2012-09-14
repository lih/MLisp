#ifndef INCLUDED_MLISP_NIL_HH
#define INCLUDED_MLISP_NIL_HH

#include "MLisp/Ref.hh"
#include "MLisp/Object/IList.hh"

namespace MLisp {
  namespace Object {
    class Nil : public ICstList {
      NOT_COPYABLE(Nil);
      static Nil ms_instance;
    
      void pushChildren(ObjectQueue*) const {}
  
      Nil(StaticLeafTag _) : ICstList(_) {}
    
    public:
      // Nil interface
      static WeakRef<Nil> instance() {
        return weakRef(&ms_instance);
      }

    public:
      // ICstList interface
      WeakRef<IObject> head() const {
        return instance();
      }
      WeakRef<IObject> tail() const {
        return instance();
      }

      int  length() const { 
        return 0; 
      }
      Ref<ICstList> reverse() const { 
        return instance();
      }
      Ref<IObject>  append(WeakRef<IObject> _obj) const {
        return _obj;
      }
 
    public:
      // IObject interface
      const char* typeName() const {
        return "cst:nil";
      }
    };
  }
}

#endif // INCLUDED_MLISP_NIL_HH
