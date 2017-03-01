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

#define STROBE 0
#define DATA 1
#define CLOCK 2
#define OUTPUT_ENABLE 14
#define SERIAL_ONE 8
#define SERIAL_TWO 9
#define Q7 11

/*
** The component 4094 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4094::C4094(const std::string &name) : AComponent(name, "chipset") {
  this->pins = new Pin[16];

  PinType pinsTypeTab[16] = {
    INPUT,    // Pin 1
    INPUT,    // Pin 2
    INPUT,    // Pin 3
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
  for (unsigned int i = 0; i < 16; i++) {
      this->pins[i].state = nts::UNDEFINED;
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

  this->oldClock = nts::Tristate::UNDEFINED;
  reset();
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
  size_t inputs[4] = { STROBE, DATA, CLOCK, OUTPUT_ENABLE };

  // Check it's the first simulation. The clock must change his state.
  if (oldClock == nts::Tristate::UNDEFINED) {
    oldClock = this->pins[CLOCK].state;
    return ;
  }

  // Compute the inputs to get the new values
  for (size_t i = 0; i < 4; i++) {
    if (this->pins[inputs[i]].component)
      this->pins[inputs[i]].state = this->pins[inputs[i]].component->Compute(this->links[inputs[i]].second);
  }

  // If OutputEnable (pin 15) is not set to true, we reset the chipset
  if (this->pins[OUTPUT_ENABLE].state != nts::Tristate::TRUE) {
    reset();
  }

  // If the Strobe is set to true, and Data equal TRUE or FALSE
  else if (this->pins[STROBE].state == nts::Tristate::TRUE &&
          this->pins[DATA].state != nts::Tristate::UNDEFINED) {

    // If the Clock (pin 3) is set to true, we can shift.
    if (this->pins[CLOCK].state == nts::Tristate::TRUE) {

      // Cascade the outputs
      for (int i = 7; i > -1; i--) {

        if (i == 0) {// The first output get the value of the data.
          this->pins[this->outputPins[i] - 1].state = this->pins[DATA].state;
        }

        else // Else, cascade the outputs.
          this->pins[this->outputPins[i] - 1].state = this->pins[this->outputPins[i - 1] - 1].state;
        }
      }
      
    // Set the serial outputs. If the CLOCK value is true, SERIAL ONE is set with pin 12 (Q7), else it's SERIAL TWO.
    this->pins[this->pins[CLOCK].state == nts::Tristate::TRUE ? SERIAL_ONE : SERIAL_TWO].state = this->pins[Q7].state;
  }
}

/*
** Check if the pin selected exist in the component,
** indexes allowed there are [1, 16].
*/
bool            C4094::pinIndexIsValid(size_t pin_num_this) {
  if (pin_num_this == 8 || pin_num_this == 16)
    return 0;
  return pin_num_this > 0 && pin_num_this < 17;
}

/*
** Check if the component type match with the type expected by the pin.
*/
bool            C4094::doesComponentTypeMatch(AComponent &component,
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
bool            C4094::doesPinsTypesMatch(size_t pin_num_this, size_t pin_num_target) {
  return this->pins[pin_num_this - 1].type == INPUT && this->pins[pin_num_target - 1].type == OUTPUT;
}

/*
** Link a pin of the chipset with a component. When it's possible,
** also link on the other side the pin [pin_num_target] with this chipset.
*/
void    C4094::SetLink(size_t pin_num_this,
                       nts::IComponent &component,
                       size_t pin_num_target) {

  // Check if the index (pin_num_this) is valid.
  if (!pinIndexIsValid(pin_num_this))
    throw Error("[ C4094 " + this->_name + " | LINK] : Invalid pin selected ("
                  + std::to_string((int)pin_num_target) + ").");

  // If we are linking pins in the same component.
  if (this == &component) {
    if (!doesPinsTypesMatch(pin_num_this, pin_num_target))
      throw Error("[ C4094 " + this->_name + " | LINK] : Impossible to link the pin "
                  + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                  + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
  }
  
  // Check if the component type match with the type expected by the pin.
  else {
    if (!doesComponentTypeMatch(*dynamic_cast<AComponent *>(&component), pin_num_this, pin_num_target))
      throw Error("[ C4094 " + this->_name + " | LINK] : Component type expected by the pin "
                  + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                  + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
    if (pin_num_this == (CLOCK + 1) && (*dynamic_cast<AComponent *>(&component)).getType() != "clock") {
      throw Error("[ C4094 " + this->_name + " | LINK] : The type of the component linked with the pin 3 must be a clock.");
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
void    C4094::Dump() const {

std::cout << _name << std::endl;
  for (unsigned int i = 0; i < 16; i++) {
      std::cout << this->_name << "[" << i + 1 << "] = ";
      if (this->pins[i].component)
        std::cout << (int)this->pins[i].state << std::endl;
      else std::cout << "NULL" << std::endl;
    }
}