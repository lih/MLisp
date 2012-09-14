#ifndef INCLUDED_MLISP_REF_HH
#define INCLUDED_MLISP_REF_HH

#include "MLisp/IRef.hh"

namespace MLisp {
  template<class _T> class Ref;
  
  template<class _T>
  class WeakRef {
    // For automatic dynamic_cast of environment objects
  private:
    // Properties
    _T* m_ptr;
    
  public:
    // Constructors & Destructors
    explicit WeakRef(_T* _ptr=NULL);
    template<class _U>
    explicit WeakRef(_U* _ptr);
    template<class _U>
    WeakRef(const WeakRef<_U>& _other);
    template<class _U>
    WeakRef(const Ref<_U>& _ref);

  public:
    // Methods
    _T*  ptr() const;
    void reset(_T* _ptr);

    bool isNull() const;

  public:
    // Operators
    _T* operator->() const {
      return ptr();
    }
    _T& operator*() const {
      return *ptr();
    }
  };
  
  template<class _T>
  class Ref : public IRef {
    // A reference to a dynamic object
  public:
    // Constructors & Destructors
    explicit Ref(_T* _ptr=NULL);
    template<class _U>
    Ref(const WeakRef<_U>& _ref);
    template<class _U>
    Ref(const Ref<_U>& _other);
    template<class _U>
    Ref(Ref<_U>&& _other);
    
  public:  
    // Methods
    _T*  ptr() const;
    void reset(_T* _ptr);

    bool isNull() const;

  public:
    // Operators
    _T* operator->() const {
      return ptr();
    }
    _T& operator*() const {
      return *ptr();
    }

    Ref& operator=(const Ref& _other) {
      reset(_other.ptr());
      return *this;
    }
    template<class _U>
    Ref& operator=(const WeakRef<_U>& _ref) {
      reset(dynamic_cast<_T*>(_ref.ptr()));
      return *this;
    }
    template<class _U>
    Ref& operator=(const Ref<_U>& _other) {
      reset(dynamic_cast<_T*>(_other.ptr()));
      return *this;
    }
    template<class _U>
    Ref& operator=(Ref<_U>&& _other) {
      if(dynamic_cast<_T*>(_other.ptr())==NULL)
        reset(NULL);
      else
        swap(_other);
      return *this;
    }
  };

  template<class _T>
  WeakRef<_T> weakRef(_T* _ptr) {
    return WeakRef<_T>(_ptr);
  }
  template<class _T>
  Ref<_T> ref(_T* _ptr) {
    return Ref<_T>(_ptr);
  }

  /*
   * WeakRef implementation 
   */
  // Constructors & Destructors
  template<class _T>
  inline
  WeakRef<_T>::WeakRef(_T* _ptr) : m_ptr(_ptr) {}
  template<class _T>
  template<class _U>
  inline 
  WeakRef<_T>::WeakRef(_U* _ptr) : m_ptr(dynamic_cast<_T*>(_ptr)) {}
  template<class _T>
  template<class _U>
  inline 
  WeakRef<_T>::WeakRef(const WeakRef<_U>& _other)
    : m_ptr(dynamic_cast<_T*>(_other.ptr())) {}
  template<class _T>
  template<class _U>
  inline 
  WeakRef<_T>::WeakRef(const Ref<_U>& _ref)
    : m_ptr(dynamic_cast<_T*>(_ref.ptr())) {}
  
  // Methods
  template<class _T>
  inline 
  _T*  WeakRef<_T>::ptr() const {
    return m_ptr;
  }
  template<class _T>
  inline 
  void WeakRef<_T>::reset(_T* _ptr) {
    m_ptr=_ptr;
  }
  template<class _T>
  inline 
  bool WeakRef<_T>::isNull() const {
    return ptr()==NULL;
  }

  /*
   * Ref implementation 
   */
  // Constructors & Destructors
  template<class _T>
  inline
  Ref<_T>::Ref(_T* _ptr) : IRef(_ptr) {}
  template<class _T>
  template<class _U>
  inline 
  Ref<_T>::Ref(const WeakRef<_U>& _ref)
    : IRef(dynamic_cast<_T*>(_ref.ptr())) {}
  template<class _T>
  template<class _U>
  inline 
  Ref<_T>::Ref(const Ref<_U>& _other)
     : IRef(dynamic_cast<_T*>(_other.ptr())) {}
  template<class _T>
  template<class _U>
  inline 
  Ref<_T>::Ref(Ref<_U>&& _other) {
    if(dynamic_cast<_T*>(_other.ptr())!=NULL)
      swap(_other);
  }
  
  // Methods
  template<class _T>
  inline 
  _T*  Ref<_T>::ptr() const {
    return static_cast<_T*>(IRef:: ptr());
  }
  template<class _T>
  inline 
  void Ref<_T>::reset(_T* _ptr) {
    IRef::reset(_ptr);
  }
  template<class _T>
  inline 
  bool Ref<_T>::isNull() const {
    return ptr()==NULL;
  }
}

#endif // INCLUDED_MLISP_REF_HH
