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

#include "C4081.hpp"

/*
** The component 4081 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4081::C4081(const std::string &name) : AComponent(name, "chipset") {
  pins = new Pin[14];

  // Create the pins of the chipset 4081 and set them.
  for (unsigned int i = 0; i < 14; i++) {
      this->pins[i].state = nts::UNDEFINED;
      this->pins[i].component = NULL;
      this->links[i] = std::make_pair(0, 0);
    }

  // Output pins with their inputs index.
  this->gateLinks[3] = std::make_pair(1, 2);
  this->gateLinks[4] = std::make_pair(5, 6);
  this->gateLinks[10] = std::make_pair(8, 9);
  this->gateLinks[11] = std::make_pair(12, 13);
}

/*
** Check if the pin selected exist in the component,
** indexes allowed there are [1, 14].
*/
bool            C4081::pinIndexIsValid(size_t pin_num_this) {
  return pin_num_this > 0 && pin_num_this < 15;
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4081::Compute(size_t pin_num_this) {

  if (pinIndexIsValid(pin_num_this))
    {
      // If the pin selected is an Output.
      if (this->gateLinks.find(pin_num_this) != this->gateLinks.end()) {

          // Get the indexes of the pins linked with the output.
          size_t  firstPinLinked = this->gateLinks[pin_num_this].first;
          size_t  secondPinLinked = this->gateLinks[pin_num_this].second;

          // Compute the inputsx
          nts::Tristate v1 = Compute(firstPinLinked);
          nts::Tristate v2 = Compute(secondPinLinked);

          // Call the door Or with v1 and v2 as parameters.
          this->pins[pin_num_this - 1].state = this->gate.compute("AND", v1, v2);
          if (this->pins[pin_num_this - 1].component)
            this->pins[pin_num_this - 1].component->setValue(this->pins[pin_num_this - 1].state);
        }

      // If the pin selected is an Input.
      else if (this->pins[pin_num_this - 1].component) {
        this->pins[pin_num_this - 1].state =
          this->pins[pin_num_this - 1].component->Compute(this->links[pin_num_this - 1].second);
      }
      
      // Return the value of the computed Pin.
      return (this->pins[pin_num_this - 1].state);
    }

  // If the pin doesn't exist, throw an error.
  throw Error("C4081 - Compute : Invalid pin selected.\n");
  return nts::Tristate::UNDEFINED;
}   

/*
** Compute all gates (outputs) of the chipset, if it can be computed.
*/
void            C4081::computeGates() {
  int           outputPins[] = { 3, 4, 10, 11 };

  for (unsigned int i = 0; i < 4; i++) {
    if (this->pins[this->gateLinks[outputPins[i]].first - 1].component &&
        this->pins[this->gateLinks[outputPins[i]].second - 1].component) {

      // Compute the inputs
      nts::Tristate v1 = Compute(this->gateLinks[outputPins[i]].first);
      nts::Tristate v2 = Compute(this->gateLinks[outputPins[i]].second);

      // Call the door OR with v1 and v2 as parameters.
      this->pins[outputPins[i] - 1].state = this->gate.compute("OR", v1, v2);
    }
  }
}

/*
** Link a pin of the chipset with a component. When it's possible,
** also link on the other side the pin [pin_num_target] with this chipset.
*/
void    C4081::SetLink(size_t pin_num_this,
                       nts::IComponent &component,
                       size_t pin_num_target) {

  if (!pinIndexIsValid(pin_num_this))
    throw Error("ERROR : [C4081 COMPONENT | LINK] : pin does not exist.\n");

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

/*
** Display all the states of each pin of the chipset. If a pin is not linked,
** it display 'NULL'.
*/
void    C4081::Dump() const {
  std::cout << "[CHIPSET 4081] :" << std::endl;

  for (unsigned int i = 0; i < 14; i++) {
      std::cout << "Pin [" << i + 1 << "] : ";
      if (this->pins[i].component)
        std::cout << (int)this->pins[i].state << std::endl;
      else std::cout << "NULL" << std::endl;
    }
}