#ifndef INCLUDED_TEST_MACROS_HH
#define INCLUDED_TEST_MACROS_HH

#include <cstdio>
#include <cstdlib>

class Test {
  static int ms_depth;
public:
  Test(const char* _test) {
    printIndent();
    printf("Testing %s...\n",_test);
    fflush(stdout);
    ++ms_depth;
  }
  static void printIndent() {
    for(int i=0;i<ms_depth;++i)
      printf("  ");
  }
  ~Test() {
    --ms_depth;
  }
};

#define ENTER_TEST(what) Test _(what);
#define TEST(something) {                                        \
    if(!(something)) {                                           \
      printf("\n%s: %d: Failed test %s.\n", __FILE__ , __LINE__ , #something );     \
      exit(EXIT_FAILURE);                                        \
    }                                                            \
  }
#define TEST_PRINT(fmt,...) do {                \
    Test::printIndent(); printf("> " fmt "\n", ## __VA_ARGS__); \
  } while(false)

#endif // INCLUDED_TEST_MACROS_HH
