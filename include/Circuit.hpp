#ifndef _CIRCUIT_HPP_
#define _CIRCUIT_HPP_

#include <vector>
#include <iostream>
#include "Component.hpp"

class   Circuit
{
  int                     _id;
  std::vector<Component>  _comps;

 public:
  Circuit(int);
  ~Circuit();

  void    addComponent(Component);
  void    delComponent(std::string, std::string);

  int     getId();
};

#endif  /* _CIRCUIT_HPP_ */