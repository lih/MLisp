#ifndef INCLUDED_MLISP_I_DYN_OBJ_HH
#define INCLUDED_MLISP_I_DYN_OBJ_HH

#include "Utils.hh"
#include "Queue.hh"
#include "Pool.hh"

#include "MLisp/IOperation.hh"

namespace MLisp {
  struct CompileState;
 
  class IObject {
    /* The parent class for all dynamic objects in the Lisp environment. */
    friend class IRef;
    NOT_COPYABLE(IObject);
  
  protected:
    // Subclass ObjectQueue
    class ObjectQueue : public Utils::Queue<IObject*> {
      // A queue that automatically resizes itself
    public:
      explicit ObjectQueue(int _size) : Utils::Queue<IObject*>(_size) {}
      void push(IObject* _ptr) {
        if(full()) resize(2*size());
        Utils::Queue<IObject*>::push(_ptr);
      }
    };

  private:
    // Garbage collection properties
    enum State {
      /* Describes the state of an object */
      UNKNOWN,        // The object may be member of a cycle, or not
      PROOT,          // The object is a possible root of a cycle
      NOT_PROOT,      // The object cannot be a possible root (object never modified)
      LEAF            // The object is a leaf (cannot ever be a root)
    };
    struct GCData {
      int refCount:28;
      State        state:3;
      bool         buffered:1;

      GCData(State _st=UNKNOWN,int _refCount=0) : refCount(_refCount),state(_st),buffered(false) {}
    } m_gcData;

  private:
    // Static variables
    static int ms_nAllocated;

  protected:
    // Tag classes
    struct StaticLeafTag {};
    struct LeafTag {};
    static const LeafTag leafTag;
    static const StaticLeafTag staticLeafTag;

  protected:
    // Constructors & Destructors
    IObject() : m_gcData(NOT_PROOT) {}
    IObject(LeafTag) : m_gcData(LEAF) {}
    IObject(StaticLeafTag) : m_gcData(LEAF,1) {}
    virtual ~IObject() {}

  protected:
    // new & delete 
    void* operator new(size_t _size);
    void  operator delete(void* _p,size_t _size);

  protected:
    // Garbage collection internals
    void changeRef(const IObject* _refChanged) { 
      // If object is green (cannot be a root), makes it of unknown state
      if(m_gcData.state==NOT_PROOT && _refChanged!=NULL && _refChanged->m_gcData.state!=LEAF)
        m_gcData.state=UNKNOWN;
    } 
    virtual void  pushChildren(ObjectQueue*) const abstract;
     
  public:
    // Compilation interface
    virtual void compile(CompileState*) const;
  
  public:
    // IObject interface
    static void         collectCycles();
    static int countAllocated();
    int        refCount() const { return m_gcData.refCount; }
    
    virtual const char* typeName() const abstract;
    virtual void        print() const;
    virtual bool        equal(const IObject& _other) const {
      return this==&_other;
    }

    template<class _T>
    bool is() const {
      return dynamic_cast<const _T*>(this)!=NULL;
    }
    
  public:
    // Operators
    bool operator==(const IObject& _other) const {
      return equal(_other);
    }
  };
}

#define OBJECT_INTERFACE(t,p)                                        \
  protected:                                                         \
  t() {}                                                             \
  t(LeafTag _) : p(_) {}                                             \
  t(StaticLeafTag _) : p(_) {}                                       \
  t(const t&) = delete;                                              \
  t& operator=(const t&) = delete;                                   \
  
#endif // INCLUDED_MLISP_I_DYN_OBJ_HH
