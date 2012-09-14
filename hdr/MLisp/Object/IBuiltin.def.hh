#include "MLisp/Object/Nil.hh"

#define DECLBUILTIN(name)                               \
  namespace MLisp {                               \
    namespace Object {                                  \
      namespace Builtin {                               \
        class name : public IBuiltin {                  \
          NOT_COPYABLE(name);                           \
          name(StaticLeafTag _) : IBuiltin(_) {}         \
                                                        \
          static name ms_instance;                      \
                                                        \
        public:                                         \
        Ref<IObject> call(WeakRef<ICstList>) const;         \
                                                        \
        public:                                          \
        static WeakRef<name> instance() {                        \
          return weakRef(&ms_instance);                          \
        }                                                        \
                                                         \
        public:                                          \
        const char* typeName() const {                   \
          return "builtin:" #name;                          \
        }                                                \
        };                                               \
      }                                                  \
    }                                                    \
  }

#define DEFBUILTIN_BEGIN namespace MLisp { namespace Object { namespace Builtin {
#define DEFBUILTIN_END } } }

#define DEFBUILTIN(name,args)                           \
  name name::ms_instance(staticLeafTag);              \
  Ref<IObject> name::call(WeakRef<ICstList> args) const 
  
#define DEFBUILTIN_1(name,arg)                                          \
  name name::ms_instance(staticLeafTag);                              \
  namespace __Call__ {                                                  \
    Ref<IObject> name ## _Call__ (arg);                                 \
  }                                                                     \
  Ref<IObject> name::call(WeakRef<ICstList> _args) const {              \
    if(_args->is<Nil>())                                                \
      throw ERROR("too few arguments for '" #name "' (expected 1).");   \
    if(!_args->tail()->is<Nil>())                                       \
      throw ERROR("too many arguments for '" #name "' (expected 1).");  \
    return __Call__::name ## _Call__(_args->head());                    \
  }                                                                     \
  Ref<IObject> __Call__::name ## _Call__ (arg)

#define DEFBUILTIN_2(name,arg1,arg2)                                    \
  name name::ms_instance(staticLeafTag);                              \
  namespace __Call__ {                                                  \
    Ref<IObject> name ## _Call__ (arg1,arg2);                           \
  }                                                                     \
  Ref<IObject> name::call(WeakRef<ICstList> _args) const {              \
    WeakRef<ICstList> tail=_args->tail();                               \
    if(_args->is<Nil>() || tail->is<Nil>())                             \
      throw ERROR("too few arguments for '" #name "' (expected 2).");                   \
    if(!tail->tail()->is<Nil>())                               \
      throw ERROR("too many arguments for '" #name "' (expected 2).");                  \
    return __Call__::name ## _Call__(_args->head(),tail->head());       \
  }                                                                     \
  Ref<IObject> __Call__::name ## _Call__ (arg1,arg2)

#define DEFBUILTIN_3(name,arg1,arg2,arg3)                                   \
  name name::ms_instance(staticLeafTag);                              \
  namespace __Call__ {                                                  \
    Ref<IObject> name ## _Call__ (arg1,arg2,arg3);                          \
  }                                                                     \
  Ref<IObject> name::call(WeakRef<ICstList> _args) const {              \
    WeakRef<ICstList> tail1=_args->tail();                              \
    WeakRef<ICstList> tail2=tail1->tail();                              \
    if(_args->is<Nil>() || tail1->is<Nil>() || tail2->is<Nil>())        \
      throw ERROR("too few arguments for '" #name "' (expected 3).");   \
    if(!tail2->tail()->is<Nil>())                                       \
      throw ERROR("too many arguments for '" #name "' (expected 3).");  \
    return __Call__::name ## _Call__(_args->head(),tail1->head(),tail2->head()); \
  }                                                                     \
  Ref<IObject> __Call__::name ## _Call__ (arg1,arg2,arg3)
