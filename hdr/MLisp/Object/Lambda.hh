#ifndef INCLUDED_MLISP_LAMBDA_HH
#define INCLUDED_MLISP_LAMBDA_HH

#include "MLisp/Error.hh"
#include "MLisp/Ref.hh"
#include "MLisp/Object/ICallable.hh"
#include "MLisp/Object/Symbol.hh"
#include "MLisp/Object/Pair.hh"

namespace MLisp {
  namespace Object {
    class Lambda : public ICallable {
    public:
      // Exception TooFewArguments
      class TooFewArguments : public MLisp::Error {
        char m_message[256];
    
      public:
        TooFewArguments(const Lambda& _l,WeakRef<ICstList> _args) {
          snprintf(m_message,256,"too few arguments (%d, expected %d).",_args->length(),_l.m_argsCount);
        }
        const char* what() const throw() { return m_message; }
      };

    private:
      // Bytecode subclass 
      class ByteCode : public IObject {
      private:
        // Bytecode is a non-copyable class
        ByteCode();
        NOT_COPYABLE(ByteCode);

      private:
        // Properties
        Instruction*     m_code;
        int     m_codeSize;
        Ref<IObject>*    m_frame;
        int     m_objectsCount;

        ByteCode(WeakRef<IObject>,CompileState*);
        ~ByteCode() { 
          delete[] m_code;
          delete[] m_frame;
        }
  
      public:
        // Methods
        static Ref<ByteCode> create(WeakRef<IObject> _obj,CompileState* _st) {
          return ref(new ByteCode(_obj,_st));
        }
  
      public:
        // ByteCode interface
        Ref<IObject>       object(int _index) const { return m_frame[_index]; }
        const Instruction* code() const { return m_code; }
      
      public:
        // IObject interface
        void         pushChildren(ObjectQueue* _queue) const;
        void         print() const;
        const char*  typeName() const { return "bytecode"; }
      };

    public:
      // Instance subclass
      class Instance : public IObject {
        NOT_COPYABLE(Instance);
        Instance() = delete;
        
      private:
        // Properties
        Ref<Lambda>  m_lambda;
        Ref<Symbol>* m_args;
        int m_argsCount;
        
      private:
        // Constructors & Destructors
        Instance(WeakRef<Lambda> _fun,WeakRef<ICstList> _args);
        ~Instance() {
          delete[] m_args;
        }

      public:
        // Instance interface
        static Ref<Instance> create(WeakRef<Lambda> _fun,WeakRef<ICstList> _args) {
          return ref(new Instance(_fun,_args));
        }

        WeakRef<Symbol>    param(int _index) const {
          return m_args[_index];
        }
        WeakRef<IObject>   object(int _index) const {
          return m_lambda->object(_index);
        }
        WeakRef<Symbol>    closed(int _index) const {
          return m_lambda->closed(_index);
        } 
        const Instruction* code() {
          return m_lambda->code();
        }

      public:
        // IObject interface
        void        pushChildren(ObjectQueue*) const;
        const char* typeName() const {
          return "lambda instance";
        }
        void        print() const noimpl;
      };

    public:
      // Closure subclass
      class Closure : public IObject {
        friend class Lambda;
        
      private:
        // Constructors & Destructors
        NOT_COPYABLE(Closure);
        Closure() = delete;
        Closure(WeakRef<IObject>,WeakRef<IObject>,CompileState*);
        ~Closure();        
        
      private:
        // Properties
        Ref<ByteCode> m_frame;
        int  m_argsCount;
        Ref<Symbol>*  m_args;
        bool          m_hasTail;
        int  m_closedCount;
        struct ArgMap {
          int val:24;
          bool         imm:1;
        };
        ArgMap* m_closedMap;
    
      public:
        // Closure interface
        static Ref<Closure> create(WeakRef<IObject> _obj,WeakRef<IObject> _args,CompileState* _st=NULL) {
          return ref(new Closure(_obj,_args,_st));
        }
        Ref<Lambda> close() const;

      public:
        // IObject interface
        void pushChildren(ObjectQueue* _q) const;
        void print() const;
        const char* typeName() const { return "closure"; }
      };

    private:
      // Properties
      Ref<ByteCode> m_frame;
      int  m_argsCount;
      Ref<Symbol>*  m_args;
      bool          m_hasTail;
      int  m_closedCount;
      Ref<Symbol>*  m_closed;
      
    private:
      // Constructors & Destructors
      NOT_COPYABLE(Lambda);
      Lambda() = delete;
      Lambda(const Closure*);
      Lambda(WeakRef<IObject> _expr,WeakRef<IObject> _args);
      ~Lambda();

    private:
      // Lambda internals
      Ref<Symbol>*  m_argsInstance(WeakRef<ICstList> _args) const;

    public:  
      // Lambda interface
      static Ref<Lambda> create(WeakRef<IObject> _expr,WeakRef<IObject> _args) {
        return ref(new Lambda(_expr,_args));
      }
      
      WeakRef<IObject>   object(int _index) const {
        return m_frame->object(_index);
      }
      WeakRef<Symbol>    closed(int _index) const {
        return m_closed[_index];
      }
      const Instruction* code() const {
        return m_frame->code();
      }

    public:
      // ICallable interface
      void call(WeakRef<ICstList>,bool) const;

    public:
      // IObject interface
      void        pushChildren(ObjectQueue* _q) const;
      void        print() const;
      const char* typeName() const { 
      return "lambda"; 
    }
    };
  }
}

#endif // INCLUDED_MLISP_LAMBDA_HH
