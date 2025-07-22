#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <sstream>

class Address
{
private:
  std::string street;
  std::string city;
  int suite;

  friend std::ostream& operator<<(std::ostream& os, const Address& obj)
  {
    return os
      << "street: " << obj.street
      << " city: " << obj.city
      << " suite: " << obj.suite;
  }

public:
  Address(const std::string& street, const std::string& city, const int suite)
    : street{street},
      city{city},
      suite{suite}
  {
  }

  Address(const Address& other)
    : street{other.street},
      city{other.city},
      suite{other.suite}
  {
  }

  std::string getStreet() const {
    return street;
  }

  void setStreet(const std::string &street) {
    this->street = street;
  }

  std::string getCity() const {
    return city;
  }

  void setCity(const std::string& city) {
    this->city = city;
  }

  int getSuite() const {
    return suite;
  }

  void setSuite(int suite) {
    this->suite = suite;
  }
};


class Contact
{
private:
  std::string name;
  Address* address;
  bool is_deep_copy;

  friend std::ostream& operator<<(std::ostream& os, const Contact& obj)
  {
    return os
      << "name: " << obj.name
      << " works at " << *obj.address; // note the star here
  }

public:
  // Assignment operator
  Contact& operator=(const Contact& other)
  {
    if (this == &other)
      return *this;
    std::cout << "Contact Assignment operator Shallow copy\n";
    name = other.name;
    address = other.address;
    return *this;
  }

  Contact() : name(nullptr), address(nullptr), is_deep_copy(false)
  {
    std::cout << "Contact default constructor\n";
  } // required for serialization

  Contact(const std::string& name, Address* address)
    : name{name}
    , address{address}
    , is_deep_copy(false)
  {
    std::cout << "Contact constructor with allocated address \n";
    // this->address = new Address{ *address };
  }

  // Copy constructor
  Contact(const Contact& other)
    : name{other.name}
    , is_deep_copy(true)
    // , address{ new Address{*other.address} }
  {
    std::cout << "Contact copy constructor Deep Copy\n";
    address = new Address(
      other.getAddress()->getStreet(),
      other.getAddress()->getCity(),
      other.getAddress()->getSuite()
    );
  }

  ~Contact()
  {
    std::cout << "~Contact\n";
    if(is_deep_copy)
      delete address;
    address = nullptr;
  }

  std::string getName() const
  {
    return name;
  }

  void setName(const std::string& name) {
    this->name = name;
  }

  Address *getAddress() const
  {
    return address;
  }
};

class EmployeeFactory
{
public:
  static Contact main;
  static Contact aux;

  static std::unique_ptr<Contact> NewMainOfficeEmployee(std::string name, int suite)
  {
    return NewEmployee(name, suite, main);
  }

  static std::unique_ptr<Contact> NewAuxOfficeEmployee(std::string name, int suite)
  {
    return NewEmployee(name, suite, aux);
  }

private:
  static std::unique_ptr<Contact> NewEmployee(std::string name, int suite, Contact& proto)
  {
    auto result = std::make_unique<Contact>(proto); // deep copy
    result->setName(name);
    result->getAddress()->setSuite(suite);
    return result;
  }
};

Contact EmployeeFactory::main{ "", new Address{ "111 East Dr", "London", 111 } };
Contact EmployeeFactory::aux{ "", new Address{ "222 East Dr", "London", 222 } };

int main()
{
  // this is tedious
  Contact john{ "John Doe", new Address{"1 East Dr", "London", 1} };
  Contact jane{ "Jane Doe", new Address{"2 East Dr", "London", 2} };

  std::cout << john << std::endl;
  std::cout << jane << std::endl;

  auto addr = new Address{ "3 East Dr", "London", 3 /* ? */ };

  std::cout << *addr << std::endl;

  Contact john1{ "John Doe", addr }; // shallow copy
  std::cout << john1 << std::endl;
  john1.getAddress()->setSuite(123);
  Contact jane1{ "Jane Doe", addr }; // shallow copy
  std::cout << jane1 << std::endl;
  jane1.getAddress()->setSuite(124);

  std::cout << john1 << std::endl;
  std::cout << jane1 << std::endl;

  Contact jane2{ jane }; // deep copy
  jane2.getAddress()->setSuite(555);

  std::cout << jane2 << std::endl;
  std::cout << jane << std::endl;

  // // whenever an address is needed, make a copy
  // /*Contact john{ "John Doe", new Address{*addr} };
  // john.address->suite = 123;

  // Contact jane{ "Jane Doe", new Address{*addr} };
  // jane.address->suite = 125;

  // cout << john << "\n" << jane << endl;*/

  // much better. let's list employees
  Contact employee{ "Unknown", new Address{"628 Happy St", "Joy", 1} };

  //// we can use this prototype to create john and jane
  Contact john11{ employee }; // deep copy
  john11.setName("John Doe");
  john11.getAddress()->setSuite(123);

  Contact jane11{ employee }; // deep copy
  jane11.setName("Jane Doe");
  jane11.getAddress()->setSuite(125);

  std::cout << john11 << "\n" << jane11 << "\n";

  auto john22 = EmployeeFactory::NewAuxOfficeEmployee("John Doe", 223);
  auto jane22 = EmployeeFactory::NewMainOfficeEmployee("Jane Doe", 225);

  std::cout << *john22 << "\n" << *jane22 << "\n"; // note the stars here

  delete addr;

  return 0;
}