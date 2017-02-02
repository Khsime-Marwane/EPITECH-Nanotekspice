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

Output() {}

~Output() {}

nts::Tristate Output::Compute(size_t pin_num_this) {
  (void)pin_num_this;
  return this->value;
}

nts::Tristate Output::getValue() const { return this->value; }

void Output::Dump() const {}

void Output::SetLink(size_t pin_num_this, nts::IComponent &component,
                     size_t pin_num_this) {
  (void)pin_num_this;
  (void)pin_num_target;
  (void)component;
}
