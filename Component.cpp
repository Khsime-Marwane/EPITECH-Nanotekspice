#include "Component.hh"

Component::Component(std::string name)
{
  this->_name = name;
  this->_value = UNDEFINED;
}

Component::~Component(){}

std::string   Component::getName() const
{
  return (this->_name);
}

Component::state  Component::getValue() const
{
  return (this->_value);
}

void    Component::setValue(const state & new_value)
{
  this->_value = new_value;
}

void    Component::setName(const std::string & name)
{
  this->_name = name;
}
