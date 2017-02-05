//
// Errors.hh for Errors in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/Errors/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Tue Jan 31 20:33:33 2017 Marwane Khsime
// Last update Tue Jan 31 20:33:36 2017 Marwane Khsime
//

#ifndef _ERRORS_HPP_
#define _ERRORS_HPP_

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

void test_print();

class Error : public std::exception {
public:
  /// Constructor
  Error(const std::string &_message) throw()
      : message(_message) {}
  /// Destructor
  virtual ~Error() throw() {}

  /// Get the description of the error
  virtual const char *what() const throw() { return this->message.c_str(); }

private:
  /// Description of the error
  std::string message;
};

class badExtensionFile : public Error
{
 public:
  badExtensionFile(const std::string &_message) : Error(_message){}
  virtual ~badExtensionFile() throw(){}
};

class undefinedComponent : public Error
{
 public:
  undefinedComponent(const std::string &_message) : Error(_message){}
  virtual ~undefinedComponent() throw(){}
};

class unknownSection : public Error
{
 public:
  unknownSection(const std::string &_message) : Error(_message){}
  virtual ~unknownSection() throw(){}
};
#endif /* end of include guard: _ERRORS_HPP_ */
