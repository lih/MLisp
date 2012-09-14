#ifndef INCLUDED_MLISP_OBJECT_MACRO_HH
#define INCLUDED_MLISP_OBJECT_MACRO_HH

#include "MLisp/Object/ICallable.hh"
#include "MLisp/Object/Lambda.hh"

namespace MLisp {
  namespace Object {
    class Macro : public ICompileCallable {
      Ref<Lambda> m_lambda;
      
      Macro(WeakRef<Lambda> _l) : m_lambda(_l) {}
      
    public:
      // Macro interface
      static Ref<Macro> create(WeakRef<Lambda> _l) {
        return ref(new Macro(_l));
      }
      WeakRef<Lambda>   lambda() const {
        return m_lambda;
      }
      
    public:
      // ICompileCallable interface
      void compileCall(WeakRef<ICstList> _args,CompileState*) const;
      
    public:
      // IObject interface
      const char* typeName() const {
        return "macro";
      }
      void        pushChildren(ObjectQueue* _q) const {
        m_lambda->pushChildren(_q);
      }
      void        print() const;
    };
  }
}

#endif // INCLUDED_MLISP_OBJECT_MACRO_HH
