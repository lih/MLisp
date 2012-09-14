#include "MLisp/Object/Builtin/Predicate.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/Object/Pair.hh"
#include "MLisp/Object/True.hh"
#include "MLisp/Object/Symbol.hh"
#include "MLisp/Object/Array.hh"
#include "MLisp/Object/Integer.hh"
#include "MLisp/Object/Float.hh"

#define ENVBOOL(expr) ((expr)?WeakRef<IObject>(True::instance()):\
                       WeakRef<IObject>(Nil::instance()))
#define DEFPREDICATE(name,var,expr) DEFBUILTIN_1(name,WeakRef<IObject> var) { return ENVBOOL(expr); }

DEFBUILTIN_BEGIN;

DEFPREDICATE(Null,x,x->is<Nil>());
DEFPREDICATE(Consp,x,x->is<Pair>());
DEFPREDICATE(Symbolp,x,x->is<Symbol>());
DEFBUILTIN_1(Boundp,WeakRef<Symbol> _s) {
  return ENVBOOL((!_s.isNull()) && _s->isBound());
}
DEFPREDICATE(Arrayp,x,x->is<Array>());
DEFPREDICATE(Integerp,x,x->is<Integer>());
DEFPREDICATE(Floatp,x,x->is<Float>());

DEFBUILTIN_END;
