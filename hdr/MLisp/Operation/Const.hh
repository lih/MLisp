#ifndef INCLUDED_MLISP_OPERATION_CONST_HH
#define INCLUDED_MLISP_OPERATION_CONST_HH

#include "Utils.hh"
#include "MLisp/IOperation.hh"

namespace MLisp {
  class IObject;
  
  namespace Operation {
    class Const {
    public:
      static const OpCode     s_opCode;
      static const OperationType  s_instance;

    public:
      // IOperation interface
      static void call(int,bool);
      
    public:
      // Const interface
      static void compileObject(IObject*,CompileState*);
    };
  }
}

#endif // INCLUDED_MLISP_OPERATION_CONST_HH
