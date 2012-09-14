#ifndef INCLUDED_MLISP_I_POINTER_HH
#define INCLUDED_MLISP_I_POINTER_HH

#include "Utils.hh"

namespace MLisp {
  class IObject;

  class IRef {
    /* A base class for smart pointers for Lisp dynamic objects */
  private:
    // Properties
    IObject* m_ptr;
    
  public:
    // Static interface
    static void collectCycles();
    static void deleteFree();
    static void pseudoDeleteRoot(IObject* _root);
    static void restoreRoot(IObject* _root);
  
  protected:
    // Constructors & Destructors
    IRef(const IRef&);
    IRef(IObject* _ptr=NULL);
    ~IRef();

  protected:
    // Methods
    IObject* ptr() const;
    void     reset(IObject*);
    void     swap(IRef& _other);
    
  public:
    // new[] & delete[]
    void* operator new[](size_t);
    void  operator delete[](void* _ptr,size_t _size);
  };

  inline IObject* IRef::ptr() const { return m_ptr; }
  inline void     IRef::swap(IRef& _other) {
    IObject* tmp=_other.m_ptr;
    _other.m_ptr=m_ptr;
    m_ptr=tmp;
  }
}

#endif // INCLUDED_MLISP_I_POINTER_HH
