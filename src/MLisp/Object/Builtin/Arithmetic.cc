#include "MLisp/Object/Builtin/Arithmetic.hh"
#include "MLisp/Object/Integer.hh"
#include "MLisp/Object/INumeric.hh"
#include "MLisp/Object/Nil.hh"

DEFBUILTIN_BEGIN;

DEFBUILTIN(Add,_args) {
  Ref<INumeric> ret=Integer::create(0);

  while(!_args->is<Nil>()) {
    WeakRef<INumeric> i=_args->head();
    if(i.isNull()) throw ERROR("wrong type argument");
    ret=ret->add(i);
    _args=_args->tail();
  }
  
  return ret;
}
DEFBUILTIN(Sub,_args) {
  Ref<INumeric> ret=Integer::create(0);
  bool first=true;

  while(!_args->is<Nil>()) {
    WeakRef<INumeric> i=_args->head();
    if(i.isNull()) throw ERROR("wrong type argument");
    if(first) 
      ret=i;
    else
      ret=ret->sub(i);
    first=false;
    _args=_args->tail();
  }
  
  return ret;
}
DEFBUILTIN(Mul,_args) {
  Ref<INumeric> ret=Integer::create(1);

  while(!_args->is<Nil>()) {
    WeakRef<INumeric> i=_args->head();
    if(i.isNull()) throw ERROR("wrong type argument");
    ret=ret->mul(i);
    _args=_args->tail();
  }
  
  return ret;
}
DEFBUILTIN(Div,_args) {
  Ref<INumeric> ret=Integer::create(1);
  bool first=true;

  while(!_args->is<Nil>()) {
    WeakRef<INumeric> i=_args->head();
    if(i.isNull()) throw ERROR("wrong type argument");
    if(first)
      ret=i;
    else
      ret=ret->div(i);
    first=false;
    _args=_args->tail();
  }
  
  return ret;
}
DEFBUILTIN(Mod,_args) {
  WeakRef<Integer> fst=_args->head();
  _args=_args->tail();
  int ret=fst->value();
  
  while(!_args->is<Nil>()) {
    WeakRef<Integer> i=_args->head();
    if(i.isNull()) throw ERROR("wrong type argument");
    ret=ret%i->value();
    _args=_args->tail();
  }
  
  return Integer::create(ret);
}

DEFBUILTIN_END;
