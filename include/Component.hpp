#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

#include <iostream>
#include "IComponent.hpp"

class   Component {

  std::string   _name;
  std::string   _type;
  nts::Tristate _value;

 public:
  Component(std::string = "", std::string = "");
  ~Component();

  std::string   getName() const;
  std::string   getType() const;
  nts::Tristate getValue() const;

  void  setValue(const nts::Tristate &);
};

#endif /* _COMPONENT_HPP_ */