#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#include "Utils.hh"
#include "MLisp.hpp"
#include "Reader.hh"

#include "main.test.hh"
#include "main.hh"

using namespace MLisp;
using namespace Object;

std::ostream& operator<<(std::ostream& _out,const IObject& _obj) {
  _obj.print();
  return _out;
}

int main(int argc,char* argv[]) {
  Environment env;
  s_curEnv=&env;

#ifdef MLISP_TEST
  MLisp_test();
#endif
  if(argc>2) {
    printf("Wrong number of arguments (%d,should be <=1).\n",argc-1);
    exit(EXIT_FAILURE); 
  }

  std::cout << "MLisp : a minimal Lisp environment." << std::endl;
  std::cout << "Copyright Marc Coiffier 2010-2011."  << std::endl;

  try {
    InputStream::File file(argc==1?"/dev/stdin":argv[1]);
    Reader            reader(file.handle());
    while(true) {
      try {
        if(argc==1) 
          std::cout << "> " << std::flush;
        Ref<IObject> expr=reader.read();
        Ref<Lambda> l=Lambda::create(expr,Nil::instance());
        
        // std::cout << *expr << std::endl;
        // l->print();    printf("\n");
        l->call(Nil::instance(),false);
        Ref<IObject> ret=s_curEnv->eval();
        
        std::cout << " => " << *ret;
        printf("\n");
      }
      catch(const MLisp::Error& _e) {
        std::cout << _e.what() << std::endl;
      }
      catch(const Reader::ReadError& _e) {
        std::cout << "reader: " << _e.what() << std::endl;
        reader.nextLine();
      }
    }
  }
  catch(const InputStream::EndOfFile&) {}
  
  std::cout << "\rPlease come back soon !"  << std::endl;

  return 0;
}
