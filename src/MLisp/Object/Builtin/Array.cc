#include "MLisp/Object/Builtin/Array.hh"
#include "MLisp/Object/Integer.hh"
#include "MLisp/Object/Array.hh"

DEFBUILTIN_BEGIN;

DEFBUILTIN(MakeArray,_args) {
  return Object::Array::create(_args);
}
DEFBUILTIN_2(ArrayRef,WeakRef<Object::Array> _ar,WeakRef<Integer> _n) {
  return _ar->elt(_n->value());
}
DEFBUILTIN_3(ArraySet,WeakRef<Object::Array> _ar,WeakRef<Integer> _n,WeakRef<IObject> _newVal) {
  _ar->setElt(_n->value(),_newVal);
  return _newVal;
}
DEFBUILTIN_1(ArraySize,WeakRef<Object::Array> _ar) {
  return Integer::create(_ar->size());
}

DEFBUILTIN_END;



