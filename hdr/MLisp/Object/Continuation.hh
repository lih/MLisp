#ifndef INCLUDED_CONTINUATION_HH
#define INCLUDED_CONTINUATION_HH

#include "Utils.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Object/ICallable.hh"
#include "MLisp/Object/Lambda.hh"
#include "MLisp/Environment.hh"

namespace MLisp {
  namespace Object {
    class Continuation : public ICallable, private Environment::Continuation {
      NOT_COPYABLE(Continuation);
      
    private:
      // Properties
      Ref<class Lambda::Instance> m_frame;
      Ref<ICstList>               m_stack;
      const Instruction*          m_pc;

      Continuation();

    public:
      // Continuation interface
      static Ref<Continuation> create() {
        return ref(new Continuation());
      }

      const Instruction* pCounter() const  { 
        return m_pc; 
      }
      

    public:
      // ICallable interface
      using Environment::Continuation::call;
      void call(WeakRef<ICstList>,bool) const;

    public:
      // IObject interface
      void pushChildren(ObjectQueue*) const;
      
      const char* typeName() const { 
        return "continuation";
      }
    };
  }
}

#endif // INCLUDED_CONTINUATION_HH
