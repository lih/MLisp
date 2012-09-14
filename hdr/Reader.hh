#ifndef INCLUDED_READER_HH
#define INCLUDED_READER_HH

#include <cstdio>
#include <exception>
#include "Utils.hh"
#include "MLisp/Ref.hh"
#include "MLisp/IObject.hh"

class InputStream {
public:
  // Exception EndOfFile
  class EndOfFile : public std::exception {
  public:
    const char* what() const throw() {
      return "end of file";
    }
  };

public:
  // Subclass File
  class File {
  private:
    // Properties
    FILE* m_hFile;
    
  public:
    // Constructors & Destructors
    File(const char* _name) : m_hFile(fopen(_name,"r")) {}
    ~File() {
      fclose(m_hFile);
    }
    
  public:
    // File interface
    FILE* handle() const { return m_hFile; }
  };

private:
  // Properties
  FILE* m_hStream;
  
public:
  // Constructors & Destructors
  InputStream(FILE* _hStream=stdin) : m_hStream(_hStream) {}
  
public:
  // InputStream interface
  char current() const {
    if(end()) throw EndOfFile();
    char ret=getc(m_hStream);
    ungetc(ret,m_hStream);
    return ret;
  }
  void forward() {
    getc(m_hStream);
  }
  void get(char* _val) {
    if(end()) throw EndOfFile();
    *_val=getc(m_hStream);
  }
  
  void skipBlanks();
  void nextLine();
  
  bool end() const { return feof(m_hStream); }
};

class Reader {
  typedef MLisp::IObject IObject;

public:
  // Exception ReadError
  class ReadError : public std::exception {
  public:
    const char* what() const throw() {
      return "read error";
    }
  };

private:
  // Properties
  InputStream     m_input;

public:
  // Constructors & Destructors
  Reader(FILE* _in=stdin);
  ~Reader();

public:
  // Reader interface
  MLisp::Ref<IObject> read();
  void                nextLine();
  bool end() const noimpl;
};

#endif // INCLUDED_READER_HH
