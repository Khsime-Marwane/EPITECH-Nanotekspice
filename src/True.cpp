//
// False.cpp for False in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/src/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 10:36:45 2017 Marwane Khsime
// Last update Thu Feb  2 04:19:35 2017 Marwane
//

#include "False.hpp"

False::False() {
  this->value = nts::Tristate::FALSE;
  this->pins[0] = NULL;
  this->links.first = 0;
  this->links.second = 0;
}

False::~False() {}

nts::Tristate False::Compute(size_t pin_num_this) {
  if (pin_num_this != 1) {
    throw Error("ERROR : [FALSE COMPONENT | COMPUTING] : pin does not exist.\n");
  }
  throw Error("ERROR : [FALSE COMPONENT | COMPUTING] : impossible to compute a False component.\n");
  return nts::Tristate::UNDEFINED;
}

nts::Tristate False::getValue() const { return this->value; }

void False::Dump() const {
    std::cout << "[FALSE COMPONENT] | Value : " << this->value << std::endl;
}

void False::SetLink(size_t pin_num_this, nts::IComponent &component,
                     size_t pin_num_target) {
  if (pin_num_this != 1) {
    throw Error("ERROR : [FALSE COMPONENT | LINK] : pin does not exist.\n");
  }
  this->links.first = pin_num_this;
  this->links.second = pin_num_target;
  this->pins[0] = &component;
  try {
    this->pins[0]->SetLink(this->links.second, *this, this->links.first);
  } catch (const std::exception& err) {
    throw err;
  }
}
