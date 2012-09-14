#ifndef INCLUDED_M_LISP_HH
#define INCLUDED_M_LISP_HH

#include <cstdio>

int __main_wrapped(int argc,char* argv[]);

int main(int argc,char* argv[]) {
  try {
    return __main_wrapped(argc,argv);
  }
  catch(const char* _c) {
    printf("%s\n",_c);
  }
}

#define main __main_wrapped

#endif // INCLUDED_M_LISP_HH
