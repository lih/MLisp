#ifndef INCLUDED_MLISP_NUMERIC_HH
#define INCLUDED_MLISP_NUMERIC_HH

#include "Utils.hh"
#include "MLisp/IObject.hh"
#include "MLisp/Ref.hh"

namespace MLisp {
  namespace Object {
    class INumeric : public IObject {
      OBJECT_INTERFACE(INumeric,IObject);

    public:
      virtual Ref<INumeric> add(WeakRef<INumeric> _other) const abstract;
      virtual Ref<INumeric> sub(WeakRef<INumeric> _other) const abstract;
      virtual Ref<INumeric> mul(WeakRef<INumeric> _other) const abstract;
      virtual Ref<INumeric> div(WeakRef<INumeric> _other) const abstract;

      virtual Ref<INumeric> addI(int i) const abstract;
      virtual Ref<INumeric> subI(int i) const abstract;
      virtual Ref<INumeric> mulI(int i) const abstract;
      virtual Ref<INumeric> divI(int i) const abstract;
    
      virtual Ref<INumeric> addF(double f) const abstract;
      virtual Ref<INumeric> subF(double f) const abstract;
      virtual Ref<INumeric> mulF(double f) const abstract;
      virtual Ref<INumeric> divF(double f) const abstract;
    };
  }
}

#endif // INCLUDED_MLISP_NUMERIC_HH
