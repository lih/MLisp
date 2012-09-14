#ifndef INCLUDED_ILIST_HH
#define INCLUDED_ILIST_HH

#include "Utils.hh"
#include "MLisp/IObject.hh"
#include "MLisp/Ref.hh"

namespace MLisp { 
  namespace Object {
    class ICstList : public IObject {
      OBJECT_INTERFACE(ICstList,IObject);

    public:
      virtual WeakRef<IObject>   head() const abstract;
      virtual WeakRef<IObject>   tail() const abstract;
      virtual int       length() const abstract;
  
      virtual Ref<ICstList> reverse() const abstract;
      virtual Ref<IObject>  append(WeakRef<IObject>) const abstract; 
    };

    class IList : public ICstList {
      OBJECT_INTERFACE(IList,ICstList);
  
    public:
      virtual void setHead(WeakRef<IObject> _head) abstract;
      virtual void setTail(WeakRef<IObject> _tail) abstract;
    };
  }
}

#endif // INCLUDED_ILIST_HH
