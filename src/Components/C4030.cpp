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

#include "C4030.hpp"

/*
** The component 4030 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4030::C4030(const std::string &name) : AComponent(name, "chipset") {
  this->pins = new Pin[14];

  PinType pinsTypeTab[14] = {
    INPUT,    // Pin 1
    INPUT,    // Pin 2
    OUTPUT,   // Pin 3
    OUTPUT,   // Pin 4
    INPUT,    // Pin 5
    INPUT,    // Pin 6
    IGNORED,  // Pin 7  (VSS)
    INPUT,    // Pin 8
    INPUT,    // Pin 9
    OUTPUT,   // Pin 10
    OUTPUT,   // Pin 11
    INPUT,    // Pin 12
    INPUT,    // Pin 13
    IGNORED   // Pin 14 (VDD)
  };

  // Create the pins of the chipset 4030 and set them.
  for (unsigned int i = 0; i < 14; i++) {
      this->pins[i].state = nts::UNDEFINED;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
    }

  // Output pins with their inputs index.
  this->gateLinks[3] = std::make_pair(1, 2);
  this->gateLinks[4] = std::make_pair(5, 6);
  this->gateLinks[10] = std::make_pair(8, 9);
  this->gateLinks[11] = std::make_pair(12, 13);
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4030::Compute(size_t pin_num_this) {

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

          // Call the door Or with v1 and v2 as parameters.
          this->pins[pin_num_this - 1].state = this->gate.compute("XOR", v1, v2);
          if (this->pins[pin_num_this - 1].component)
            this->pins[pin_num_this - 1].component->setStateAtPin(this->links[pin_num_this].second,
                                                                  this->pins[pin_num_this - 1].state);
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
void            C4030::computeGates() {
  int           outputPins[] = { 3, 4, 10, 11 };

  for (unsigned int i = 0; i < 4; i++) {
    if (this->pins[this->gateLinks[outputPins[i]].first - 1].component &&
        this->pins[this->gateLinks[outputPins[i]].second - 1].component) {

      // Compute the inputs
      nts::Tristate v1 = Compute(this->gateLinks[outputPins[i]].first);
      nts::Tristate v2 = Compute(this->gateLinks[outputPins[i]].second);

      // Call the door OR with v1 and v2 as parameters.
      this->pins[outputPins[i] - 1].state = this->gate.compute("OR", v1, v2);
    }
  }
}

/*
** Check if the pin selected exist in the component,
** indexes allowed there are [1, 14].
*/
bool            C4030::pinIndexIsValid(size_t pin_num_this) {
  if (pin_num_this == 7 || pin_num_this == 14)
    return 0;
  return pin_num_this > 0 && pin_num_this < 15;
}

/*
** Check if the component type match with the type expected by the pin.
*/
bool            C4030::doesComponentTypeMatch(AComponent &component, size_t pin) {
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
bool            C4030::doesPinsTypesMatch(size_t pin_num_this, size_t pin_num_target) {
  return this->pins[pin_num_this].type == INPUT && this->pins[pin_num_target].type == OUTPUT;
}

/*
** Link a pin of the chipset with a component. When it's possible,
** also link on the other side the pin [pin_num_target] with this chipset.
*/
void    C4030::SetLink(size_t pin_num_this,
                       nts::IComponent &component,
                       size_t pin_num_target) {

  // Check if the index (pin_num_this) is valid.
  if (!pinIndexIsValid(pin_num_this))
    throw Error("[ C4030 " + this->_name + " | LINK] : Invalid pin selected ("
                  + std::to_string((int)pin_num_target) + ").");

  // If we are linking pins in the same component.
  if (this == &component && !doesPinsTypesMatch(pin_num_this, pin_num_target))
    throw Error("[ C4030 " + this->_name + " | LINK] : Impossible to link the pin "
                + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
  
  // Check if the component type match with the type expected by the pin.
  else if (!doesComponentTypeMatch(*dynamic_cast<AComponent *>(&component), pin_num_this))
    throw Error("[ C4030 " + this->_name + " | LINK] : Component type expected by the pin "
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
void    C4030::Dump() const {
  for (unsigned int i = 0; i < 14; i++) {
      std::cout << this->_name << "[" << i + 1 << "] = ";
      if (this->pins[i].component)
        std::cout << (int)this->pins[i].state << std::endl;
      else std::cout << "NULL" << std::endl;
    }
}