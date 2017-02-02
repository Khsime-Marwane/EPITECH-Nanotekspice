#include <iostream>
#include "Component.hh"

Component::Component(std::string name, std::string type)
{
  this->_name = name;
  this->_type = type;
  this->_value = nts::UNDEFINED;
}

Component::~Component(){}

std::string   Component::getName() const
{
  return (this->_name);
}

std::string   Component::getType() const
{
  return (this->_type);
}

nts::Tristate  Component::getValue() const
{
  return (this->_value);
}

void    Component::setValue(const nts::Tristate & new_value)
{
  this->_value = new_value;
}
