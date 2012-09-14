#ifndef INCLUDED_FLAGGED_PTR_HH
#define INCLUDED_FLAGGED_PTR_HH

#include <cstddef>

template<class _T> 
class FlaggedPtr {
    ptrdiff_t m_ptr;

public:
  FlaggedPtr(_T* _p=NULL,bool _b=false) : m_ptr(0) {
    setPtr(_p);
    setFlag(_b);
  }
 
  _T*  ptr() const {
    return reinterpret_cast<_T*>(m_ptr&~1);
  }
  bool flag() const {
    return m_ptr&1;
  }
  void setPtr(_T* _p) {
    m_ptr=flag()|(reinterpret_cast<ptrdiff_t>(_p)&~1);
  }
  void setFlag(bool _f) {
    if(_f) m_ptr|=1;
    else   m_ptr&=~1;
  }

  FlaggedPtr<const _T> constVal() const {
    return FlaggedPtr<const _T>(ptr(),flag());
  }

  _T* operator->() const {
    return ptr();
  }
  _T& operator*() const {
    return *ptr();
  }

  FlaggedPtr& operator=(_T* _p) {
    setPtr(_p);
    return *this;
  }
  
  void operator delete(void*) {
    delete ptr();
  }

  operator _T* () const {
    return ptr();
  }
  operator FlaggedPtr<const _T>() const {
    return constVal();
  }
};

#endif // INCLUDED_FLAGGED_PTR_HH
