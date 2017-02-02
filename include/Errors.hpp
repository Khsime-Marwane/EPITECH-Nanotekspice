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
  Error(int _errorID, const std::string &_message, int _level) throw()
      : errorID(_errorID), message(_message), level(_level) {}
  /// Destructor
  virtual ~Error() throw() {}

public:
  /// Get the description of the error
  virtual const char *what() const throw() { return this->message.c_str(); }

  /// Get the level of the error
  int getErrorLevel() const throw() { return this->level; }

private:
  /// ID of the error
  int errorID;
  /// Description of the error
  std::string message;
  /// Level of the error
  int level;
};

#endif /* end of include guard: _ERRORS_HPP_ */
