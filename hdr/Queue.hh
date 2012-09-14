#ifndef INCLUDED_QUEUE_HH
#define INCLUDED_QUEUE_HH

#include "Array.hh" 

namespace Utils {
  template<class _T>
  class Queue {
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
  
    M_Array m_array;
    int m_front;
    int m_back;
    int m_size;

  public:
    // Exceptions
    class Underflow : public std::exception {
    public:
      const char* what() const throw() { return "queue underflow"; }
    };
    class Overflow : public std::exception {
    public:
      const char* what() const throw() { return "queue overflow"; }
    };

  public:
    // Methods
    int size() const { return m_size; };
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

      return m_array[m_front];
    }
    const _T& top() const {
      if(empty()) throw Underflow();
    
      return m_array[m_front];
    }
    _T&       top(int _n) {
      if(_n>=size()) throw Underflow();

      return m_array[(m_front+_n>=capacity())?m_front+_n-capacity():m_front+_n];
    }
    const _T& top(int _n) const {
      if(_n>=size()) throw Underflow();

      return m_array[(m_front+_n>=capacity())?m_front+_n-capacity():m_front+_n];
    }

    void resize(int _newCap) {
      if(_newCap<m_size) throw Overflow();

      if(_newCap<capacity()) {
        if(m_front+m_size>=_newCap) {
          if(m_front+m_size>=capacity()) {
            for(int i=m_front;i<m_array.size();++i)
              m_array[i+_newCap-capacity()]=m_array[i];
            m_front+=_newCap-capacity();
          }
          else {
            for(int i=_newCap;i<m_front+m_size;++i)
              m_array[i-_newCap]=m_array[i];
            m_back-=_newCap;
          }
        }
        m_array.resize(_newCap);
      }
      else {
        int oldSize=m_array.size();
      
        m_array.resize(_newCap);
        if(m_front+m_size>=oldSize) {
          for(int i=_newCap;i>m_front+_newCap-oldSize;--i)
            m_array[i-1]=m_array[i-1-_newCap+oldSize];
          m_front+=_newCap-oldSize;
        }
      }
    }
  
    void pop() {
      if(empty()) throw Underflow();

      ++m_front;
      if(m_front==m_array.size())
        m_front=0;
      --m_size;
    }
    void pop(_T* _dest) {
      *_dest=top();
      pop();
    }

    void push(const _T& _val=_T()) {
      if(full()) throw Overflow();

      m_array[m_back]=_val;
      ++m_back;
      if(m_back==m_array.size())
        m_back=0;

      ++m_size;
    }

  public:
    // Constructors & Destructors
    Queue(int _size=4096) : m_array(_size),m_front(0),m_back(0),m_size(0) {}
  };
}

#endif // INCLUDED_QUEUE_HH
