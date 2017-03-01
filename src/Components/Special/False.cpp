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

False::False(const std::string &name) : AComponent(name, "false") {
  this->_nbPins = 1;
  this->pins = new Pin;
  this->pins[0].component = NULL;
  this->pins[0].state = nts::Tristate::FALSE;
  this->pins[0].type = IGNORED;
  this->links[0].first = -1;
  this->links[0].second = -1;
}

False::~False() {}

nts::Tristate False::Compute(size_t pin_num_this) {
  if (pin_num_this != 1) {
    throw Error("ERROR : [ " + this->_name + " | COMPUTE] : Invalid pin selected.");
  }
  return this->pins[0].state;
}

void False::SetLink(size_t pin_num_this, nts::IComponent &component,
                     size_t pin_num_target) {
  if (pin_num_this != 1) {
    throw Error("ERROR : [ " + this->_name + " | LINK] : Invalid pin selected ("
                  + std::to_string((int)pin_num_target) + ").");
  }
  if (!this->pins[0].component) {
    // Save the Link's indexes.
    this->links[0].first = pin_num_this;
    this->links[0].second = pin_num_target;
    // Link the chipset with the component.
    this->pins[0].component = dynamic_cast<AComponent *>(&component);
    // Link the component with the chipset.
    this->pins[0].component->SetLink(pin_num_target, *this, pin_num_this);
  }
}