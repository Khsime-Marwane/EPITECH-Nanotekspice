//
// Clock.cpp for Clock in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/src/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 10:36:45 2017 Marwane Khsime
// Last update Thu Feb  2 04:19:35 2017 Marwane
//

#include "Clock.hpp"

// TODO: A changer en std::string si on veut pas se faire chier à convertir
Clock::Clock(const std::string &name, int _value) : AComponent(name, "clock") {
  this->pins = new Pin;
  this->pins[0].component = NULL;
  this->pins[0].state = (nts::Tristate)_value;
  this->pins[0].type = IGNORED;
}

Clock::~Clock() {}

nts::Tristate Clock::Compute(size_t pin_num_this) {
  if (pin_num_this != 1)
    throw Error("ERROR : [ " + this->_name + " | COMPUTE] : Invalid pin selected.");
  return this->pins[0].state;
}

void Clock::Dump() const {
  std::cout << this->_name << "=" << this->pins[0].state << std::endl;
}

void Clock::SetLink(size_t pin_num_this,
                    nts::IComponent &component,
                    size_t pin_num_target) {
  if (pin_num_this != 1) {
  throw Error("ERROR : [ " + this->_name + " | LINK] : Invalid pin selected ("
                + std::to_string((int)pin_num_target) + ").");
  }
  if (!this->pins[0].component) {
    // Link the chipset with the component.
    this->pins[0].component = dynamic_cast<AComponent * >(&component);
    // Link the component with the chipset.
    this->pins[0].component->SetLink(pin_num_target, *this, pin_num_this);
  };
}