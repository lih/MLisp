#ifndef INCLUDED_STREAM_HH
#define INCLUDED_STREAM_HH

#include "Utils.hh"

typedef unsigned char byte;

namespace Utils {
  class Closeable {
  public:
    virtual void close() const abstract;
  };

  class InputStream : virtual Closeable {
  public:
    virtual byte get() abstract;
    virtual byte peek() abstract;
    virtual void forward() abstract;

    virtual void read(int _n,void* _dest) abstract;
    
    virtual void close() const abstract;
  };

  class OutputStream : virtual Closeable {
  public:
    virtual void put(byte) abstract;
    virtual void write(void* _src,int _n) abstract;

    virtual void close() const abstract;
  };
}

#endif // INCLUDED_STREAM_HH
