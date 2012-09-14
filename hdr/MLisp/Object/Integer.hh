#ifndef INCLUDED_MLISP_OBJECT_INTEGER_HH
#define INCLUDED_MLISP_OBJECT_INTEGER_HH

#include "Utils.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Object/INumeric.hh"

namespace MLisp {
  namespace Object {
    class Integer : public INumeric {
      NOT_COPYABLE(Integer);
      int m_value;

    private:
      void pushChildren(ObjectQueue*) const {}

      Integer();
      Integer(int _val) : INumeric(leafTag),m_value(_val) {}

    public:
      static Ref<Integer> create(int _val) {
        return ref(new Integer(_val));
      }

      int value() const { return m_value; }
      
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
        return "integer";
      }
      void        print() const;
      bool        equal(const IObject&) const;
    };    
  }
}

#endif // INCLUDED_MLISP_OBJECT_INTEGER_HH
