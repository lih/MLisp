#ifndef INCLUDED_MLISP_OPERATION_VAL_HH
#define INCLUDED_MLISP_OPERATION_VAL_HH

#include "MLisp/IOperation.hh"
#include "MLisp/IObject.hh"

namespace MLisp {
  namespace Object { class Symbol; }
  
  namespace Operation {
    class Val {
    public:
      static const OpCode s_opCode;
      static const OperationType s_instance;
      
    public:
      // IOperation interface
      static void call(int,bool);

    public:
      // Val interface
      static void compileObject(Object::Symbol*,CompileState*);
    };
  }
}

#endif // INCLUDED_MLISP_OPERATION_VAL_HH
