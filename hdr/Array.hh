#ifndef INCLUDED_ARRAY_HH
#define INCLUDED_ARRAY_HH

#include <exception>

#ifndef NULL
#  define NULL 0
#endif

namespace Utils {
  template<class _T>
  class Array {
    // A class that implements a resizable array
  private:
    // Properties
    _T* m_tab;
    int m_size;
    int m_capacity;

  public:
    // Exceptions
    class OutOfBounds : public std::exception {
    public:
      const char* what() const throw() {
        return "index out of bounds";
      }
    };

  protected:
    // Safe methods
    _T& safe_Elt(int _index) {
      return m_tab[_index];
    }
    const _T& safe_Elt(int _index) const {
      return m_tab[_index];
    }

  public:
    // Methods
    void fill(const _T& _elt) {
      for(int i=0;i<m_size;++i)
        m_tab[i]=_elt;
    }
    void resize(int _newsize) {
      if(_newsize>m_capacity) {
        _T* tmp=m_tab;
        m_tab=new _T[_newsize];
        m_capacity=_newsize;
        for(int i=0;i<m_size;++i)
          m_tab[i]=tmp[i];
        if(tmp!=NULL) delete[] tmp;
      }

      m_size=_newsize;
    }
    void assign(const Array& _other) {
      resize(_other.m_size);
      for(int i=0;i<m_size;++i)
        m_tab[i]=_other.m_tab[i];
    }

    int size() const {
      return m_size;
    }
    int capacity() const {
      return m_capacity;
    }

    _T&       elt(int _index) {
      if(_index>=m_size) throw OutOfBounds();

      return safe_Elt(_index);
    }
    const _T& elt(int _index) const {
      if(_index>=m_size) throw OutOfBounds();

      return safe_Elt(_index);
    }

  public:
    // Constuctors & destructors
    explicit Array(int _size=0,const _T& _elt=_T()) 
      : m_tab(NULL),m_size(0),m_capacity(0) {
      resize(_size);
      fill(_elt);
    }
    Array(const Array& _other) : m_size(_other.m_size),m_capacity(m_size),m_tab(NULL) {
    
    }

    ~Array() {
      if(m_tab!=NULL) delete[] m_tab;
    }

  public:
    // Operators
    _T&       operator[](int _index) {
      return elt(_index);
    }
    const _T& operator[](int _index) const {
      return elt(_index);
    }
  };
}

#endif // INCLUDED_ARRAY_HH
