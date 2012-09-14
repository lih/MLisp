#include <cstdlib>
#include <cstddef>

#include "Utils.hh"
#include "Pool.hh"

#pragma GCC diagnostic ignored "-Wpointer-arith"

Pool::Block* Pool::newBlock() const {
  Block* ret=static_cast<Block*>(malloc(sizeof(Block)+m_allocSize*m_blockSize));
  void*  cur=ret->chunks;
  
  ret->next=NULL;
  for(int i=0;i<m_blockSize;++i) {
    static_cast<Chunk*>(cur)->next = static_cast<Chunk*>(cur+m_allocSize);
    cur+=m_allocSize;
  }
  cur-=m_allocSize;
  static_cast<Chunk*>(cur)->next = NULL;
    
  return ret;
}

namespace {
  int defaultBlockSize(unsigned int _allocSize) {
    int ret=(4096/_allocSize);
    return max<int>(ret,16);
  }
}

Pool::Pool(int _allocSize,unsigned int _blockSize)
  : m_firstChunk(NULL),m_firstBlock(NULL),
    m_allocSize(_allocSize),m_blockSize(_blockSize),
    m_allocated(0) {}
Pool::Pool(int _allocSize)
  : m_firstChunk(NULL),m_firstBlock(NULL),
    m_allocSize(_allocSize),m_blockSize(defaultBlockSize(m_allocSize)),
    m_allocated(0) {}

Pool::Pool(const Pool& _other)
  : m_firstChunk(NULL),m_firstBlock(NULL),
    m_allocSize(_other.m_allocSize),m_blockSize(_other.m_blockSize),
    m_allocated(0) {}


void* Pool::allocate() {
  if(m_firstChunk==NULL) {
    Block* newHead=newBlock();

    newHead->next=m_firstBlock;
    m_firstChunk=reinterpret_cast<Chunk*>(newHead->chunks);
    m_firstBlock=newHead;
  }
    
  void* ret=&m_firstChunk->val;
  m_firstChunk=m_firstChunk->next;
  ++m_allocated;

  return ret;
}
void  Pool::free(void* _p)  {
  static_cast<Chunk*>(_p)->next=m_firstChunk;
  m_firstChunk=static_cast<Chunk*>(_p);
  --m_allocated;
}

namespace {
#define until(e) while(!(e))
  template<class _List>
  void move(_List src,_List dst) {
    _List tmp=src.tail();
    src.setTail(tmp.tail());
    tmp.setTail(dst.tail());
    dst.setTail(tmp);
  }
  template<class _List,class _Cmp>
  _List endSeq(_List l) {
    _Cmp less;
    until(l.tail().isNull() || less(l.tail(),l))
      l=l.tail();
    return l;
  }
  template<class _List,class _Cmp>
  void sort_(_List l) {
    int  mergeCount;
    _Cmp less;
    do {
      mergeCount=0;
      _List cur=l;
    
      until(cur.tail().isNull()) {
        _List l1=cur,l2=endSeq<_List,_Cmp>(cur.tail());

        if(!l2.tail().isNull()) {
          _List end=endSeq<_List,_Cmp>(l2.tail()).tail();
          ++mergeCount;
        
          until(l2.tail() == end || l1==l2)
            if(less(l1.tail(),l2.tail()))
              l1=l1.tail();            
            else            
              move(l2,l1);

          if(l1==l2) l2=endSeq<_List,_Cmp>(l2);
        }
        cur=l2;
      }
    } until(mergeCount==0);
  }
    
  template<class _Node>
  class NodeWrapper {
    _Node* m_node;
  public:
    NodeWrapper(_Node* _node) : m_node(_node) {}
    
    NodeWrapper tail() const { return m_node->next; }
    void        setTail(NodeWrapper l) { m_node->next=l.m_node; }

    bool isNull() const { return m_node==NULL; }
    
    operator _Node* () const { return m_node; }

    class Less {
    public:
      bool operator() (NodeWrapper l1, NodeWrapper l2) {
#define rcui reinterpret_cast<ptrdiff_t>
        return rcui(l1.m_node) < rcui(l2.m_node);
#undef rcui
      }
    };
  };

  template<class _Node>
  void sort(_Node** l) {
    _Node tmp;
    tmp.next=*l;
    sort_<NodeWrapper<_Node>,class NodeWrapper<_Node>::Less>(&tmp);
    *l=tmp.next;
    tmp.next=NULL;
  }
#undef until
}

Pool::Iterator Pool::allocated() const {
  sort(&m_firstChunk);
  sort(&m_firstBlock);

  return Iterator(this,m_firstChunk,m_firstBlock,0);
}

Pool::~Pool() {
  while(m_firstBlock!=NULL) {
    Block* tmp=m_firstBlock;
    m_firstBlock=m_firstBlock->next;
    free(tmp);
  }
}

Pool::Iterator::Iterator(const Pool* _parent,Chunk* _curChunk,Block* _curBlock,int _curInd)
  : m_parent(_parent),m_curChunk(_curChunk),
    m_curBlock(_curBlock),m_curVal(NULL),m_curInd(_curInd) {
  if(!end()) {
    m_curVal=m_curBlock->chunks;

    while(m_curChunk==value()) {
      m_Forward();
      m_curChunk=m_curChunk->next;
    }
  }
}
void  Pool::Iterator::m_Forward() {
  m_curInd++;
  
  if(m_curInd>=m_parent->m_blockSize) {
    m_curBlock=m_curBlock->next;
    m_curInd=0;
    if(!end()) 
      m_curVal=m_curBlock->chunks;
  }
  else
    m_curVal += m_parent->m_allocSize;
}
void  Pool::Iterator::forward() {
  if(end()) return;

  m_Forward();
  while(m_curChunk==value()) {
    m_Forward();
    m_curChunk=m_curChunk->next;
  }
}
