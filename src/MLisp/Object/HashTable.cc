#include "MLisp/Object/HashTable.hh"

using namespace MLisp;
using namespace Object;

Ref<Symbol> HashTable::get(const std::string& _key) {
  Node* cur=m_first;
  while(cur!=NULL && cur->key!=_key)
    cur=cur->next;
  if(cur==NULL) {
    m_first=new Node(_key,Symbol::create(String::create(_key.c_str())),m_first);
    return m_first->value;
  }
  else
    return cur->value;
}
bool        HashTable::has(const std::string& _key) const {
  Node* cur=m_first;
  while(cur!=NULL && cur->key!=_key)
    cur=cur->next;
  return cur!=NULL;
}

void HashTable::pushChildren(ObjectQueue* _q) const {
  for(Node* current=m_first;current!=NULL;current=current->next)
    _q->push(current->value.ptr());
}
