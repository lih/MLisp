#include "MLisp/Object/Builtin/List.hh"
#include "MLisp/Object/Pair.hh"

DEFBUILTIN_BEGIN;

DEFBUILTIN_2(Cons,WeakRef<IObject> _car,WeakRef<IObject> _cdr) {
  return Pair::create(_car,_cdr);
}
DEFBUILTIN_1(Car,WeakRef<ICstList> l) {
  return l->head();
}
DEFBUILTIN_1(Cdr,WeakRef<ICstList> l) {
  return l->tail();
}

DEFBUILTIN_END;

