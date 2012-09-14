#include "MLisp/Object/Builtin/Apply.hh"
#include "MLisp/Object/Integer.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/Object/Pair.hh"

using namespace MLisp;
using namespace Object;
using namespace Builtin;

Apply Apply::ms_instance(staticLeafTag);

void Apply::call(WeakRef<ICstList> _args,bool _tail) const {
  WeakRef<ICallable> fun=_args->head();
  _args=_args->tail();
  Ref<ICstList> args=_args->reverse();
  Ref<ICstList> argList=args->head();
  args=args->tail();
  
  while(!args->is<Nil>()) {
    argList=Pair::create(args->head(),argList);
    args=args->tail();
  }

  fun->call(argList,_tail);
}
