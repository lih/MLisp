#include "MLisp/IRef.test.hh"
#include "MLisp/Environment.test.hh"
#include "MLisp.hpp"
#include "TestMacros.hh" 

using namespace MLisp;
using namespace Object;

#define CONS(a,b) (Pair::create((a),(b)))
#define NIL (Nil::instance())
#define QUOTE(e) (CONS(SpecialForm::Quote::instance(),CONS((e),NIL)))
#define IF(cond,then,else) (CONS(SpecialForm::If::instance(),CONS((cond),CONS((then),CONS((else),NIL)))))
#define PROG1(fst,snd) (CONS(SpecialForm::Prog1::instance(),CONS((fst),CONS((snd),NIL))))
#define PROG2(fst,snd) (CONS(SpecialForm::Prog2::instance(),CONS((fst),CONS((snd),NIL))))
#define LAMBDA(args,body) (Lambda::create((body),(args)))
#define CALL0(fun) (CONS((fun),NIL))
#define CALL1(fun,arg) (CONS((fun),CONS((arg),NIL)))
#define CALL2(fun,arg1,arg2) (CONS((fun),CONS((arg1),CONS((arg2),NIL))))
#define INT(n) (Integer::create(n))
#define SYMBOL(name,val) (Symbol::create(String::create(name),(val)))
#define UNDEF (WeakRef<IObject>(NULL))

#define PRINT(arg) CALL1(Builtin::Print::instance(),arg)

namespace {
  void testIf() {
    ENTER_TEST("special form if");

    Ref<IObject> n=INT(3);
    
    { // then branch
      ENTER_TEST("then branch");
      Ref<Lambda>  l=LAMBDA(NIL,IF(n,n,NIL));
      
      l->call(NIL,false);
      s_curEnv->eval();

      TEST(s_curEnv->topStack()->is<Integer>());
    }
    { // else branch
      ENTER_TEST("else branch");
      Ref<Lambda>  l=LAMBDA(NIL,IF(NIL,NIL,n));
      
      l->call(NIL,false);
      s_curEnv->eval();

      TEST(s_curEnv->topStack()->is<Integer>());
    }
  }
  void testQuote() {
    ENTER_TEST("special form quote");

    Ref<Symbol>  sym=SYMBOL("foo",NIL);
    Ref<Lambda>  l=LAMBDA(NIL,QUOTE(sym));

    l->call(NIL,false);
    s_curEnv->eval();
    
    TEST(s_curEnv->topStack()->is<Symbol>());
  }
  void testProg1() {
    ENTER_TEST("special form prog1");
    
    Ref<Integer> x=INT(25),y=INT(33);
    Ref<Lambda>  l=LAMBDA(NIL,PROG1(x,y));

    l->call(NIL,false);
    s_curEnv->eval();
    
    TEST(s_curEnv->topStack().ptr()==x.ptr());
  }
  void testProg2() {
    ENTER_TEST("special form prog2");
    
    Ref<Integer> x=INT(29);
    Ref<Lambda>  l=LAMBDA(NIL,PROG2(NIL,x));

    l->call(NIL,false);
    s_curEnv->eval();
    
    TEST(s_curEnv->topStack().ptr()==x.ptr());
  }
  void testArgQuote() {
    ENTER_TEST("parameter quote");
    
    Ref<Symbol> sym=SYMBOL("sym",NIL);
    Ref<Lambda> l=LAMBDA(CONS(sym,NIL),QUOTE(sym));

    l->call(CONS(INT(3),NIL),false);
    s_curEnv->eval();
    
    TEST(s_curEnv->topStack()->is<Symbol>());
    TEST(WeakRef<Symbol>(s_curEnv->topStack())->value()->is<Integer>());
    TEST(sym->value()->is<Nil>());
  }
  void testCompileCall() {
    ENTER_TEST("function call compilation");

    Ref<IObject> x=INT(3);
    Ref<Symbol>  sym=SYMBOL("foo",NIL);
    Ref<Lambda>  lamStr=LAMBDA(CONS(sym,NIL),sym);
    Ref<Lambda>  lam=LAMBDA(NIL,IF(CALL1(lamStr,x),x,NIL));
    
    lam->call(NIL,false);
    s_curEnv->eval();
    
    TEST(s_curEnv->topStack().ptr()==x.ptr());
  }
  void testSymFuncall() {
    ENTER_TEST("symbol function call");

    Ref<Lambda> fun=LAMBDA(NIL,INT(24));
    Ref<Symbol> sym=SYMBOL("sym",fun);
    Ref<Lambda> l=LAMBDA(NIL,CALL0(sym));

    l->call(NIL,false);
    s_curEnv->eval();
      
    TEST(s_curEnv->topStack()->is<Integer>());
    WeakRef<Integer> ret=s_curEnv->topStack();
    TEST(ret->value()==24);
  }
  void testBuiltinPrint() {
    ENTER_TEST("builtin print");

    Ref<Symbol>  x=SYMBOL("x",UNDEF);
    Ref<Lambda>  l=LAMBDA(CONS(x,NIL),PRINT(x));

    l->call(CONS(INT(42),NIL),false);
    s_curEnv->eval();
    
    TEST(s_curEnv->topStack()->is<Integer>());
  }
}  

void environment_test() {
  ENTER_TEST("Lisp environment");

  IRef_test();
    
  testIf();
  testQuote();
  testProg1();
  testProg2();
  testArgQuote();
  testCompileCall();
  testSymFuncall();
  testBuiltinPrint();
}
