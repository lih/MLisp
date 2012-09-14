#ifndef INCLUDED_MLISP_I_ARRAY_HH
#define INCLUDED_MLISP_I_ARRAY_HH

#include "MLisp/IObject.hh"

namespace MLisp {
  namespace Object {
    class IArray : public IObject {
      OBJECT_INTERFACE(IArray,IObject);

    public:
      virtual Ref<IObject> elt(int) const abstract;
      virtual void         setElt(int,WeakRef<IObject>) abstract;
  
      virtual int size() const abstract;
    };
  }
}

#endif // INCLUDED_MLISP_I_ARRAY_HH
