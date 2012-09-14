#include "MLisp/Object/Builtin/Print.hh"
#include "MLisp/Object/IList.hh"
#include "MLisp/Object/Nil.hh"

DEFBUILTIN_BEGIN;

DEFBUILTIN_1(Print,WeakRef<IObject> _obj) {
  _obj->print();
  return _obj;
}

DEFBUILTIN_END;
