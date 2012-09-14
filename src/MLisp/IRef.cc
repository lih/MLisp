#include <cstdlib> // for functions malloc() and free()

#include "MLisp/IRef.hh"
#include "MLisp/IObject.hh"
#include "Pool.hh"
#include "Queue.hh"

using namespace MLisp;
using namespace Utils;

#define ARRAY_SIZE_THRESHOLD 32

namespace {
  Pool s_arrayPool(ARRAY_SIZE_THRESHOLD);
  Queue<IObject*> ms_toDelete(1024);
  
  struct Node {
    IObject* val;
    Node*   next;

    static Pool s_nodePool;

    Node(IObject* _val,Node* _next) : val(_val),next(_next) {}
    
    void* operator new(size_t) {
      return s_nodePool.allocate();
    }
    void  operator delete(void* _p) {
      s_nodePool.free(_p);
    }
  };
  static Node s_pRoots(NULL,NULL);
  Pool Node::s_nodePool(sizeof(Node));
}

IRef::IRef(IObject* _ptr) : m_ptr(NULL) {
  reset(_ptr);
}
IRef::IRef(const IRef& _ref) : m_ptr(NULL) {
  reset(_ref.ptr());
}
IRef::~IRef() {
  reset(NULL);
}

void* IRef::operator new[](size_t _size) {
  if(_size<=ARRAY_SIZE_THRESHOLD)
    return s_arrayPool.allocate();
  else
    return malloc(_size);
}
void  IRef::operator delete[](void* _ptr,size_t _size) {
  if(_size<=ARRAY_SIZE_THRESHOLD)
    s_arrayPool.free(_ptr);
  else
    free(_ptr);
}

void IRef::reset(IObject* _ptr) {
  static bool collecting=false;

  if(m_ptr!=NULL) {
    m_ptr->m_gcData.refCount--;
    if(m_ptr->m_gcData.refCount==0)
      ms_toDelete.push(m_ptr);
    else if(m_ptr->m_gcData.state==IObject::UNKNOWN && 
            !m_ptr->m_gcData.buffered) {
      m_ptr->m_gcData.state=IObject::PROOT;
      m_ptr->m_gcData.buffered=true;
      s_pRoots.next=new Node(m_ptr,s_pRoots.next);
    }
  }
  m_ptr=_ptr;
  if(m_ptr!=NULL) {
    m_ptr->m_gcData.refCount++;
    if(m_ptr->m_gcData.state==IObject::PROOT)
      m_ptr->m_gcData.state=IObject::UNKNOWN;
  }
  
  if(!collecting) {
    collecting=true;
    IObject* cur;
    while(!ms_toDelete.empty()) {
      ms_toDelete.pop(&cur);
      if(!cur->m_gcData.buffered)
        delete cur;
    }
    collecting=false;
  }
}

void IRef::deleteFree() {
  Node* cur;
  bool deleted;
  do {
    deleted=false;
    cur=&s_pRoots;
    while(cur->next!=NULL) {
      if(cur->next->val->m_gcData.refCount==0) {
        deleted=true;
        cur->next->val->print();
        delete cur->next->val;
        Node* tmp=cur->next->next;
        delete cur->next;
        cur->next=tmp;
      }
      cur=cur->next;
    }
  } while(deleted);
}
void IRef::pseudoDeleteRoot(IObject* _root) {
  IObject::ObjectQueue toDelete(40);
  IObject* cur;
  _root->pushChildren(&toDelete);
    
  while(!toDelete.empty()) {
    toDelete.pop(&cur);
    --cur->m_gcData.refCount;
    if(cur->m_gcData.refCount==0 &&
       cur->m_gcData.state!=IObject::PROOT) 
      cur->pushChildren(&toDelete);
  }
}
void IRef::restoreRoot(IObject* _root) {
  IObject::ObjectQueue toRestore(40);
  _root->pushChildren(&toRestore);
  
  while(!toRestore.empty()) {
    IObject* cur;
    toRestore.pop(&cur);
    if(cur->m_gcData.refCount==0) { 
      cur->pushChildren(&toRestore);
      if(cur->m_gcData.state==IObject::PROOT)
        cur->m_gcData.state=IObject::UNKNOWN;
    }
    ++cur->m_gcData.refCount;
  }
}

void IRef::collectCycles() {
  deleteFree();

  // Keeps only possible roots
  for(Node* cur=&s_pRoots;cur!=NULL && cur->next!=NULL;cur=cur->next)
    if(cur->next->val->m_gcData.state!=IObject::PROOT) {
      Node* tmp=cur->next->next;
      cur->next->val->m_gcData.buffered=false;
      delete cur->next;
      cur->next=tmp;
    }

  // Simulates deletion of possible roots
  for(Node* cur=s_pRoots.next;cur!=NULL;cur=cur->next)
    pseudoDeleteRoot(cur->val);

  // Restores those which haven't been deleted
  for(Node* cur=s_pRoots.next;cur!=NULL;cur=cur->next)
    if(cur->val->m_gcData.refCount!=0 &&
       cur->val->m_gcData.state==IObject::PROOT) {
      restoreRoot(cur->val);
      cur->val->m_gcData.state=IObject::UNKNOWN;
    }

  // Filters the non-roots out
  for(Node* cur=&s_pRoots;cur!=NULL && cur->next!=NULL;cur=cur->next)
    if(cur->next->val->m_gcData.state!=IObject::PROOT) {
      Node* tmp=cur->next->next;
      cur->next->val->m_gcData.buffered=false;
      delete cur->next;
      cur->next=tmp;
    }
    else 
      ++cur->next->val->m_gcData.refCount;

  /* From this point on, we only have true roots in our root buffer */

  // Restores the cycles' reference counts 
  for(Node* cur=s_pRoots.next;cur!=NULL;cur=cur->next)
    if(cur->val->m_gcData.state==IObject::PROOT)
      restoreRoot(cur->val);

  Node* rem=s_pRoots.next;
  for(Node* cur=s_pRoots.next;cur!=NULL;cur=cur->next) {
    cur->val->m_gcData.buffered=false;
    cur->val->m_gcData.state=IObject::NOT_PROOT;
    delete cur->val;
  }
  
  Node* cur;
  for(cur=&s_pRoots;cur->next!=rem;cur=cur->next);
  cur->next=NULL;

  while(rem!=NULL) {
    Node* tmp=rem;
    rem=rem->next;
    delete tmp;
  }
}


