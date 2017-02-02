#ifndef CIRCUIT_H_
#define CIRCUIT_H_

#include <vector>
#include <iostream>
#include "Component.hh"

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

#endif