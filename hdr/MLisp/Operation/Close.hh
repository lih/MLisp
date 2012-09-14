#ifndef INCLUDED_MLISP_OPERATION_CLOSE_HH
#define INCLUDED_MLISP_OPERATION_CLOSE_HH

#include "MLisp/IOperation.hh"

namespace MLisp {
  namespace Operation {
    class Close {
    public:
      static const OpCode     s_opCode;
      static const OperationType s_instance;
      
    public:
      // IOperation interface
      static void call(int,bool);
    };
  }
}

#endif // INCLUDED_MLISP_OPERATION_CLOSE_HH
