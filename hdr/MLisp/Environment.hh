#ifndef INCLUDED_MLISP_HH
#define INCLUDED_MLISP_HH

#include <exception>
#include "MLisp/Ref.hh"
#include "MLisp/Object/IList.hh"
#include "MLisp/Object/Lambda.hh"
#include "MLisp/Object/HashTable.hh"

namespace MLisp {
  class  Environment;
  extern Environment* s_curEnv;
  class  Environment {
  private:
    // Properties
    Ref<Object::Lambda::Instance> m_frame;
    Ref<Object::ICstList>         m_stack;
    const Instruction*            m_PC;
    Ref<Object::HashTable>        m_builtins;
    Ref<Object::HashTable>        m_obarray;

  public:
    // Substruct Continuation
    struct Continuation {
    protected:
      Ref<Object::Lambda::Instance> m_frame;
      Ref<Object::ICstList>         m_stack;
      const Instruction*            m_PC;

    public:
      Continuation(const Environment& _env) 
        : m_frame(_env.m_frame),m_stack(_env.m_stack),m_PC(_env.m_PC) {}
      void call() const {
        s_curEnv->m_frame=m_frame;
        s_curEnv->m_stack=m_stack;
        s_curEnv->m_PC=m_PC;
      }
    };
    
  public:
    // Constructors & Destructors
    Environment();
 
  public:
    // Stack manipulation
    WeakRef<IObject>      topStack() {
      return m_stack->head();
    }
    Ref<Object::ICstList> popStack(int _nargs);
    Ref<IObject>          popStack();
    void                  pushStack(WeakRef<IObject> _val);
    void                  printStack();
    
  public:
    // Control flow manipulation
    void  returnWith(Ref<IObject>);
    void  forward(int _size) { 
      m_PC+=_size;
    }
    void  forward() { 
      ++m_PC; 
    }
    void  enterFrame(WeakRef<Object::Lambda::Instance> _frame) {
      m_frame=_frame;
      m_PC=_frame->code();
    }
    void  resetFrame() {
      m_PC=NULL;
      m_stack.reset(NULL);
      m_frame.reset(NULL);
    }

  public:
    // Misceleanna
    Instruction               fetch() {
      return *(m_PC++);
    }
    Object::HashTable&        obarray() {
      return *m_obarray;
    }
    Object::HashTable&        builtins() {
      return *m_builtins;
    }
    Object::Lambda::Instance& frame() {
      return *m_frame;
    }

    Ref<IObject>  eval();
  };
}

#endif // INCLUDED_MLISP_HH
