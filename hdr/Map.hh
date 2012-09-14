#ifndef INCLUDED_MAP_HH
#define INCLUDED_MAP_HH

#include <functional>

#include "AVLTree.hh"
#include "FlaggedPtr.hh"

namespace Utils {
  template<class _Key,class _Val>
  class Map {
  private:
    struct Assoc {
      _Key key;
      mutable _Val val;
  
      struct Less {
        bool operator() (const Assoc& _x,const Assoc& _y) {
          std::less<_Key> less;
          return less(_x.key,_y.key);
        }
      };
    };

    typedef AVLTree<Assoc,class Assoc::Less> Tree;

    Tree m_tree;
    int m_size;
  
  private:
    // Utility typedefs
    typedef FlaggedPtr<class Tree::Node> FPN;
  
  public:
    // Iterator classes
    class Iterator : private Tree::Iterator {
      typedef class Tree::Iterator Parent;
    
    public:
      Iterator(const Parent& _it) : Parent(_it) {}    
    
      _Val& value() {
        return Parent::value().val;
      }
      const _Key& key() {
        return Parent::value().key;
      }

      void forward() { Parent::forward(); }
      void backward() { Parent::backward(); }
 
      _Val& operator*() {
        return value();
      }
      _Val* operator->() {
        return &value();
      }
    
      Iterator& operator++() {
        forward();
        return *this;
      }
      Iterator& operator--() {
        backward();
        return *this;
      }
    
      bool operator==(const Iterator& _other) const {
        return equal(_other);
      }
      bool operator!=(const Iterator& _other) const {
        return NEqual(_other);
      }
    };
    class CIterator : private Tree::CIterator {
      typedef class Tree::CIterator Parent;
    
    public:
      const _Val& value() {
        return Parent::value().val;
      }
      const _Key& key() {
        return Parent::value().key;
      }

      void forward() { Parent::forward(); }
      void backward() { Parent::backward(); }
    
      const _Val& operator*() {
        return value();
      }
      const _Val* operator->() {
        return &value();
      }
    
      CIterator& operator++() {
        forward();
        return *this;
      }
      CIterator& operator--() {
        backward();
        return *this;
      }
    };

  public:
    // Public interface
    Map() : m_size(0) {}

#pragma GCC diagnostic ignored "-Wreturn-type"
    _Val& element(const _Key& _key)  {
      Assoc ass;
      class Assoc::Less less;
      ass.key=_key;
      if(m_tree.insert(ass)) ++m_size;
      FPN cur=m_tree.root();
    
      while(!cur.flag()) {
        if(less(ass,cur->value()))
          cur=cur->left();
        else if(less(cur->value(),ass))
          cur=cur->right();
        else
          return cur->value().val;
      }

      return cur->value().val;
    }
#pragma GCC diagnostic warning "-Wreturn-type"
  
    bool  contains(const _Key& _key) {
      if(m_tree.empty()) return false;

      Assoc ass;
      class Assoc::Less less;
      FPN cur=m_tree.root();
    
      ass.key=_key;

      while(!cur.flag()) {
        if(less(ass,cur->value()))
          cur=cur->left();
        else if(less(cur->value(),ass))
          cur=cur->right();
        else
          return true;
      }

      return false;
    }

    int size() const {
      return m_size;
    }

    Iterator begin() const {
      return m_tree.begin();
    }
    Iterator end() const {
      return m_tree.end();
    }

    _Val& operator[](const _Key& _key) {
      return element(_key);
    }
  };
}

#endif // INCLUDED_MAP_HH
