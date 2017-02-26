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
C4013::C4013(const std::string &name) : AComponent(name, "chipset") {
  this->pins = new Pin[14];

  PinType pinsTypeTab[14] = {
    OUTPUT,    // Pin 1
    OUTPUT,    // Pin 2
    INPUT,   // Pin 3
    INPUT,   // Pin 4
    INPUT,    // Pin 5
    INPUT,    // Pin 6
    IGNORED,  // Pin 7  (VSS)
    INPUT,    // Pin 8
    INPUT,    // Pin 9
    INPUT,   // Pin 10
    INPUT,   // Pin 11
    OUTPUT,    // Pin 12
    OUTPUT,    // Pin 13
    IGNORED   // Pin 14 (VDD)
  };

  // Create the pins of the chipset 4013 and set them.
  for (unsigned int i = 0; i < 14; i++) {
      this->pins[i].state = nts::UNDEFINED;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
    }

  // Output pins with their inputs index.
  this->gateLinks[1] = std::make_pair(4, 6);
  this->gateLinks[12] = std::make_pair(10, 8);
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4013::Compute(size_t pin_num_this) {

  if (pinIndexIsValid(pin_num_this))
    {
      // If the pin selected is an Output.
      if (this->gateLinks.find(pin_num_this) != this->gateLinks.end()) {

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
              this->pins[pin_num_this - 1].state = v2;
              this->pins[pin_num_this].state = v1;
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

                this->pins[pin_num_this - 1].state = data;
                if (this->pins[pin_num_this - 1].component)
                  this->pins[pin_num_this - 1].component->setStateAtPin(1, data);

                this->pins[pin_num_this].state = (nts::Tristate)(!data);
                if (this->pins[pin_num_this ].component)
                  this->pins[pin_num_this].component->setStateAtPin(1, (nts::Tristate)(!data));
              }

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
void            C4013::computeGates() {
  size_t        outputPins[] = { 1, 12};

  for (size_t i = 0; i < 2; i++) {
    Compute(outputPins[i]);
  }
}

/*
** Check if the pin selected exist in the component,
** indexes allowed there are [1, 14].
*/
bool            C4013::pinIndexIsValid(size_t pin_num_this) {
  if (pin_num_this == 7 || pin_num_this == 14)
    return 0;
  return pin_num_this > 0 && pin_num_this < 15;
}

/*
** Check if the component type match with the type expected by the pin.
*/
bool            C4013::doesComponentTypeMatch(AComponent &component, size_t pin) {
  // If the pin is an output, the component fixed must be also an output.
  if (this->pins[pin - 1].type == OUTPUT)
    return component.getType() == "output";
  // Others pins can be fixed with any type of component.
  return true;
}

/*
** Check, when we are linking in the same component, if the pin used is an
** Input and if the target is an Output (in a chipset, we can only link an
** Output to an Input)
*/
bool            C4013::doesPinsTypesMatch(size_t pin_num_this, size_t pin_num_target) {
  return this->pins[pin_num_this - 1].type == INPUT && this->pins[pin_num_target - 1].type == OUTPUT;
}

/*
** Link a pin of the chipset with a component. When it's possible,
** also link on the other side the pin [pin_num_target] with this chipset.
*/
void    C4013::SetLink(size_t pin_num_this,
                       nts::IComponent &component,
                       size_t pin_num_target) {

  // Check if the index (pin_num_this) is valid.
  if (!pinIndexIsValid(pin_num_this))
    throw Error("[ C4013 " + this->_name + " | LINK] : Invalid pin selected ("
                  + std::to_string((int)pin_num_target) + ").");

  // If we are linking pins in the same component.
  if (this == &component && !doesPinsTypesMatch(pin_num_this, pin_num_target))
    throw Error("[ C4013 " + this->_name + " | LINK] : Impossible to link the pin "
                + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
  
  // Check if the component type match with the type expected by the pin.
  else if (!doesComponentTypeMatch(*dynamic_cast<AComponent *>(&component), pin_num_this))
    throw Error("[ C4013 " + this->_name + " | LINK] : Component type expected by the pin "
                + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");

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
void    C4013::Dump() const {

std::cout << _name << std::endl;
  for (unsigned int i = 0; i < 14; i++) {
      std::cout << this->_name << "[" << i + 1 << "] = ";
      if (this->pins[i].component)
        std::cout << (int)this->pins[i].state << std::endl;
      else std::cout << "NULL" << std::endl;
    }
}