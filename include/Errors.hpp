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
  Error(const std::string &_message, int _level) throw()
      : message(_message), level(_level) {}
  /// Destructor
  virtual ~Error() throw() {}

public:
  /// Get the description of the error
  const char *what() const throw() { return this->message.c_str(); }

  /// Get the level of the error
  int getErrorLevel() const throw() { return this->level; }

private:
  /// Description of the error
  std::string message;
  /// Level of the error
  int level;
};

class badExtensionFile : public Error
{
 public:
  badExtensionFile(const std::string &_message, int _level) : Error(_message, _level){}
  virtual ~badExtensionFile() throw(){}
};

#endif /* end of include guard: _ERRORS_HPP_ */
