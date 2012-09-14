#ifndef INCLUDED_UTILS_HH
#define INCLUDED_UTILS_HH

#include <cstdio>

#ifndef NULL
#  define NULL
#endif

template<class _T>
inline _T max(_T a,_T b) { return a>b?a:b; }
template<class _T>
inline _T min(_T a,_T b) { return a<b?a:b; }

#define NOT_COPYABLE(t) t(const t&) = delete; t& operator=(const t&) = delete;

/* A readability macro for pure virtual functions */
#define line___(l) #l
#define line__(l) line___(l)
#define line_ line__(__LINE__)
#define ERROR(s) ("\n" __FILE__ ":" line_ ": error: " s)

#define DEBUG_PRINT(fmt,...) do printf(__FILE__ ":" line_ ": " fmt "\n",## __VA_ARGS__); while(false)
#define DEBUG_OK DEBUG_PRINT("OK")
#define DEBUG_NOT_OK DEBUG_PRINT("Not OK")
class __Enter__ {
    const char* m_value;
  
  public:
    __Enter__(const char* _val) : m_value(_val) {
      printf("++ %s()\n",m_value);
    }
    ~__Enter__() {
      printf("-- %s()\n",m_value);
    }
  };
#define DEBUG_ENTRY(n) __Enter__ __en__(#n)

/* type fun(args...) [const] noimpl means that 'fun' is unimplemented, giving
   it a default implementation that prints a helpful ERROR message and exits
 */
#define abstract =0
#define todo do throw ERROR("functionality not present."); while(false)
#define noimpl { throw ERROR("function not implemented."); }

#endif // INCLUDED_UTILS_HH
