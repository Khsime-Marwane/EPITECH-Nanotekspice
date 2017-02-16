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

  for (unsigned int i = 0; i < 14; i++) {
      this->pins[i] = new Pin();
      this->pins[i]->state = nts::UNDEFINED;
      this->pins[i]->component = NULL;
    }

  for (unsigned int i = 0; i < 14; i++)
    this->links[i] = std::make_pair(0, 0);

  this->links[2] = std::make_pair(0, 1);
  this->links[3] = std::make_pair(4, 5);
  this->links[9] = std::make_pair(7, 8);
  this->links[10] = std::make_pair(11, 12);

//    this->outputLinks[0] = std::
  this->outputLinks[1] = std::make_pair(1, 2);
  this->outputLinks[2] = std::make_pair(5, 6);
  this->outputLinks[3] = std::make_pair(8, 9);
  this->outputLinks[4] = std::make_pair(12, 13);

  this->gate = Gate();
}

bool            C4071::pinIndexIsValid(size_t pin_num_this) {
  return pin_num_this > 0 && pin_num_this < 15;
}

nts::Tristate   C4071::Compute(size_t pin_num_this) {
  if (pinIndexIsValid(pin_num_this - 1))
    {
      std::cout << "OK : " << pin_num_this - 1 << " | \n";
      if (links[pin_num_this - 1].first > 0 ||  links[pin_num_this - 1].second > 0)
        {
          this->pins[pin_num_this - 1]->state = this->gate.compute("OR", pins[links[pin_num_this - 1].first]->component, pins[links[pin_num_this - 1].second]->component);
          std::cout << "value state : " << this->pins[pin_num_this - 1]->state << std::endl;
        }
      else if (this->pins[pin_num_this - 1]->component)
          this->pins[pin_num_this - 1]->state = this->pins[pin_num_this - 1]->component->getValue();

      this->pins[pin_num_this - 2]->state = this->Compute(pin_num_this - 1);
    }
  return (this->pins[pin_num_this - 1]->state);
}

void            C4071::computeAllGates() {
  for (unsigned int i = 1; i < 5; i++) {
      this->pins[i]->state = this->gate.compute("OR",
                                                this->pins[this->outputLinks[i].first]->component,
                                                this->pins[this->outputLinks[i].second]->component);
      this->pins[i]->component->setTristate(this->pins[i]->state);
    }
}

void            C4071::computeGate(size_t gate) {
  this->pins[gate]->state = this->gate.compute("OR",
                                               this->pins[this->outputLinks[gate].first]->component,
                                               this->pins[this->outputLinks[gate].second]->component);
  this->pins[gate]->component->setTristate(this->pins[gate]->state);
}

// void    C4071::SetTristate(size_t pin_num_this, nts::Tristate _value) {
//     if (pinIndexIsValid(pin_num_this))
//         this->pins[pin_num_this - 1]->SetTristate(1, _value);
// }

void    C4071::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target) {
  if (!pinIndexIsValid(pin_num_this))
    throw Error("ERROR : [C4071 COMPONENT | LINK] : pin does not exist.\n");

  component.SetLink(pin_num_this, component, pin_num_target);
  this->pins[pin_num_target - 1]->component = dynamic_cast<AComponent *>(&component);
}

void    C4071::Dump() const {
  std::cout << "[CHIPSET 4071] :" << std::endl;

  for (unsigned int i = 0; i < 14; i++) {
      std::cout << "Pin [" << i + 1 << "] : ";
      if (this->pins[i] && this->pins[i]->component)
        std::cout << (int)this->pins[i]->component->Compute(1) << std::endl;
      else std::cout << "NULL" << std::endl;
    }
}