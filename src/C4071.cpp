//
// Chipset4001.cpp for 4001 in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/Chipsets/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 02:16:32 2017 Marwane Khsime
// Last update Thu Feb  2 04:19:53 2017 Marwane
//

#include "C4071.hpp"

C4071::C4071(const std::string &name) : AComponent(name, "chipset") {
  pins = new Pin[14];

  for (unsigned int i = 0; i < 14; i++) {
      // this->pins[i] = new Pin();
      this->pins[i].state = nts::UNDEFINED;
      this->pins[i].component = NULL;
      this->links[i] = std::make_pair(1, 1);
    }

  // Output pins with their inputs index.
  this->links[3] = std::make_pair(1, 2);
  this->links[4] = std::make_pair(5, 6);
  this->links[10] = std::make_pair(8, 9);
  this->links[11] = std::make_pair(12, 13);
}

bool            C4071::pinIndexIsValid(size_t pin_num_this) {
  return pin_num_this > 0 && pin_num_this < 15;
}

nts::Tristate   C4071::Compute(size_t pin_num_this) {
  if (pinIndexIsValid(pin_num_this))
    {
      // If the pin selected is an Output.
      if (this->gateLinks.find(pin_num_this) != this->gateLinks.end()) {
        this->pins[pin_num_this - 1].state =
          this->gate.compute("OR",
                             pins[this->gateLinks[pin_num_this - 1].first].component,
                             pins[this->gateLinks[pin_num_this - 1].second].component);
      }
      // If the pin selected is an Input.
      else if (this->pins[pin_num_this - 1].component)
        this->pins[pin_num_this - 1].state = this->pins[pin_num_this - 1].component->Compute();
      return (this->pins[pin_num_this - 1].state);
    }
  throw Error("C4071 - Compute : Invalid pin selected.\n");
  return nts::Tristate::UNDEFINED;
}

void            C4071::computeGates() {
  int           outputPins[] = { 2, 3, 9, 10 };

  for (unsigned int i = 0; i < 4; i++) {
    if (this->pins[this->gateLinks[i].first].component &&
        this->pins[this->gateLinks[i].second].component) {
      this->pins[outputPins[i]].state = this->gate.compute("OR",
                                                this->pins[this->gateLinks[i].first].component,
                                                this->pins[this->gateLinks[i].second].component);
    }
  }
}

void    C4071::SetLink(size_t pin_num_this,
                       nts::IComponent &component,
                       size_t pin_num_target) {

  if (!pinIndexIsValid(pin_num_this))
    throw Error("ERROR : [C4071 COMPONENT | LINK] : pin does not exist.\n");

  if (!this->pins[pin_num_this - 1].component) {
    // Save the indexes
    this->links[pin_num_this - 1].first = pin_num_this;
    this->links[pin_num_this - 1].second = pin_num_target;
    // Link the chipset with the component.
    this->pins[pin_num_this - 1].component = dynamic_cast<AComponent * >(&component);
    // Link the component with the chipset.
    this->pins[pin_num_this - 1].component->SetLink(pin_num_target, *this, pin_num_this);
  };
}

void    C4071::Dump() const {
  std::cout << "[CHIPSET 4071] :" << std::endl;

  for (unsigned int i = 0; i < 14; i++) {
      std::cout << "Pin [" << i + 1 << "] : ";
      if (this->pins[i].component)
        std::cout << (int)this->pins[i].state << std::endl;
      else std::cout << "NULL" << std::endl;
    }
}

int main() {
  return 0;
}