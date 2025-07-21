/**
 * Interface Segregation Principle:
 * 	--> Don't put too much into an interface; split into separate interfaces
 * 	--> YAGNI - You Ain't Going to Need It
 */

#include <vector>
#include <iostream>
#include <memory>
#include <typeinfo>

struct Document{};

//struct IMachine
//{
//  virtual void print(Document& doc) = 0;
//  virtual void fax(Document& doc) = 0;
//  virtual void scan(Document& doc) = 0;
//};
//
//struct MFP : IMachine
//{
//  void print(Document& doc) override;
//  void fax(Document& doc) override;
//  void scan(Document& doc) override;
//};

// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

class IPrinter {
public:
  virtual void print(Document& doc) = 0;
};

class IScanner {
public:
  virtual void scan(Document& doc) = 0;
};

class IFax {
public:
  virtual void fax(Document& doc) = 0;
};

class Printer : public IPrinter {
public:
  void print(Document& doc) override
  {
    std::cout << "Print Document\n";
  }
};

class Scanner : public IScanner {
public:
  void scan(Document& doc) override
  {
    std::cout << "Scan Document\n";
  }
};

class Fax : public IFax {
public:
  void fax(Document& doc) override
  {
    std::cout << "Fax Document\n";
  }
};

class IMachine: public IPrinter, public IScanner, public IFax {
  public:
    void print(Document& doc) override{
      std::cout << "Not yet implemented\n";
    };
    void scan(Document& doc) override{
      std::cout << "Not yet implemented\n";
    };
    void fax(Document& doc) override{
      std::cout << "Not yet implemented\n";
    };
};

class Machine : public IMachine {
private:
  IPrinter& printer;
  IScanner& scanner;
  IFax& faxer;
public:
  Machine(IPrinter& printer, IScanner& scanner, IFax& fax)
    : printer{printer}, scanner{scanner}, faxer{fax}
  {
  }

  void print(Document& doc) override
  {
    printer.print(doc);
  }

  void scan(Document& doc) override
  {
    scanner.scan(doc);
  }

  void fax(Document& doc) override
  {
    faxer.fax(doc);
  }
};

// IPrinter --> Printer
// everything --> Machine

int main(int argc, char **argv)
{
  Document d{};
  Printer p;
  Scanner s;
  Fax f;

  Machine m(p, s, f);

  m.scan(d);
  m.print(d);
  m.fax(d);

  return 0;
}
