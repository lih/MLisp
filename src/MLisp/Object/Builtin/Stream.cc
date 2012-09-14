#include "MLisp/Object/Builtin/Stream.hh"
#include "MLisp/Object/File.hh"
#include "MLisp/Object/Integer.hh"

DEFBUILTIN_BEGIN;

DEFBUILTIN_1(Open,WeakRef<String> _name) {
  return File::create(_name);
}
DEFBUILTIN_2(Read,WeakRef<IStream> _s,WeakRef<Integer> _n) {
  return _s->read(_n->value());
}
DEFBUILTIN_1(GetC,WeakRef<IStream> _s) {
  return _s->get();
}
DEFBUILTIN_2(Write,WeakRef<IStream> _s,WeakRef<String> _str) {
  _s->write(_str);
  return _s;
}

DEFBUILTIN_END;

