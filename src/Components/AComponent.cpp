//
// Author: Marwane Khsime 
// Date: 2017-02-16 00:25:01 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-16 00:25:01
//

#include "AComponent.hpp"
#include "True.hpp"

/*
** Constructor / Destructor
*/
AComponent::AComponent(const std::string &name, const std::string &type)
    : _name(name), _type(type) {
    this->_VSS = -1;
    this->_VDD = -1;
}

AComponent::~AComponent() {

}

/*
** return the name of the component.
*/
std::string     AComponent::getName() const {
    return this->_name;
}

/*
** return the type of the component.
*/
std::string     AComponent::getType() const {
    return this->_type;
}

/*
** Get the state of the pin's component at the pin 'index'.
*/
nts::Tristate   AComponent::getStateAtPin(size_t index) const {
    return this->pins[index - 1].state;
}

/*
** Set the state of the pin's component at the pin 'index'.
*/
void    AComponent::setStateAtPin(size_t index, nts::Tristate state)
{
  this->pins[index - 1].state = state;
}

/*
** Check if the pin selected exist in the component and if it's allowed.
*/
bool    AComponent::pinIndexIsValid(size_t pin_num_this) const {
  if (pin_num_this == _VDD || pin_num_this == _VSS)
    return 0;
  return pin_num_this > 0 && pin_num_this < (_nbPins + 1);
}

/*
** Check, when we are linking in the same component, if the pin used is an
** Input and if the target is an Output (in a chipset, we can only link an
** Output to an Input)
*/
bool            AComponent::doesPinsTypesMatch(size_t pin_num_this, size_t pin_num_target) {
  return this->pins[pin_num_this - 1].type == INPUT && this->pins[pin_num_target - 1].type == OUTPUT;
}

/*
** Check if the component type match with the type expected by the pin.
*/
bool            AComponent::doesComponentTypeMatch(AComponent &component,
                                              size_t pin_num_this,
                                              size_t pin_num_target) {
  // If the pin is an output, the component fixed must be also an output.
  return this->pins[pin_num_this - 1].type == INPUT || component.pins[pin_num_target - 1].type != OUTPUT;
}

/*
** Link a pin of the chipset with a component. When it's possible,
** also link on the other side the pin [pin_num_target] with this chipset.
*/
void            AComponent::SetLink(size_t pin_num_this,
                                    nts::IComponent &component,
                                    size_t pin_num_target) {

  // Check if the index (pin_num_this) is valid.
  if (!pinIndexIsValid(pin_num_this))
    throw Error("[" + this->getType() + " | LINK] : Invalid pin selected ("
                  + std::to_string((int)pin_num_target) + ").");
  // If we are linking pins in the same component.
  if (this == &component) {
    if (!doesPinsTypesMatch(pin_num_this, pin_num_target))
      throw Error("[" + this->_name + " | LINK] : Impossible to link the pin "
                  + std::to_string((int)pin_num_target) + " doesn't correspond with the type of the component '"
                  + (*dynamic_cast<AComponent *>(&component)).getName() + "'.");
  }

  // Check if the component type match with the type expected by the pin.
  else
    if (!doesComponentTypeMatch(*dynamic_cast<AComponent *>(&component), pin_num_this, pin_num_target))
      throw Error("[" + this->getType() + " | LINK] : Component type expected by the pin "
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
void    AComponent::Dump() const {

if (this->_nbPins == 1) {
    std::cout << this->_name << "=" << this->pins[0].state << std::endl;
} else {
    for (unsigned int i = 0; i < this->_nbPins; i++) {
        std::cout << this->_name << "[" << i + 1 << "] = ";
        if (this->pins[i].component)
            std::cout << (int)this->pins[i].state << std::endl;
        else std::cout << "NULL" << std::endl;
    }
  }
}

void            AComponent::computeGates() {
    // Nothing to do there if it's not surcharged by inherited class.
}