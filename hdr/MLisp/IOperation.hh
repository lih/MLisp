#ifndef INCLUDED_MLISP_I_OPERATION_HH
#define INCLUDED_MLISP_I_OPERATION_HH

#include "Utils.hh"

namespace MLisp {
  enum OpCode {
    CALLER,
    CONST,ARG_SYM,CLOSED_ARG_SYM,
    VAL,ARG,CLOSED_ARG,
    FORWARD,FORWARD_IF_NIL,
    IGNORE,
    CLOSE,
    SIZE
  };
  struct Instruction {
    static const int MAX_ARG=(1<<24)-1;
    
    OpCode opCode :6;
    int    arg    :25;
    bool   tail   :1;
  
    Instruction(OpCode _code=SIZE,int _arg=MAX_ARG,bool _tail=false)
      : opCode(_code),arg(_arg),tail(_tail) {}
    void print() const;
  };
  
  typedef void (*OperationType)(int,bool);
  extern const OperationType s_ops[SIZE];
}

#endif // INCLUDED_MLISP_I_OPERATION_HH
