#ifndef INCLUDED_MLISP_OBJECT_FILE_HH
#define INCLUDED_MLISP_OBJECT_FILE_HH

#include "MLisp/Object/IStream.hh"
#include <cstdio>

namespace MLisp {
  namespace Object {
    class File : public IStream {
      NOT_COPYABLE(File);

    private:
      // Properties
      FILE* m_hFile;
      
    private:
      // Constructors & Destructors
      File() = delete;
      File(WeakRef<String> _name);
      ~File();

    public:
      // File interface
      static Ref<File> create(WeakRef<String> _name) {
        return ref(new File(_name));
      }
      
    public:
      // IStream interface
      void        write(WeakRef<String> _str);

      Ref<String>  read(int _n);
      Ref<Integer> get();
      
    public:
      // IObject interface
      const char* typeName() const { return "file"; }
      void        pushChildren(ObjectQueue*) const {}
    };
  }
}

#endif // INCLUDED_MLISP_OBJECT_FILE_HH
