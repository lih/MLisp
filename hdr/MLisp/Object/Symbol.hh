#ifndef INCLUDED_MLISP_SYMBOL_HH
#define INCLUDED_MLISP_SYMBOL_HH

#include "Utils.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Object/ICallable.hh"
#include "MLisp/Object/String.hh"

namespace MLisp {
  namespace Object {
    class Symbol : public ICompileCallable {
      NOT_COPYABLE(Symbol);
      
    private:
      // Properties
      Ref<String> m_name;
      Ref<IObject> m_value;
  
    private:
      // Constructors & Destructors
      Symbol();
      Symbol(WeakRef<String> _name) : m_name(_name) {}
      Symbol(WeakRef<String> _name,WeakRef<IObject> _val) 
        : m_name(_name),m_value(_val) {}

    public:
      // Symbol interface
      static Ref<Symbol> create(WeakRef<String> _name) {
        return ref(new Symbol(_name));
      } 
      static Ref<Symbol> create(WeakRef<String> _name,WeakRef<IObject> _val) {
        return ref(new Symbol(_name,_val));
      }

      WeakRef<IObject> value() const {
        return m_value;
      }
      void             setValue(WeakRef<IObject> _newVal) {
        changeRef(_newVal.ptr());
        m_value=_newVal;
      }

      WeakRef<String>  name() const { return m_name; }

      bool  isBound() const { return !m_value.isNull(); }

    public:
      // ICompileCallable interface
      void compileCall(WeakRef<ICstList>,CompileState*) const;
    
    private:
      // IObject internals
      void pushChildren(ObjectQueue* _queue) const {
        if(!m_value.isNull()) _queue->push(m_value.ptr());
        _queue->push(m_name.ptr());
      }
      void compile(CompileState* _st) const;
  
    public:
      // IObject interface
      const char* typeName() const {
        return "symbol";
      }
      void        print() const;
    };
  }
}

#endif // INCLUDED_MLISP_SYMBOL_HH
