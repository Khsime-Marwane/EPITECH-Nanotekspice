#include <iostream>
#include "Component.hh"

Component::Component(std::string name, std::string type)
{
  this->_name = name;
  this->_type = type;
  this->_value = UNDEFINED;
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

Component::state  Component::getValue() const
{
  return (this->_value);
}

void    Component::setValue(const state & new_value)
{
  this->_value = new_value;
}
