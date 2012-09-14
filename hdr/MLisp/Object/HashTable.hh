#ifndef INCLUDED_MLISP_OBJECT_HASH_TABLE_HH
#define INCLUDED_MLISP_OBJECT_HASH_TABLE_HH

#include <string>
#include "MLisp/Ref.hh"
#include "MLisp/Object/Symbol.hh"
#include "MLisp/IObject.hh"

namespace MLisp {
  namespace Object {
    class HashTable : public IObject {
    private:
      // Substruct Node
      struct Node {
        std::string key;
        Ref<Symbol> value;
        Node* next;

        Node(const std::string& _key,WeakRef<Symbol> _value,Node* _next=NULL) 
          : key(_key),value(_value),next(_next) {}
      };
      
    public:
      // Subclass Iterator
      class Iterator {
        friend class HashTable;

      private:
        // Properties
        Node* m_current;
        
      private:
        // Constructors & Destructors
        Iterator(Node* _n) : m_current(_n) {}

      public:
        // Iterator interface
        void         forward() {
          m_current=m_current->next;
        }
        bool         end() const {
          return m_current==NULL;
        }
        Ref<Symbol>& data() const {
          return m_current->value;
        }
        
        operator bool() const {
          return !end();
        }
        Ref<Symbol>& operator*() const {
          return data();
        }
        Iterator&    operator++() {
          forward();
          return *this;
        }
      };

    private:
      // Properties
      Node* m_first;

    private:
      // Constructors & Destructors      
      HashTable() : m_first(NULL) {}
      ~HashTable() {
        while(m_first!=NULL) {
          Node* tmp=m_first;
          m_first=m_first->next;
          delete tmp;
        }
      }

    public:
      // HashTable interface
      static Ref<HashTable> create() {
        return ref(new HashTable());
      }
      
      Ref<Symbol> get(const std::string& _key);
      bool        has(const std::string& _key) const;

      Iterator begin() const {
        return Iterator(m_first);
      }
  
    public:
      // IObject interface
      const char* typeName() const {
        return "hash table";
      }
      void        pushChildren(ObjectQueue*) const;
    };
  }
}

#endif // INCLUDED_MLISP_OBJECT_HASH_TABLE_HH
