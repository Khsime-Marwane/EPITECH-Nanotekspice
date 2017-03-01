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

#include "C4008.hpp"

/*
** The component 4008 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4008::C4008(const std::string &name) : AComponent(name, "chipset") {
  this->_nbPins = 16;
  this->_VSS = 8;
  this->_VDD = 16;

  this->pins = new Pin[this->_nbPins];

  PinType pinsTypeTab[this->_nbPins] = {
          INPUT,    // Pin 1
          INPUT,    // Pin 2
          INPUT,    // Pin 3
          INPUT,    // Pin 4
          INPUT,    // Pin 5
          INPUT,    // Pin 6
          INPUT,    // Pin 7
          IGNORED,  // Pin 8 (VSS)
          INPUT,    // Pin 9
          OUTPUT,   // Pin 10
          OUTPUT,   // Pin 11
          OUTPUT,   // Pin 12
          OUTPUT,   // Pin 13
          OUTPUT,   // Pin 14
          INPUT,    // Pin 15
          IGNORED   // Pin 16 (VDD)
  };
  // Create the pins of the chipset 4008 and set them.
  for (unsigned int i = 0; i < this->_nbPins; i++) {
      this->pins[i].state = nts::UNDEFINED;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
    }

  // Output pins with their inputs index.
  this->gateLinks[10] = std::make_pair(7, 6);
  this->gateLinks[11] = std::make_pair(5, 4);
  this->gateLinks[12] = std::make_pair(3, 2);
  this->gateLinks[13] = std::make_pair(1, 15);
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4008::Compute(size_t pin_num_this) {

  if (pinIndexIsValid(pin_num_this))
    {
      // If the pin selected is an Output.
      if (this->gateLinks.find(pin_num_this) != this->gateLinks.end()) {

          // Get the indexes of the pins linked with the output.
          size_t  firstPinLinked = this->gateLinks[pin_num_this].first;
          size_t  secondPinLinked = this->gateLinks[pin_num_this].second;

          // Compute the inputs
          nts::Tristate v1 = Compute(firstPinLinked);
          nts::Tristate v2 = Compute(secondPinLinked);
          nts::Tristate cinp = (this->pins[13].component->getStateAtPin(1) == nts::Tristate::UNDEFINED) ? Compute(9) : Compute(14);


          // Call the door Or with v1 and v2 as parameters.
          this->pins[pin_num_this - 1].state = this->gate.compute("SUM", v1, v2, cinp);
          this->pins[13].state = this->gate.compute("SUMC", v1, v2, cinp);
          this->pins[13].component->setStateAtPin(1, this->gate.compute("SUMC", v1, v2, cinp));

          if (this->pins[pin_num_this - 1].component)
            this->pins[pin_num_this - 1].component->setStateAtPin(this->links[pin_num_this - 1].second,
                                                                  this->pins[pin_num_this - 1].state);
      }

      // If the pin selected is an Input.
      else if (this->pins[pin_num_this - 1].component && this->pins[pin_num_this - 1].type == INPUT) {
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
void            C4008::computeGates() {
  size_t        outputPins[] = { 10, 11, 12, 13};

  for (size_t i = 0; i < 4; i++) {
    Compute(outputPins[i]);
  }
}
