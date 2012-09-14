#ifndef INCLUDED_MLISP_COMPILE_STATE_HH
#define INCLUDED_MLISP_COMPILE_STATE_HH

#include "Set.hh"
#include "Map.hh"
#include "Array.hh"
#include "MLisp/Object/Continuation.hh"
#include "MLisp/Object/IList.hh"
#include "MLisp/Ref.hh"
#include "MLisp/IOperation.hh"

namespace MLisp {
  using namespace Utils;
  struct CompileState {
    class Objects : public Map<IObject*,int> {
      typedef Map<IObject*,int> Parent;
        
    public:
      int operator[](IObject* _obj) {
        if(!contains(_obj)) {
          int size=this->size();
          Parent::element(_obj)=size;
        }
        return Parent::element(_obj);
      }
    };
    class NewObjects {
      Array<Ref<IObject> > m_array;
      int m_size;
    public:
      NewObjects() : m_array(8),m_size(0) {}
      void add(WeakRef<IObject> _obj) {
        if(m_size==m_array.size())
          m_array.resize(2*m_array.size());
        m_array[m_size++]=_obj;
      }
    };
    class Code {
      Array<Instruction> m_code;
      int                m_size;
    public:
      Code() : m_code(32), m_size(0) {}
      void pushBack(OpCode _c,int _arg=Instruction::MAX_ARG,bool _t=false) {
        if(m_code.size()==m_size)
          m_code.resize(m_code.size()*2);
        m_code[m_size++]=Instruction(_c,_arg,_t);
      }
      int size() const {
        return m_size;
      }
      Instruction* code() const {
        Instruction* ret=new Instruction[m_size];
        for(int i=0;i<m_size;++i)
          ret[i]=m_code[i];
        return ret;
      }

      Instruction& operator[](int _index) {
        return m_code[_index];
      }
    };
    Objects     params;
    Objects     objectsUsed;
    Objects     closedArgs;
    Set<IObject*> closableArgs;
    NewObjects  newObjects;
    Code        code;
    bool          tail;
  };
}

#endif // INCLUDED_MLISP_COMPILE_STATE_HH
