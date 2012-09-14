#include <cstdio>
#include "MLisp/Environment.hh"
#include "MLisp/CompileState.hh"
#include "MLisp/Object/Lambda.hh"
#include "MLisp/Object/Nil.hh"
#include "MLisp/Object/Continuation.hh"

using namespace MLisp;
using namespace Object;

namespace {
  // Utility functions
  inline int argListLength(WeakRef<IObject> _arglist) {
    int ret=0;
    while(_arglist->is<Pair>()) {
      ++ret;
      _arglist=WeakRef<Pair>(_arglist)->tail();
    }
    if(_arglist->is<Symbol>())
      ++ret;
    else if(!_arglist->is<Nil>())
      throw ERROR("invalid arg list");
    
    return ret;
  }
  inline void         splitArgList(WeakRef<IObject> _arglist,int* _size,Ref<Symbol>** _args,bool* _hasTail) {
    Ref<IObject>      next=_arglist;
    WeakRef<ICstList> curC=next;
    *_size=argListLength(_arglist);
    *_hasTail=false;

    if(*_size>0) {
      *_args=new Ref<Symbol>[*_size];
      int i=0;
      while(curC->is<Pair>()) {
        next=curC->tail();
        WeakRef<Symbol> cur=curC->head();
        if(cur.isNull()) {
          _arglist->print();
          throw ERROR("invalid arg list");
        }
        (*_args)[i++]=cur;
        curC=next;
      }
      if(!next->is<Nil>()) {
        (*_args)[i]=next;
        *_hasTail=true;
      }
    }
    else 
      *_args=NULL;
  }

}

// Constructors & Destructors
Lambda::Lambda(WeakRef<IObject> _expr,WeakRef<IObject> _args)
  : m_closedCount(0),m_closed(NULL) {
  splitArgList(_args,&m_argsCount,&m_args,&m_hasTail);

  CompileState st;
  for(int i=0;i<m_argsCount;++i)
    st.params[m_args[i].ptr()];
  st.tail=true;
  m_frame=ByteCode::create(_expr,&st);
}
Lambda::Lambda(const Closure* _parent) 
  : m_frame(_parent->m_frame),
    m_argsCount(_parent->m_argsCount),m_args(NULL),m_hasTail(_parent->m_hasTail),
    m_closedCount(_parent->m_closedCount),m_closed(NULL) {
  if(m_argsCount>0) {
    m_args=new Ref<Symbol>[m_argsCount];
    for(int i=0;i<m_argsCount;++i)
      m_args[i]=_parent->m_args[i];
  }
  if(m_closedCount>0) {
    m_closed=new Ref<Symbol>[m_closedCount];
    for(int i=0;i<m_closedCount;++i)
      if(_parent->m_closedMap[i].imm)
        m_closed[i]=s_curEnv->frame().param(_parent->m_closedMap[i].val);
      else
        m_closed[i]=s_curEnv->frame().closed(_parent->m_closedMap[i].val);
  }
}
Lambda::~Lambda() {
  if(m_args!=NULL)
    delete[] m_args;
  if(m_closed!=NULL)
    delete[] m_closed;
}

// Lambda internals
Ref<Symbol>*    Lambda::m_argsInstance(WeakRef<ICstList> _args) const {
  Ref<Symbol>* ret=new Ref<Symbol>[m_argsCount];

  WeakRef<ICstList> curC=_args;
  int argsCount=m_argsCount-(m_hasTail?1:0);
  for(int i=0;i<argsCount;++i) {
    if(!curC->is<Pair>())
      throw TooFewArguments(*this,_args);
    ret[i]=Symbol::create(m_args[i]->name(),curC->head());
    curC=curC->tail();
  }
  if(m_hasTail)
    ret[argsCount]=Symbol::create(m_args[argsCount]->name(),curC);
  else if(!curC->is<Nil>())
    throw ERROR("too many arguments.");

  return ret;
}

// IObject interface
void Lambda::pushChildren(ObjectQueue* _q) const {
  _q->push(m_frame.ptr());
  // pushing args
  for(int i=0;i<m_argsCount;++i)
    _q->push(m_args[i].ptr());
  // pushing closed args
  for(int i=0;i<m_closedCount;++i)
    _q->push(m_closed[i].ptr());
}
void Lambda::call(WeakRef<ICstList> _args,bool _tail) const {
  if(!_tail)
    s_curEnv->pushStack(Continuation::create());
  s_curEnv->enterFrame(Instance::create(weakRef(const_cast<Lambda*>(this)),
                                      _args));
}
void Lambda::print() const {
  printf("#(lambda (");
  bool first=true;
  int argsCount=m_argsCount-(m_hasTail?1:0);
  for(int i=0;i<argsCount;++i) {
    if(!first)
      printf(",");
    else
      first=false;
    m_args[i]->print();
  }
  if(m_hasTail) {
    printf("|");
    m_args[argsCount]->print();
  }
  printf(") ");
  if(m_closed!=NULL) {
    printf("[");
    bool first=true;
    for(int i=0;i<m_closedCount;++i) {
      if(!first)
        printf(",");
      first=false;
      m_closed[i]->print();
    }
    printf("] ");
  }
  m_frame->print();
  printf(")");
}

/* 
 * Bytecode subclass
 */
Lambda::ByteCode::ByteCode(WeakRef<IObject> _obj,CompileState* _st) {
  _obj->compile(_st);

  m_codeSize=_st->code.size();
  m_code=_st->code.code();
  m_objectsCount=_st->objectsUsed.size();
  m_frame=new Ref<IObject>[m_objectsCount];
  
  auto it=_st->objectsUsed.begin();
  for(;it!=_st->objectsUsed.end();++it)
    m_frame[it.value()]=ref(it.key());
}

// IObject interface
void  Lambda::ByteCode::pushChildren(ObjectQueue* _queue) const {
  for(int i=0;i<m_objectsCount;++i)
    _queue->push(m_frame[i].ptr());
}
void  Lambda::ByteCode::print() const {
  printf("{");
  
  if(m_objectsCount>0)
    m_frame[0]->print();
  for(int i=1;i<m_objectsCount;++i) {
    printf(","); fflush(stdout);
    m_frame[i]->print();
  }
  printf("} ");
  
  printf("[");
  for(int i=0;i<m_codeSize;++i) {
    m_code[i].print();
    printf(";");
  }
  printf("]");
}

/*
 * Instance subclass
 */
Lambda::Instance::Instance(WeakRef<Lambda> _fun,WeakRef<ICstList> _args)
  : m_lambda(_fun), m_args(_fun->m_argsInstance(_args)), m_argsCount(_fun->m_argsCount) {}

// IObject interface
void Lambda::Instance::pushChildren(ObjectQueue* _q) const {
  _q->push(m_lambda.ptr());
  for(int i=0;i<m_argsCount;++i)
    _q->push(m_args[i].ptr());
}

/*
 * Closure subclass
 */
Lambda::Closure::Closure(WeakRef<IObject> _expr,WeakRef<IObject> _args,CompileState* _st)
  : m_closedCount(0), m_closedMap(NULL) {
  splitArgList(_args,&m_argsCount,&m_args,&m_hasTail);

  CompileState st;
  for(int i=0;i<m_argsCount;++i)
    st.params[m_args[i].ptr()];
  st.tail=true;
  if(_st!=NULL) {
    for(auto it=_st->closableArgs.begin();it!=_st->closableArgs.end();++it)
      st.closableArgs.insert(*it);
    for(auto it=_st->params.begin();it!=_st->params.end();++it)
      st.closableArgs.insert(it.key());
  }
  m_frame=ByteCode::create(_expr,&st);
  if(_st!=NULL) {
    m_closedCount=st.closedArgs.size();
    if(m_closedCount>0) {
      m_closedMap=new ArgMap[m_closedCount];
      for(auto it=st.closedArgs.begin();it!=st.closedArgs.end();++it) {
        m_closedMap[*it].imm=_st->params.contains(it.key());
        if(m_closedMap[*it].imm)
          m_closedMap[*it].val=_st->params[it.key()];
        else
          m_closedMap[*it].val=_st->closedArgs[it.key()];
      }
    }
  }
}
Lambda::Closure::~Closure() {
  if(m_closedMap!=NULL)
    delete[] m_closedMap;
  if(m_args!=NULL)
    delete[] m_args;
}

// Closure interface
Ref<Lambda> Lambda::Closure::close() const {
  return ref(new Lambda(this));
}

// IObject interface
void Lambda::Closure::pushChildren(ObjectQueue* _q) const {
  _q->push(m_frame.ptr());
  for(int i=0;i<m_argsCount;++i)
    _q->push(m_args[i].ptr());
}
void Lambda::Closure::print() const {
  printf("#(closure (");
  bool first=true;
  int argsCount=m_argsCount-(m_hasTail?1:0);
  for(int i=0;i<argsCount;++i) {
    if(!first)
      printf(",");
    else
      first=false;
    m_args[i]->print();
  }
  if(m_hasTail) {
    printf("|");
    m_args[argsCount]->print();
  }
  printf(") ");
  m_frame->print();
  printf(")");
}
