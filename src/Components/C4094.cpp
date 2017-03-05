//
// Chipset4094.cpp for 4094 in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/Chipsets/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 02:16:32 2017 Marwane Khsime
// Last update Thu Feb  2 04:19:53 2017 Marwane
//

#include "C4094.hpp"

#define _STROBE_ 0
#define _DATA_ 1
#define _CLOCK_ 2
#define _OUTPUT_ENABLE_ 14
#define _QPRIME_ 8
#define _QS_ 9
#define _Q7_ 11

/*
** The component 4094 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4094::C4094(const std::string &name) : AComponent(name, "chipset") {
  this->_nbPins = 16;
  this->_VSS = 8;
  this->_VDD = 16;

  this->pins = new Pin[this->_nbPins];

  PinType pinsTypeTab[this->_nbPins] = {
    INPUT,    // Pin 1
    INPUT,    // Pin 2
    CLOCK,    // Pin 3
    OUTPUT,   // Pin 4
    OUTPUT,   // Pin 5
    OUTPUT,   // Pin 6
    OUTPUT,   // Pin 7
    IGNORED,  // Pin 8  (VSS)
    OUTPUT,   // Pin 9
    OUTPUT,   // Pin 10
    OUTPUT,   // Pin 11
    OUTPUT,   // Pin 12 
    OUTPUT,   // Pin 13
    OUTPUT,   // Pin 14
    INPUT,    // Pin 15
    IGNORED   // Pin 16 (VDD)
  };

  // Create the pins of the chipset 4094 and set them.
  for (unsigned int i = 0; i < this->_nbPins; i++) {
      this->pins[i].state = nts::Tristate::FALSE;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
  }
  
  // Pin index with the decimal value associated.
  this->outputPins[0] = 4;
  this->outputPins[1] = 5;
  this->outputPins[2] = 6;
  this->outputPins[3] = 7;
  this->outputPins[4] = 14;
  this->outputPins[5] = 13;
  this->outputPins[6] = 12;
  this->outputPins[7] = 11;

  for (size_t i = 0; i < 8; i++) {
    this->pins[this->outputPins[i] - 1].state = nts::Tristate::UNDEFINED;
  }

  this->pins[_QPRIME_].state = nts::Tristate::UNDEFINED;
  this->pins[_QS_].state = nts::Tristate::UNDEFINED;
  this->first = true;
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4094::Compute(size_t pin_num_this) {

  // If the pin selected is valid.
  if (pinIndexIsValid(pin_num_this))
      return (this->pins[pin_num_this - 1].state);

  // If the pin doesn't exist, or if it's a VSS / VDD, throw an error.
  throw Error("ERROR : [ " + this->_name + " | COMPUTE] : Invalid pin selected.");
  return nts::Tristate::UNDEFINED;
}

void            C4094::reset() {
  // Set all outputs pins to false.
  for (std::map<size_t, size_t>::iterator it = outputPins.begin(); it != outputPins.end(); it++) {
    this->pins[(*it).second - 1].state = nts::Tristate::UNDEFINED;
  }
}

/*
** Compute all gates (outputs) of the chipset, if it can be computed.
*/
void            C4094::computeGates() {
  size_t inputs[4] = { _STROBE_, _DATA_, _CLOCK_, _OUTPUT_ENABLE_ };

  if (this->first) { this->first = false; return; }
  // Compute the inputs to get the new values
  for (size_t i = 0; i < 4; i++) {
    if (this->pins[inputs[i]].component)
      this->pins[inputs[i]].state = this->pins[inputs[i]].component->Compute(this->links[inputs[i]].second);
  }

  // IF OE is FALSE
  if (this->pins[_OUTPUT_ENABLE_].state == nts::Tristate::FALSE &&
      (this->pins[_CLOCK_].state == nts::Tristate::TRUE ||
      this->pins[_CLOCK_].state == nts::Tristate::FALSE)) {

    // IF CLOCK IS TRUE
    if (this->pins[_CLOCK_].state == nts::Tristate::TRUE)
      this->pins[_QS_].state = this->pins[_Q7_].state;
    else // IF CLOCK IS FALSE
      this->pins[_QPRIME_].state = this->pins[_Q7_].state;

    reset();
    return ;
  }

  // If the Strobe is FALSE, OUTPUT_ENABLE TRUE and CLOCK TRUE
  else if (this->pins[_STROBE_].state == nts::Tristate::FALSE &&
           this->pins[_OUTPUT_ENABLE_].state == nts::Tristate::TRUE &&
           this->pins[_CLOCK_].state == nts::Tristate::TRUE) {
      this->pins[_QS_].state = this->pins[_Q7_].state;
    return ;
  }

  // If the STROBE is set to TRUE and DATA == TRUE || FALSE
  else if (this->pins[_STROBE_].state == nts::Tristate::TRUE &&
           (this->pins[_DATA_].state == nts::Tristate::TRUE ||
            this->pins[_DATA_].state == nts::Tristate::FALSE) &&
            this->pins[_CLOCK_].state == nts::Tristate::TRUE) {

      // Cascade the outputs
      for (int i = 7; i > -1; i--) {
        if (i == 0) // The first output get the value of the _DATA_.
          this->pins[this->outputPins[i] - 1].state = this->pins[_DATA_].state;
        else // Else, cascade the outputs.
          this->pins[this->outputPins[i] - 1].state = this->pins[this->outputPins[i - 1] - 1].state;
      }
      this->pins[_QS_].state = this->pins[_Q7_].state;
  }

  else if (this->pins[_OUTPUT_ENABLE_].state == nts::Tristate::TRUE &&
           this->pins[_STROBE_].state == nts::Tristate::TRUE &&
           this->pins[_DATA_].state == nts::Tristate::TRUE) {
    this->pins[_QPRIME_].state = this->pins[_Q7_].state;
  }
}