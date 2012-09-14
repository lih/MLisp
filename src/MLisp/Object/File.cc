#include "MLisp/Object/File.hh"
#include <cstdio>

using namespace MLisp;
using namespace Object;

File::File(WeakRef<String> _name) : m_hFile(fopen(_name->data(),"rw")) {}
File::~File() {
  fclose(m_hFile);
}

void         File::write(WeakRef<String> _str) {
  fputs(_str->data(),m_hFile);
}
Ref<String>  File::read(int _n) {
    char* data = new char[_n+1];

    fgets(data,_n+1,m_hFile);

    Ref<String> ret = String::create(data);

    delete[] data;

    return ret;
}
Ref<Integer> File::get() {
  return Integer::create(getc(m_hFile));
}

