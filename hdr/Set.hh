#ifndef INCLUDED_SET_HH
#define INCLUDED_SET_HH

#include <functional> // for std::less

#include "FlaggedPtr.hh"
#include "AVLTree.hh"

namespace Utils {
  template<class _T>
  class Set {
    /* A class representing a set of _T.
     * You can :
     *   - query it for the presence of an element
     *   - add/delete elements to/from it
     *   - iterate through its elements
     */
  private:
    // Utility typedefs
    typedef FlaggedPtr<typename AVLTree<_T>::Node> FPN;
    typedef std::less<_T>  Less;

  private:
    // Properties
    AVLTree<_T,Less> m_tree;
    int     m_size;
 
  public:
    // Iterator class
    typedef class AVLTree<_T,Less>::Iterator Iterator;
 
  public:
    // Public interface
    Set() : m_size(0) {}
  
    int size() const {
      return m_size;
    }
    bool empty() const {
      return size()==0;
    }

    bool contains(const _T& _elem) const {
      FPN cur=m_tree.root();
      Less less;
      
      while(!cur.flag()) {
        if(less(cur->value(),_elem)) cur=cur->right();
        else if(less(_elem,cur->value())) cur=cur->left();
        else return true;
      }
    
      return false;
    }
    bool insert(const _T& _elem) {
      if(m_tree.insert(_elem)) {
        ++m_size;
        return true;
      }
      else
        return false;
    }
    bool erase(const _T& _elem) {
      if(m_tree.erase(_elem)) {
        --m_size;
        return true;
      }
      else
        return false;
    }
  
    Iterator begin() const {
      return m_tree.begin();
    }
    Iterator end() const {
      return m_tree.end();
    }

    ~Set() {}
  };
}

#endif // INCLUDED_SET_HH
