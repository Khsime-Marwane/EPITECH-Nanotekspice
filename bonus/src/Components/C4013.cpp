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

#include "C4013.hpp"

/*
** The component 4013 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
nts::C4013::C4013(const std::string &name) : nts::AComponent(name, "chipset") {
  this->tranState = false;
  this->_nbPins = 14;
  this->_VSS = 7;
  this->_VDD = 14;
  this->old = nts::Tristate::UNDEFINED;
  this->nold = nts::Tristate::UNDEFINED;

  this->pins = new nts::Pin[this->_nbPins];

  nts::PinType  pinsTypeTab[this->_nbPins] = {
                OUTPUT,  // Pin 1
                OUTPUT,  // Pin 2
                CLOCK,   // Pin 3
                INPUT,   // Pin 4
                INPUT,   // Pin 5
                INPUT,   // Pin 6
                IGNORED, // Pin 7  (VSS)
                INPUT,   // Pin 8
                INPUT,   // Pin 9
                INPUT,   // Pin 10
                CLOCK,   // Pin 11
                OUTPUT,  // Pin 12
                OUTPUT,  // Pin 13
                IGNORED  // Pin 14 (VDD)
  };

  // Create the pins of the chipset 4013 and set them.
  for (unsigned int i = 0; i < this->_nbPins; i++) {
      this->pins[i].state = nts::Tristate::FALSE;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
    }

  this->pins[0].state = nts::Tristate::UNDEFINED;
  this->pins[1].state = nts::Tristate::UNDEFINED;
  this->pins[11].state = nts::Tristate::UNDEFINED;
  this->pins[12].state = nts::Tristate::UNDEFINED;

  // Output pins with their inputs index.
  this->gateLinks[1] = std::make_pair(4, 6);
  this->gateLinks[12] = std::make_pair(10, 8);
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   nts::C4013::Compute(size_t pin_num_this) {

  if (pinIndexIsValid(pin_num_this))
    {
      // If the pin selected is an Output.
      if (this->gateLinks.find(pin_num_this) != this->gateLinks.end() && this->startFromGate) {

          // Get the indexes of the pins linked with the output.
          size_t  firstPinLinked = this->gateLinks[pin_num_this].first;
          size_t  secondPinLinked = this->gateLinks[pin_num_this].second;

          if (this->pins[10].component)
            this->pins[10].state = this->pins[10].component->getStateAtPin(1);

          if (this->pins[2].component)
            this->pins[2].state = this->pins[2].component->getStateAtPin(1);

          // Compute the inputs
          nts::Tristate v1 = Compute(firstPinLinked);
          nts::Tristate v2 = Compute(secondPinLinked);
          nts::Tristate clk = (pin_num_this == 1) ? this->pins[2].state : this->pins[10].state;


          if ((v1 == nts::Tristate::TRUE || v2 == nts::Tristate::TRUE) || clk == nts::Tristate::FALSE)
            {
              if (clk == nts::Tristate::FALSE && v1 == nts::Tristate::FALSE && v2 == nts::Tristate::FALSE)
                {
                  this->pins[pin_num_this - 1].state = this->old;
                  this->pins[pin_num_this].state = this->nold;
                }
              else
                {
                  this->pins[pin_num_this - 1].state = v2;
                  this->pins[pin_num_this].state = v1;
                }
              if (this->pins[pin_num_this - 1].component)
                this->pins[pin_num_this - 1].component->setStateAtPin(this->links[pin_num_this - 1].second,
                                                                      this->pins[pin_num_this - 1].state);
              if (this->pins[pin_num_this].component)
                this->pins[pin_num_this].component->setStateAtPin(this->links[pin_num_this].second,
                                                                  this->pins[pin_num_this].state);
            }
          else if (clk == nts::Tristate::TRUE)
              {
                nts::Tristate data = (pin_num_this == 1) ? Compute(5) : Compute(9);

                if (!tranState)
                  {
                    this->pins[pin_num_this - 1].state = this->old;
                    this->pins[pin_num_this].state = this->nold;
                  }
                else
                  {
                    this->pins[pin_num_this - 1].state = data;
                    this->pins[pin_num_this].state = (nts::Tristate)(!data);
                  }
                if (this->pins[pin_num_this - 1].component)
                  this->pins[pin_num_this - 1].component->setStateAtPin(this->links[pin_num_this - 1].second,
                                                                        this->pins[pin_num_this - 1].state);
                if (this->pins[pin_num_this].component)
                  this->pins[pin_num_this].component->setStateAtPin(this->links[pin_num_this].second,
                                                                    this->pins[pin_num_this].state);
              }
          this->old = this->pins[pin_num_this - 1].state;
          this->nold = this->pins[pin_num_this].state;
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
void            nts::C4013::computeGates() {
  size_t        outputPins[] = {1, 12};

  this->startFromGate = true;

  for (size_t i = 0; i < 2; i++) {
    Compute(outputPins[i]);
  }

  this->startFromGate = false;
  this->tranState = true;
}