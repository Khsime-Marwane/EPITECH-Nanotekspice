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

#include "C4040.hpp"

/*
** The component 4040 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4040::C4040(const std::string &name) : AComponent(name, "chipset") {

  this->_nbPins = 16;
  this->_VSS = 8;
  this->_VDD = 16;

  this->pins = new Pin[this->_nbPins];
  this->current = 0;
  this->pow_fact = 1;
  this->first = true;

  PinType pinsTypeTab[this->_nbPins] = {
          OUTPUT,   // Pin 1
          OUTPUT,   // Pin 2
          OUTPUT,   // Pin 3
          OUTPUT,   // Pin 4
          OUTPUT,   // Pin 5
          OUTPUT,   // Pin 6
          OUTPUT,   // Pin 7
          IGNORED,  // Pin 8 (VSS)
          OUTPUT,   // Pin 9
          CLOCK,    // Pin 10
          INPUT,    // Pin 11
          OUTPUT,   // Pin 12
          OUTPUT,   // Pin 13
          OUTPUT,   // Pin 14
          OUTPUT,   // Pin 15
          IGNORED   // Pin 16 (VDD)
  };

  // Create the pins of the chipset 4040 and set them.
  for (unsigned int i = 0; i < this->_nbPins; i++) {
      this->pins[i].state = nts::Tristate::FALSE;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
    }

  // Output pins with their inputs index.
  this->gateLinks[1] = std::make_pair(0, 0);
  this->gateLinks[2] = std::make_pair(0, 0);
  this->gateLinks[3] = std::make_pair(0, 0);
  this->gateLinks[4] = std::make_pair(0, 0);
  this->gateLinks[5] = std::make_pair(0, 0);
  this->gateLinks[6] = std::make_pair(0, 0);
  this->gateLinks[7] = std::make_pair(0, 0);
  this->gateLinks[9] = std::make_pair(0, 0);
  this->gateLinks[12] = std::make_pair(0, 0);
  this->gateLinks[13] = std::make_pair(0, 0);
  this->gateLinks[14] = std::make_pair(0, 0);
  this->gateLinks[15] = std::make_pair(0, 0);

  // Pin index with the decimal value associated.
  this->order[0] = 9;
  this->order[1] = 7;
  this->order[2] = 6;
  this->order[3] = 5;
  this->order[4] = 3;
  this->order[5] = 2;
  this->order[6] = 4;
  this->order[7] = 13;
  this->order[8] = 12;
  this->order[9] = 14;
  this->order[10] = 15;
  this->order[11] = 1;

}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4040::Compute(size_t pin_num_this) {
  // If the pin selected is valid.
  if (pinIndexIsValid(pin_num_this))
    return (this->pins[pin_num_this - 1].state);

  // If the pin doesn't exist, or if it's a VSS / VDD, throw an error.
  throw Error("ERROR : [ " + this->_name + " | COMPUTE] : Invalid pin selected.");
  return nts::Tristate::UNDEFINED;
}

/*
** Compute all gates (outputs) of the chipset, if it can be computed.
*/
void            C4040::computeGates() {

  this->pins[9].state = this->pins[9].component->Compute(this->links[9].second);
  this->pins[10].state = this->pins[10].component->Compute(this->links[10].second);

  if (this->pow_fact == 12 || this->pins[10].state == nts::Tristate::TRUE)
    {
      this->pow_fact = 1;
      this->current = 1;
      for (unsigned int i = 0; i < this->_nbPins; i++)
        this->pins[i].state = nts::Tristate::FALSE;
    }

  if (this->pins[9].state == nts::Tristate::TRUE && this->first)
    this->current++;
  int tmp = this->current/2;
  for (int i = 0; i < 12; ++i)
    {
      int bite = tmp % 2;
      this->pins[this->order[i] - 1].state = (nts::Tristate)(bite);
      tmp /= 2;
    }
  this->current++;
  this->first = false;
}