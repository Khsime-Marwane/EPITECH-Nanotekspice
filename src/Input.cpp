//
// Input.cpp for Input in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/src/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 10:36:45 2017 Marwane Khsime
// Last update Thu Feb  2 04:19:35 2017 Marwane
//

#include "Input.hpp"

// TODO: A changer en std::string si on veut pas se faire chier à convertir
Input::Input(const std::string &name, int _value) : AComponent(name, "input") {
  this->pins = new Pin;
  this->pins[0].component = NULL;
  this->pins[0].state = (nts::Tristate)_value;
}

Input::~Input() {}

nts::Tristate Input::Compute(size_t pin_num_this) {
  if (pin_num_this != 1) {
      throw Error("ERROR : [INPUT COMPONENT | COMPUTING] : pin does not exist.\n");
    }
  return this->pins[0].state;
}

void Input::Dump() const {
  std::cout << "[INPUT COMPONENT] | Value : " << this->pins[0].state << std::endl;
}

void Input::SetLink(size_t pin_num_this,
                    nts::IComponent &component,
                    size_t pin_num_target) {
  if (pin_num_this != 1) {
      throw Error("ERROR : [INPUT COMPONENT | LINK] : pin does not exist.\n");
    }
  if (!this->pins[0].component) {
    // Link the chipset with the component.
    this->pins[0].component = dynamic_cast<AComponent * >(&component);
    // Link the component with the chipset.
    this->pins[0].component->SetLink(pin_num_target, *this, pin_num_this);
  };
}