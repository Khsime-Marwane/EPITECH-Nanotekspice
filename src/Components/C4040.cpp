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
  pins = new Pin[16];
  tranState = false;

  PinType pinsTypeTab[16] = {
          OUTPUT,    // Pin 1
          OUTPUT,    // Pin 2
          OUTPUT,   // Pin 3
          OUTPUT,   // Pin 4
          OUTPUT,    // Pin 5
          OUTPUT,    // Pin 6
          OUTPUT,  // Pin 7
          IGNORED,    // Pin 8 (VSS)
          OUTPUT,    // Pin 9
          INPUT,   // Pin 10
          INPUT,   // Pin 11
          OUTPUT,    // Pin 12
          OUTPUT,    // Pin 13
          OUTPUT,    // Pin 14
          OUTPUT,   // Pin 15
          IGNORED // Pin 16 (VDD)
  };
  // Create the pins of the chipset 4040 and set them.
  for (unsigned int i = 0; i < 16; i++) {
      this->pins[i].state = nts::UNDEFINED;
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
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4040::Compute(size_t pin_num_this) {

  if (pinIndexIsValid(pin_num_this))
    {
      // If the pin selected is an Output.
      if (this->gateLinks.find(pin_num_this) != this->gateLinks.end() && startFromGate) {

          nts::Tristate clk = this->pins[9].state;

          if (this->pins[10].state == nts::Tristate::TRUE)
            this->pins[pin_num_this - 1].state = nts::Tristate::FALSE;
          else if (tranState)
            this->pins[pin_num_this - 1].state = clk;

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
void            C4040::computeGates() {
  size_t        outputPins[] = { 9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1 };

  this->pins[9].state = this->pins[9].component->getStateAtPin(1);
  this->pins[10].state = this->pins[10].component->getStateAtPin(1);

  startFromGate = true;

  for (size_t i = 0; i < 12; i++) {
      Compute(outputPins[i]);
    }
  tranState = true;
  startFromGate = false;
}

/*
** Check if the pin selected exist in the component,
** indexes allowed there are [1, 14].
*/
bool            C4040::pinIndexIsValid(size_t pin_num_this)
{
  if (pin_num_this == 8 || pin_num_this == 16)
    return 0;
  return pin_num_this > 0 && pin_num_this < 16;
}


/*
** Check if the component type match with the type expected by the pin.
*/
bool            C4040::doesComponentTypeMatch(AComponent &component,
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
bool            C4040::doesPinsTypesMatch(size_t pin_num_this, size_t pin_num_target) {
  return this->pins[pin_num_this - 1].type == INPUT && this->pins[pin_num_target - 1].type == OUTPUT;
}

/*
** Link a pin of the chipset with a component. When it's possible,
** also link on the other side the pin [pin_num_target] with this chipset.
*/
void    C4040::SetLink(size_t pin_num_this,
                       nts::IComponent &component,
                       size_t pin_num_target) {

  // Check if the index (pin_num_this) is valid.
  if (!pinIndexIsValid(pin_num_this))
    throw Error("[ C4040 " + this->_name + " | LINK] : Invalid pin selected ("
                + std::to_string((int)pin_num_target) + ").");

  // If we are linking pins in the same component.
  if (this == &component) {
      if (!doesPinsTypesMatch(pin_num_this, pin_num_target))
        throw Error("[ C4040 " + this->_name + " | LINK] : Impossible to link the pin "
                    + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                    + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
    }
    // Check if the component type match with the type expected by the pin.
  else
    {
      if (!doesComponentTypeMatch(*dynamic_cast<AComponent *>(&component), pin_num_this, pin_num_target))
        {
          throw Error("[ C4040 " + this->_name + " | LINK] : Component type expected by the pin "
                      + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                      + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
        }
      else if (pin_num_this == 10)
          {
            if ((*dynamic_cast<AComponent *>(&component)).getType() != "clock")
              throw Error("[ C4040 " + this->_name + " | LINK] : Component type expected by the pin "
                          + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                          + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
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

      this->pins[pin_num_this - 1].state = dynamic_cast<AComponent *>(&component)->pins[pin_num_target - 1].state;
    };
}

/*
** Display all the states of each pin of the chipset. If a pin is not linked,
** it display 'NULL'.
*/
void    C4040::Dump() const {

  std::cout << _name << std::endl;
  for (unsigned int i = 0; i < 16; i++) {
      std::cout << this->_name << "[" << i + 1 << "] = ";
      if (this->pins[i].component)
        std::cout << (int)this->pins[i].state << std::endl;
      else std::cout << "NULL" << std::endl;
    }
}