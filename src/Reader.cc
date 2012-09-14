#include <stdint.h>
#include <cstdlib>
#include <string>
#include "Reader.hh"
#include "MLisp.hpp"

using namespace MLisp;
using namespace Object;

namespace {
  class UnknownBuiltin : public Reader::ReadError {
    char m_message[256];
    
  public:
    UnknownBuiltin(const char* _name) {
      snprintf(m_message,256,"unknown builtin %s",_name);
    }
    const char* what() const throw() { return m_message; }
  };

  class BlankChar {
    bool m_blank[256];
    
  public:
    BlankChar() {
      for(int i=0;i<256;++i)
        m_blank[i]=false;
      m_blank[' ']=true;
      m_blank['\t']=true;
      m_blank['\n']=true;
    }
    bool operator[](int _index) const {
      return m_blank[_index];
    }
  } s_blank;
  bool isblank(char _car) {
    return s_blank[_car];
  }
  class SymbolChar {
    bool m_blank[256];
    
  public:
    SymbolChar() {
      for(int i=0;i<256;++i)
        m_blank[i]=true;
      m_blank[' ']=false;
      m_blank['\t']=false;
      m_blank['\n']=false;
      m_blank[')']=false;
      m_blank['(']=false;
    }
    bool operator[](int _index) const {
      return m_blank[_index];
    }
  } s_symbol;
  bool issymbol(char _car) {
    return s_symbol[_car];
  }

  class QuotedChar {
    char m_quoted[256];
    
  public:
    QuotedChar() {
      for(int i=0;i<256;++i)
        m_quoted[i]=i;
      m_quoted['n']='\n';
      m_quoted['t']='\t';
      m_quoted['r']='\r';
    }
    char operator[](int _index) const {
      return m_quoted[_index];
    }
  } s_quoted;
}

void InputStream::skipBlanks() {
  while(isblank(current())) forward();
}
void InputStream::nextLine() {
  while(current()!='\n') forward();
  forward();
}

Reader::Reader(FILE* _input) : m_input(_input) {}
Reader::~Reader() {}

Ref<IObject> Reader::read() {
#define cur (m_input.current())
  m_input.skipBlanks(); 
  
  if(isdigit(cur)) {
    char str[256];
    int size=0;
    bool isFloat=false;
    while(isdigit(cur)) {
      str[size++]=cur;
      m_input.forward();
    }
    if(cur=='.') {
      isFloat=true;
      str[size++]=cur;
      m_input.forward();
      while(isdigit(cur)) {
        str[size++]=cur;
        m_input.forward();
      }
    }
    str[size]='\0';
    if(isFloat)
      return Float::create(atof(str));
    else
      return Integer::create(atoi(str));
  }
  else if(cur=='(') {
    Ref<ICstList> ret=Nil::instance();
    m_input.forward();
    while(cur!=')' && cur!='.') {
      ret=Pair::create(read(),ret);
      m_input.skipBlanks();
    }
    if(cur=='.') {
      m_input.forward();
      Ref<IObject> tail=read();
      m_input.skipBlanks();
      if(cur!=')') throw ReadError();        
      m_input.forward();
      return ret->reverse()->append(tail);
    }
    else {
      m_input.forward();
      return ret->reverse();
    }
  }
  else if(cur=='{') {
    Ref<ICstList> ret=Nil::instance();
    m_input.forward();
    while(cur!='}') {
      ret=Pair::create(read(),ret);
      m_input.skipBlanks();
    }
    m_input.forward();
    return Pair::create(s_curEnv->obarray().get("progn"),ret->reverse());
  }
  else if(cur=='"') {
    char str[256];
    int size=0;
    m_input.forward();
    while(cur!='"') {
      if(cur=='\\') {
        m_input.forward();
        str[size++]=s_quoted[cur];
      }
      else
        str[size++]=cur;
      m_input.forward();
    }
    m_input.forward();
    str[size]='\0';
    return String::create(str);
  }
  else if(cur=='\'') {
    m_input.forward();
    return Pair::create(SpecialForm::Quote::instance(),
                     Pair::create(read(),Nil::instance()));
  }
  else if(cur=='`') {
    m_input.forward();
    return Pair::create(s_curEnv->obarray().get("backquote-quote"),
                      Pair::create(read(),Nil::instance()));
  }
  else if(cur==',') {
    m_input.forward();
    return Pair::create(s_curEnv->obarray().get("backquote-unquote"),
                      Pair::create(read(),Nil::instance()));
  }
  else if(cur==';') {
    m_input.nextLine();
    return read();
  }
  else if(cur=='@') {
    m_input.forward();
    char name[256];
    int size=0;
    while(issymbol(cur)) {
      name[size++]=cur;
      m_input.forward();
    }
    name[size]='\0';
    if(!s_curEnv->builtins().has(name))
      throw UnknownBuiltin(name);
    return s_curEnv->builtins().get(name)->value();
  }
  else if(issymbol(cur)) {
    char name[256];
    int size=0;
    while(issymbol(cur)) {
      name[size++]=cur;
      m_input.forward();
    }
    name[size]='\0';
    return s_curEnv->obarray().get(name);
  }
  else throw ReadError();
#undef cur
}
void         Reader::nextLine() {
  m_input.nextLine();
}
