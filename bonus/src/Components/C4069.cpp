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

#include "C4069.hpp"

/*
** The component 4069 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4069::C4069(const std::string &name) : AComponent(name, "chipset") {
  this->_nbPins = 14;
  this->_VSS = 7;
  this->_VDD = 14;

  this->pins = new Pin[this->_nbPins];

  PinType pinsTypeTab[this->_nbPins] = {
    INPUT,    // Pin 1
    OUTPUT,   // Pin 2
    INPUT,    // Pin 3
    OUTPUT,   // Pin 4
    INPUT,    // Pin 5
    OUTPUT,   // Pin 6
    IGNORED,  // Pin 7  (VSS)
    OUTPUT,   // Pin 8
    INPUT,    // Pin 9
    OUTPUT,   // Pin 10
    INPUT,    // Pin 11
    OUTPUT,   // Pin 12
    INPUT,    // Pin 13
    IGNORED   // Pin 14 (VDD)
  };

  // Create the pins of the chipset 4069 and set them.
  for (unsigned int i = 0; i < this->_nbPins; i++) {
      this->pins[i].state = nts::Tristate::FALSE;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
    }

  // Output pins with their inputs index.
  this->gateLinks[2] = std::make_pair(1, -1);
  this->gateLinks[4] = std::make_pair(3, -1);
  this->gateLinks[6] = std::make_pair(5, -1);
  this->gateLinks[8] = std::make_pair(9, -1);
  this->gateLinks[10] = std::make_pair(11, -1);
  this->gateLinks[12] = std::make_pair(13, -1);
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4069::Compute(size_t pin_num_this) {

  if (pinIndexIsValid(pin_num_this))
    {
      // If the pin selected is an Output.
      if (this->gateLinks.find(pin_num_this) != this->gateLinks.end()) {

          size_t  firstPinLinked = this->gateLinks[pin_num_this].first;

          // Compute the inputs
          nts::Tristate v1 = Compute(firstPinLinked);

          // Call the door NOT with v1 and v2 as parameters.
          this->pins[pin_num_this - 1].state = this->gate.compute("NOT", v1);
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
  throw Error("ERROR : [ " + this->_name + " | COMPUTE] : Invalid pin selected.");
  return nts::Tristate::UNDEFINED;
}

/*
** Compute all gates (outputs) of the chipset, if it can be computed.
*/
void            C4069::computeGates() {
  size_t        outputPins[] = { 2, 4, 6, 8, 10, 12};

  for (size_t i = 0; i < 6; i++) {
    Compute(outputPins[i]);
  }
}