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
Input::Input() {
  this->value = nts::Tristate::UNDEFINED;
  this->pins[0] = NULL;
  this->links.first = 0;
  this->links.second = 0;
}

Input::~Input() {}

nts::Tristate Input::Compute(size_t pin_num_this) {
  if (pin_num_this != 1) {
    throw Error("ERROR : [INPUT COMPONENT | COMPUTING] : pin does not exist.\n");
  }
  if (this->getValue() == nts::Tristate::UNDEFINED)
    throw Error("ERROR : [INPUT COMPONENT | COMPUTING] : Undefined value used.\n");
  return this->value;
}

nts::Tristate Input::getValue() const { return this->value; }

void Input::Dump() const {
    std::cout << "[INPUT COMPONENT] | Value : " << this->value << std::endl;
}

void Input::SetLink(size_t pin_num_this, nts::IComponent &component,
                     size_t pin_num_target) {
  if (pin_num_this != 1) {
    throw Error("ERROR : [INPUT COMPONENT | LINK] : pin does not exist.\n");
  }
  this->links.first = pin_num_this;
  this->links.second = pin_num_target;
  this->pins[0] = &component;
  // try {
  //   this->pins[0]->SetLink(this->links.second, *this, this->links.first);
  // } catch (const std::exception& err) {
  //   throw err;
  // }
}