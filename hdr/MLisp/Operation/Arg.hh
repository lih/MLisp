#ifndef INCLUDED_MLISP_OPERATION_PARAM_HH
#define INCLUDED_MLISP_OPERATION_PARAM_HH

#include "MLisp/IOperation.hh"

namespace MLisp {
  namespace Operation {
    class Arg {
    public:
      static const OpCode s_opCode;
      static const OperationType s_instance;
      
    public:
      // IOperation interface
      static void call(int,bool);
    };

    class ArgSym {
    public:
      static const OpCode   s_opCode;
      static const OperationType s_instance;
      
    public:
      // IOperation interface
      static void call(int,bool);
    };

    class ClosedArg {
    public:
      static const OpCode      s_opCode;
      static const OperationType s_instance;
      
    public:
      // IOperation interface
      static void call(int,bool);
    };

    class ClosedArgSym {
    public:
      static const OpCode         s_opCode;
      static const OperationType s_instance;
      
    public:
      // IOperation interface
      static void call(int,bool);
    };
  }
}

#endif // INCLUDED_MLISP_OPERATION_PARAM_HH
