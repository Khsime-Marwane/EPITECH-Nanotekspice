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

#include "C4017.hpp"

/*
** The component 4017 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4017::C4017(const std::string &name) : AComponent(name, "chipset") {
  this->pins = new Pin[14];

  PinType pinsTypeTab[16] = {
    OUTPUT,   // Pin 1
    OUTPUT,   // Pin 2
    OUTPUT,   // Pin 3
    OUTPUT,   // Pin 4
    OUTPUT,   // Pin 5
    OUTPUT,   // Pin 6
    OUTPUT,   // Pin 7
    IGNORED,  // Pin 8  (VSS)
    OUTPUT,   // Pin 9
    OUTPUT,   // Pin 10
    OUTPUT,   // Pin 11
    OUTPUT,    // Pin 12 
    INPUT,    // Pin 13
    INPUT,    // Pin 14
    INPUT,    // Pin 15
    IGNORED   // Pin 16 (VDD)
  };

  // Create the pins of the chipset 4017 and set them.
  for (unsigned int i = 0; i < 16; i++) {
      this->pins[i].state = nts::UNDEFINED;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
    }
  
  // Pin index with the decimal value associated.
  this->order[0] = 3;
  this->order[1] = 2;
  this->order[2] = 4;
  this->order[3] = 7;
  this->order[4] = 10;
  this->order[5] = 1;
  this->order[6] = 5;
  this->order[7] = 6;
  this->order[8] = 9;
  this->order[9] = 11;
  this->current = 0;
  reset();
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4017::Compute(size_t pin_num_this) {

  // If the pin selected is valid.
  if (pinIndexIsValid(pin_num_this))
      return (this->pins[pin_num_this - 1].state);

  // If the pin doesn't exist, or if it's a VSS / VDD, throw an error.
  throw Error("ERROR : [ " + this->_name + " | COMPUTE] : Invalid pin selected.");
  return nts::Tristate::UNDEFINED;
}

void            C4017::reset() {
  // Set all outputs pins to false.
  for (std::map<size_t, size_t>::iterator it = order.begin(); it != order.end(); it++) {
    this->pins[(*it).second - 1].state = nts::Tristate::FALSE;
  }
  // Set the first pin (pin 3 with the value 0) and the carry.
  this->pins[3 - 1].state = nts::Tristate::TRUE;
  this->pins[12 - 1].state = nts::Tristate::TRUE;
  this->current = 0;
}

/*
** Compute all gates (outputs) of the chipset, if it can be computed.
*/
void            C4017::computeGates() {
  if (this->pins[14 - 1].component)
    this->pins[14 - 1].state = this->pins[14 - 1].component->Compute(this->links[14 - 1].second);

  // If the reset pin is TRUE, we reset the chipset
  if (this->pins[15 - 1].state == nts::Tristate::TRUE) {
    reset();
  }

  // If the Clock Inhibit is set to true, we can decade the counter.
  else if (this->pins[13 - 1].state != nts::Tristate::TRUE) {
    // If the Clock (pin 14) is set to true, we can increment.
    if (this->pins[14 - 1].state == nts::Tristate::TRUE) {
      if (this->current == 9) {
        reset();
      }
      else {
        this->pins[this->order[current] - 1].state = nts::Tristate::FALSE;
        this->current++;
        this->pins[this->order[current] - 1].state = nts::Tristate::TRUE;
      }
    }
  }
}

/*
** Check if the pin selected exist in the component,
** indexes allowed there are [1, 16].
*/
bool            C4017::pinIndexIsValid(size_t pin_num_this) {
  if (pin_num_this == 8 || pin_num_this == 16)
    return 0;
  return pin_num_this > 0 && pin_num_this < 17;
}

/*
** Check if the component type match with the type expected by the pin.
*/
bool            C4017::doesComponentTypeMatch(AComponent &component,
                                              size_t pin_num_this,
                                              size_t pin_num_target) {
  // If the pin is an output, the component fixed must be also an output.
  return this->pins[pin_num_this - 1].type == INPUT || component.pins[pin_num_target - 1].type != OUTPUT;
}

/*
** Check, when we are linking in the same component, if the pin used is an
** Input and if the target is an Output (in a chipset, we can only link an
** Output to an Input)
*/
bool            C4017::doesPinsTypesMatch(size_t pin_num_this, size_t pin_num_target) {
  return this->pins[pin_num_this - 1].type == INPUT && this->pins[pin_num_target - 1].type == OUTPUT;
}

/*
** Link a pin of the chipset with a component. When it's possible,
** also link on the other side the pin [pin_num_target] with this chipset.
*/
void    C4017::SetLink(size_t pin_num_this,
                       nts::IComponent &component,
                       size_t pin_num_target) {

  // Check if the index (pin_num_this) is valid.
  if (!pinIndexIsValid(pin_num_this))
    throw Error("[ C4017 " + this->_name + " | LINK] : Invalid pin selected ("
                  + std::to_string((int)pin_num_target) + ").");

  // If we are linking pins in the same component.
  if (this == &component) {
    if (!doesPinsTypesMatch(pin_num_this, pin_num_target))
      throw Error("[ C4017 " + this->_name + " | LINK] : Impossible to link the pin "
                  + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                  + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
  }
  
  // Check if the component type match with the type expected by the pin.
  else {
    if (!doesComponentTypeMatch(*dynamic_cast<AComponent *>(&component), pin_num_this, pin_num_target))
      throw Error("[ C4017 " + this->_name + " | LINK] : Component type expected by the pin "
                  + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                  + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
    if (pin_num_this == 14 && (*dynamic_cast<AComponent *>(&component)).getType() != "clock") {
      throw Error("[ C4017 " + this->_name + " | LINK] : The type of the component linked with the pin 14 must be a clock.");
    }
  }

  // If the pin already has a component, nothing to do.
  if (!this->pins[pin_num_this - 1].component) {

    // Save the indexes
    this->links[pin_num_this - 1].first = pin_num_this;
    this->links[pin_num_this - 1].second = pin_num_target;

    // Link the chipset with the component.
    this->pins[pin_num_this - 1].component = dynamic_cast<AComponent *>(&component);

    // Link the component with the chipset (do nothing if we are linking inside).
    if (this != &component) {
      this->pins[pin_num_this - 1].component->SetLink(pin_num_target, *this, pin_num_this);
    }

    if (this->pins[pin_num_this - 1].type == INPUT)
      this->pins[pin_num_this - 1].state = dynamic_cast<AComponent *>(&component)->pins[pin_num_target - 1].state;
  };
}

/*
** Display all the states of each pin of the chipset. If a pin is not linked,
** it display 'NULL'.
*/
void    C4017::Dump() const {

std::cout << _name << std::endl;
  for (unsigned int i = 0; i < 16; i++) {
      std::cout << this->_name << "[" << i + 1 << "] = ";
      if (this->pins[i].component)
        std::cout << (int)this->pins[i].state << std::endl;
      else std::cout << "NULL" << std::endl;
    }
}