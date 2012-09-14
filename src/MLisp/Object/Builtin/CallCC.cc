#include "MLisp/Object/Builtin/CallCC.hh"
#include "MLisp/Object/Lambda.hh"
#include "MLisp/Object/Pair.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/Object/Continuation.hh"

using namespace MLisp;
using namespace Object;
using namespace Builtin;

CallCC CallCC::ms_instance(staticLeafTag);

void CallCC::call(WeakRef<ICstList> _args,bool _tail) const {
  WeakRef<ICallable> fun=_args->head();
  if(!_args->tail()->is<Nil>())
    throw ERROR("Wrong number of arguments to call/cc");
  
  fun->call(Pair::create(Continuation::create(),Nil::instance()),_tail);
}
