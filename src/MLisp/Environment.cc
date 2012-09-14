#include "MLisp.hpp"

using namespace MLisp;
using namespace Object;

Environment* MLisp::s_curEnv=NULL;

Environment::Environment()
  : m_frame(NULL),m_stack(NULL),m_PC(NULL),
    m_builtins(HashTable::create()), m_obarray(HashTable::create()) {
  { // Builtins initialization
    // Special forms
    m_builtins->get("if")->setValue(SpecialForm::If::instance());
    m_builtins->get("prog1")->setValue(SpecialForm::Prog1::instance());
    m_builtins->get("prog2")->setValue(SpecialForm::Prog2::instance());
    m_builtins->get("quote")->setValue(SpecialForm::Quote::instance());
    m_builtins->get("lambda")->setValue(SpecialForm::Lambda::instance());

    // Constants
    m_builtins->get("nil")->setValue(Nil::instance());
    m_builtins->get("t")->setValue(True::instance());
    m_builtins->get("obarray")->setValue(m_obarray);
    
    // Builtins
#define ADDBUILTIN(name,class) m_builtins->get(name)->setValue(Builtin::class::instance())
    ADDBUILTIN("print",Print);
    ADDBUILTIN("apply",Apply);
    ADDBUILTIN("macro",Macro);
    ADDBUILTIN("set!",Set);
    ADDBUILTIN("call/cc",CallCC);

    ADDBUILTIN("+",Add);
    ADDBUILTIN("-",Sub);
    ADDBUILTIN("*",Mul);
    ADDBUILTIN("/",Div);
    ADDBUILTIN("mod",Mod);
    ADDBUILTIN(">",Greater);
    ADDBUILTIN(">=",GreaterEq);
    ADDBUILTIN("<",Lesser);
    ADDBUILTIN("<=",LesserEq);
    ADDBUILTIN("=",Eq);

    ADDBUILTIN("cons",Cons);
    ADDBUILTIN("car",Car);
    ADDBUILTIN("cdr",Cdr);
  
    ADDBUILTIN("array",MakeArray);
    ADDBUILTIN("aref",ArrayRef);
    ADDBUILTIN("aset!",ArraySet);
    ADDBUILTIN("array-size",ArraySize);

    ADDBUILTIN("open",Open);
    ADDBUILTIN("read",Read);
    ADDBUILTIN("write",Write);
    ADDBUILTIN("getc",GetC);

    ADDBUILTIN("macro-lambda",MacroLambda);  
    ADDBUILTIN("null?",Null);
    ADDBUILTIN("cons?",Consp);
    ADDBUILTIN("symbol?",Symbolp);
    ADDBUILTIN("array?",Arrayp);
    ADDBUILTIN("integer?",Integerp);
    ADDBUILTIN("float?",Floatp);
    ADDBUILTIN("bound?",Boundp);
    ADDBUILTIN("eq?",Eq);
#undef ADDBUILTIN
  }
  for(auto it=m_builtins->begin();it;++it)
    m_obarray->get((*it)->name()->data())->setValue((*it)->value());
}

Ref<ICstList> Environment::popStack(int _n) {
  if(_n==0)
    return Nil::instance();
  else {
    Ref<ICstList>     ret=m_stack;
    WeakRef<ICstList> stack=m_stack;
    for(int i=1;i<_n;++i)
      stack=stack->tail();
    WeakRef<IList> last=stack;
    m_stack=stack->tail();
    last->setTail(Nil::instance());
    return ret;
  }
} 
Ref<IObject>  Environment::popStack() {
  Ref<ICstList> head=m_stack;
  m_stack=m_stack->tail();
  return head->head();
} 
void          Environment::pushStack(WeakRef<IObject> _obj) {
  m_stack=Pair::create(_obj,m_stack);
}
void          Environment::printStack() {
  WeakRef<ICstList> cur=m_stack;

  while(!(cur.isNull() || cur->is<Nil>())) {
    if(!cur->head().isNull()) {
      cur->head()->print();
      printf(" ");
    }
    cur=cur->tail();
  }
}
void          Environment::returnWith(Ref<IObject> _obj) {
  Ref<Object::Continuation> retCC=popStack();
  if(!retCC.isNull())
    retCC->call();
  else
    m_PC=NULL;
  pushStack(_obj);
}

Ref<IObject> Environment::eval() {
  try {
    while(m_PC!=NULL) {
      Instruction       i=fetch();
      // Uncomment next line to get a detailed execution trace
      // printf("Executing "); i.print(); printf(" | "); printStack(); printf("\n");
      s_ops[i.opCode](i.arg,i.tail);
    }
  }
  catch(...) {
    m_PC=NULL;
    m_stack.reset(NULL);
    m_frame.reset(NULL);
    throw;
  }
  
  return popStack();
}


