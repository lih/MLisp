#ifndef INCLUDED_MLISP_DARRAY_HH
#define INCLUDED_MLISP_DARRAY_HH

#include "Utils.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Object/IArray.hh"
#include "MLisp/Object/IList.hh"

namespace MLisp {
  namespace Object {
    class Array : public IArray {
      Array();
      NOT_COPYABLE(Array);
  
    private:
      // Properties & Constructors
      const int  m_size;
      Ref<IObject>*       m_data;
 
      Array(int);
      Array(WeakRef<ICstList> _l);
      void pushChildren(ObjectQueue*) const;

      ~Array();

    public:
      static Ref<Array> create(int _size) {
        return ref(new Array(_size));
      }
      static Ref<Array> create(WeakRef<ICstList> _l) {
        return ref(new Array(_l));
      }
 
      Ref<IObject> elt(int _index) const {
        return m_data[_index];
      }
      void         setElt(int _index,WeakRef<IObject> _val) {
        changeRef(_val.ptr());
        m_data[_index]=_val;
      }
  
      int size() const {
        return m_size;
      }

    public:
      const char* typeName() const { return "array"; }
      void        print() const;
      bool        operator==(const IObject&) const noimpl;
    };
  }
}

#endif // INCLUDED_MLISP_DARRAY_HH
