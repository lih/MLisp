#include "MLisp/Object/Builtin/Set.hh"
#include "MLisp/Object/Symbol.hh"

DEFBUILTIN_BEGIN;

DEFBUILTIN_2(Set,WeakRef<Symbol> _sym,WeakRef<IObject> _newVal) {
  _sym->setValue(_newVal);
  return _newVal;
}

DEFBUILTIN_END;
