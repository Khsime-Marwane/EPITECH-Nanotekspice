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

# define _RESET_ 14
# define _CLOCK_ 13
# define _ENABLE_ 12
# define _CARRY_ 11
# define _FIRSTPIN_ 2

/*
** The component 4017 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4017::C4017(const std::string &name) : AComponent(name, "chipset") {
  this->_nbPins = 16;
  this->_VSS = 8;
  this->_VDD = 16;

  this->pins = new Pin[this->_nbPins];

  PinType pinsTypeTab[this->_nbPins] = {
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
    OUTPUT,   // Pin 12 
    INPUT,    // Pin 13
    CLOCK,    // Pin 14
    INPUT,    // Pin 15
    IGNORED   // Pin 16 (VDD)
  };

  // Create the pins of the chipset 4017 and set them.
  for (unsigned int i = 0; i < this->_nbPins; i++) {
      this->pins[i].state = nts::Tristate::FALSE;
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
  this->pins[_FIRSTPIN_].state = nts::Tristate::TRUE;
  this->pins[_CARRY_].state = nts::Tristate::TRUE;
  this->current = 0;
}

/*
** Compute all gates (outputs) of the chipset, if it can be computed.
*/
void            C4017::computeGates() {

  if (this->pins[_CLOCK_].component)
    this->pins[_CLOCK_].state = this->pins[_CLOCK_].component->Compute(this->links[_CLOCK_].second);

  if (this->pins[_RESET_].component)
    this->pins[_RESET_].state = this->pins[_RESET_].component->Compute(this->links[_RESET_].second);

  if (this->pins[_ENABLE_].component)
    this->pins[_ENABLE_].state = this->pins[_ENABLE_].component->Compute(this->links[_ENABLE_].second);
  // If the reset pin is TRUE, we reset the chipset
  if (this->pins[_RESET_].state == nts::Tristate::TRUE) {
    reset();
  }

  // If the Clock Inhibit is set to true, we can decade the counter.
  else if (this->pins[_ENABLE_].state != nts::Tristate::TRUE) {
    // If the Clock (pin 14) is set to true, we can increment.
    if (this->pins[_CLOCK_].state == nts::Tristate::TRUE) {
      if (this->current == 9) {
        reset();
      }
      else {
        this->pins[this->order[current] - 1].state = nts::Tristate::FALSE;
        this->current++;
        this->pins[this->order[current] - 1].state = nts::Tristate::TRUE;
        if (this->current >= 5)
          this->pins[_CARRY_].state = nts::Tristate::FALSE;
      }
    }
  }
}