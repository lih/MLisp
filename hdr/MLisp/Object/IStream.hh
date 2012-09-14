#ifndef INCLUDED_MLISP_OBJECT_I_STREAM_HH
#define INCLUDED_MLISP_OBJECT_I_STREAM_HH

#include "MLisp/IObject.hh"
#include "MLisp/Object/String.hh"
#include "MLisp/Object/Integer.hh"

namespace MLisp {
  namespace Object {
    class IStream : public IObject {
      OBJECT_INTERFACE(IStream,IObject);
      
    public:
      // enum OpenMode
      enum OpenMode {
        READ=1,WRITE=2,
        RW=READ|WRITE
      };

    private:
      // Properties
      OpenMode m_mode;

    protected:
      // Constructors & Destructors
      IStream(OpenMode _mode);

    public:
      // IStream interface
      bool                 isWritable() const {
        return (m_mode&WRITE)==WRITE;
      }
      virtual void         write(WeakRef<String> _str) abstract;
      
      bool                 isReadable() const {
        return (m_mode&READ)==READ;
      }
      virtual Ref<String>  read(int _n) abstract;
      virtual Ref<Integer> get() abstract;
    };
  }
}

#endif // INCLUDED_MLISP_OBJECT_I_STREAM_HH
