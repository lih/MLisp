#ifndef INCLUDED_POOL_HH
#define INCLUDED_POOL_HH

#ifndef NULL
#  define NULL 0
#endif

class Pool {
  typedef unsigned char byte;

  union Chunk {
    byte   val[0];
    Chunk* next;
  };
  struct Block {
    Block*    next;
    Chunk     chunks[0];
  };
  
  mutable Chunk*       m_firstChunk;
  mutable Block*       m_firstBlock;
  const int   m_allocSize;
  const int   m_blockSize;
  int         m_allocated;
  
private:
  Pool() = delete;
  Pool& operator=(const Pool&) = delete;

public:
  Pool(int _allocSize,unsigned int _blockSize);
  explicit Pool(int _allocSize);
  Pool(const Pool&);
  ~Pool();

private:
  Block* newBlock() const;
public:
  void*        allocate();
  void*        alloc() { return allocate(); }
  void         free(void* _p);
  int blockSize() const { return m_blockSize; }

public:
  int nbAllocated() const {
    return m_allocated;
  }
  int allocCount() const {
    return nbAllocated();
  }
    
public:
  class Iterator {
  private:
    friend class Pool;

    const Pool*  m_parent;
    Chunk*       m_curChunk;
    Block*       m_curBlock;
    void*        m_curVal;
    int m_curInd;
    
    Iterator(const Pool*,Chunk*,Block*,int ind);

    void m_Forward();
    
  public:
    void  forward();
    void* value() const { return m_curVal; }
    bool  end() const { return m_curBlock==NULL; }
    
    void* operator*() const { return value(); }
    void  operator++() { forward(); }
    operator bool() const { return !end(); }
  };

  Iterator     allocated() const;
};

#endif // INCLUDED_POOL_HH
