#include "MLisp/Object/Builtin/Comparison.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/Object/Integer.hh"
#include "MLisp/Object/True.hh"

#define ENVBOOL(expr) ((expr)?WeakRef<IObject>(True::instance()):   \
                       WeakRef<IObject>(Nil::instance()))

DEFBUILTIN_BEGIN;

DEFBUILTIN_2(Eq,WeakRef<IObject> _fst,WeakRef<IObject> _snd) {
  return ENVBOOL(*_fst==*_snd);
}
DEFBUILTIN_2(Lesser,WeakRef<Integer> _fst,WeakRef<Integer> _snd) {
  return ENVBOOL(_fst->value()<_snd->value());
}
DEFBUILTIN_2(LesserEq,WeakRef<Integer> _fst,WeakRef<Integer> _snd) {
  return ENVBOOL(_fst->value()<=_snd->value());
}
DEFBUILTIN_2(Greater,WeakRef<Integer> _fst,WeakRef<Integer> _snd) {
  return ENVBOOL(_fst->value()>_snd->value());
}
DEFBUILTIN_2(GreaterEq,WeakRef<Integer> _fst,WeakRef<Integer> _snd) {
  return ENVBOOL(_fst->value()>=_snd->value());
}

DEFBUILTIN_END;
