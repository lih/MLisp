#ifndef INCLUDED_MLISP_STRING_HH
#define INCLUDED_MLISP_STRING_HH

#include "MLisp/Ref.hh"
#include "MLisp/Object/IArray.hh"

namespace MLisp {
  namespace Object {
    class String : public IArray {
      char*              m_data;
      const int m_size;
    
      String(const char* _data);
      ~String();

      void pushChildren(ObjectQueue*) const {}

    public:
      // String interface
      static Ref<String> create(const char* _data) {
        return ref(new String(_data));
      }
      
      const char* data() const {
        return m_data;
      }
      char operator[](int _index) {
        return m_data[_index];
      }
    
    public:
      // IArray interface
      int size() const { return m_size; }

      Ref<IObject> elt(int _index) const;
      void         setElt(int,WeakRef<IObject>);

    public:
      const char* typeName() const { return "string"; }
      void print() const;
      bool operator==(const IObject& _other) const;
    };
  }
}

#endif // INCLUDED_MLISP_STRING_HH
