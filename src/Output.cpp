//
// Output.cpp for Output in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/src/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 10:36:45 2017 Marwane Khsime
// Last update Thu Feb  2 04:19:35 2017 Marwane
//

#include "Output.hpp"

Output::Output(const std::string &name) : AComponent(name, "output") {
  this->_value = nts::Tristate::UNDEFINED;
  this->pins[0] = NULL;
  this->links.first = 0;
  this->links.second = 0;
}

Output::~Output() {}

nts::Tristate Output::Compute(size_t pin_num_this) {
  if (pin_num_this != 1) {
      throw Error("ERROR : [OUTPUT COMPONENT | COMPUTING] : pin does not exist.\n");
    }
  return this->_value;
}

void Output::Dump() const {
  std::cout << "[Output] | Value : " << this->_value << std::endl;
}

void  Output::SetTristate(nts::Tristate _value) {
  this->_value = _value;
}

void Output::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target) {
  if (pin_num_this != 1) {
      throw Error("ERROR : [OUTPUT COMPONENT | LINK] : pin does not exist.\n");
    }

  this->links.first = pin_num_this;
  this->links.second = pin_num_target;
  this->pins[0] = &component;
}