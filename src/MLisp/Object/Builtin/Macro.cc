#include "MLisp/Object/Builtin/Macro.hh"
#include "MLisp/Object/Macro.hh"

DEFBUILTIN_BEGIN;

DEFBUILTIN_1(Macro,WeakRef<Lambda> _l) {
  return Object::Macro::create(_l);
}
DEFBUILTIN_1(MacroLambda,WeakRef<Object::Macro> _m) {
  return _m->lambda();
} 

DEFBUILTIN_END;
