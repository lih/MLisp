#ifndef INCLUDED_MLISP_OBJECT_TRUE_HH
#define INCLUDED_MLISP_OBJECT_TRUE_HH

#include "MLisp/IObject.hh"
#include "MLisp/Ref.hh"

namespace MLisp {
  namespace Object {
    class True : public IObject {
      NOT_COPYABLE(True);
      
      static True ms_instance;

      True(StaticLeafTag _) : IObject(_) {}

    private:
      void pushChildren(ObjectQueue*) const {}

    public:
      static WeakRef<True> instance() {
        return weakRef(&ms_instance);
      }

    public:
      // IObject interface
      const char* typeName() const {
        return "cst:True";
      }
    };
  }
}

#endif // INCLUDED_MLISP_OBJECT_TRUE_HH
