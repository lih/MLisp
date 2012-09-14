#ifndef INCLUDED_STACK_HH
#define INCLUDED_STACK_HH

#include <exception>

#include "Array.hh"

namespace Utils {
  template<class _T> 
  class Stack {
  private:
    // Subclasses
    class M_Array : public Array<_T> {
    public:
      M_Array(int _size) : Array<_T>(_size) {}

      _T& operator[](int _index) {
        return Array<_T>::safe_Elt(_index);
      }
      const _T& operator[](int _index) const {
        return Array<_T>::safe_Elt(_index);
      }
    };

  private:
    // Properties
    M_Array      m_array;
    int m_size;

  public:
    // Exceptions
    class Underflow : public std::exception {
    public:
      const char* what() const throw() { return "stack underflow"; }
    };
    class Overflow : public std::exception {
    public:
      const char* what() const throw() { return "stack overflow"; }
    };
  
  public:
    // Methods
    int size() const {
      return m_size;
    }
    int capacity() const {
      return m_array.size();
    }

    bool empty() const {
      return size()==0;
    }
    bool full() const {
      return size()==capacity();
    }

    _T&       top() {
      if(empty()) throw Underflow();

      return m_array[m_size-1];
    }
    const _T& top() const {
      if(empty()) throw Underflow();
    
      return m_array[m_size-1];
    }
    _T&       top(int _nth) {
      if(_nth>=size()) throw Underflow();

      return m_array[m_size-_nth-1];
    }
    const _T& top(int _nth) const {
      if(_nth>=size()) throw Underflow();

      return m_array[m_size-_nth-1];
    }
  
    void resize(int _newSize) {
      if(_newSize<m_size) throw Overflow();

      m_array.resize(_newSize);
    }
  
    void pop() {
      if(empty()) throw Underflow();

      --m_size;
    }
    void pop(_T* _val) {
      if(empty()) throw Underflow();
    
      --m_size;
      *_val=m_array[m_size];
    }
    void pop(int n) {
      if(size()<n) throw Underflow();

      m_size-=n;
    }
    
    void push(const _T& _val=_T()) {
      if(full()) throw Overflow();

      m_array[m_size]=_val;
      ++m_size;
    }

  public:  
    // Constructors & Destructors
    explicit Stack(int _cap=4096) : m_array(_cap), m_size(0) {}
  };
}

#endif // INCLUDED_STACK_HH
