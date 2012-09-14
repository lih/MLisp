#ifndef INCLUDED_MLISP_OBJECT_FLOAT_HH
#define INCLUDED_MLISP_OBJECT_FLOAT_HH

#include "Utils.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Object/INumeric.hh"

namespace MLisp {
  namespace Object {
    class Float : public INumeric {
      NOT_COPYABLE(Float);
      double m_value;

    private:
      void pushChildren(ObjectQueue*) const {}

      Float();
      Float(double _val) : INumeric(leafTag),m_value(_val) {}

    public:
      static Ref<Float> create(double _val) {
        return ref(new Float(_val));
      }

      double value() const { return m_value; }

      Ref<INumeric> add(WeakRef<INumeric> _other) const;
      Ref<INumeric> sub(WeakRef<INumeric> _other) const;
      Ref<INumeric> mul(WeakRef<INumeric> _other) const;
      Ref<INumeric> div(WeakRef<INumeric> _other) const;

      Ref<INumeric> addI(int i) const;
      Ref<INumeric> subI(int i) const;
      Ref<INumeric> mulI(int i) const;
      Ref<INumeric> divI(int i) const;
    
      Ref<INumeric> addF(double f) const;
      Ref<INumeric> subF(double f) const;
      Ref<INumeric> mulF(double f) const;
      Ref<INumeric> divF(double f) const;

    public:
      const char* typeName() const {
        return "double";
      }
      void        print() const;
    };
  }
}

#endif // INCLUDED_MLISP_OBJECT_FLOAT_HH
