#ifndef INCLUDED_MLISP_PAIR_HH
#define INCLUDED_MLISP_PAIR_HH

#include "Utils.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Object/IList.hh"

namespace MLisp {
  namespace Object {
    class Pair : public IList {
      NOT_COPYABLE(Pair);
  
      Ref<IObject> m_head,m_tail;

    private:
      void pushChildren(ObjectQueue* _queue) const {
        _queue->push(m_head.ptr());
        _queue->push(m_tail.ptr());
      }
  
      Pair(WeakRef<IObject> _head,WeakRef<IObject> _tail)
        : m_head(_head),m_tail(_tail) {}
      
    private:
      void compile(CompileState* _st) const;

    public:
      static Ref<Pair> create(WeakRef<IObject> _head,WeakRef<IObject> _tail) {
        return ref(new Pair(_head,_tail));
      }

      WeakRef<IObject> head() const { 
        return m_head; 
      }
      WeakRef<IObject> tail() const { 
        return m_tail; 
      } 
      void         setHead(WeakRef<IObject> _head) {
        changeRef(_head.ptr());
        m_head=_head;
      }
      void         setTail(WeakRef<IObject> _tail) {
        changeRef(_tail.ptr());
        m_tail=_tail;
      }
      
      int  length() const;
      Ref<ICstList> reverse() const;
      Ref<IObject>  append(WeakRef<IObject>) const;

    public:
      const char* typeName() const {
        return "pair";
      } 
      void        print() const;
      bool        operator==(const IObject& _other) const;
    };
  }
}

#endif // INCLUDED_MLISP_PAIR_HH
