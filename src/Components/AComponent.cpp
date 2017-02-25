//
// Author: Marwane Khsime 
// Date: 2017-02-16 00:25:01 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-16 00:25:01
//

#include "AComponent.hpp"
#include "True.hpp"

// Constructor / Destructor
AComponent::AComponent(const std::string &name, const std::string &type)
    : _name(name), _type(type) {
}

AComponent::~AComponent() {

}

// return the name of the component.
std::string     AComponent::getName() const {
    return this->_name;
}

// return the type of the component.
std::string     AComponent::getType() const {
    return this->_type;
}

// Get the state of the pin's component at the pin 'index'.
nts::Tristate   AComponent::getStateAtPin(size_t index) const {
    return this->pins[index - 1].state;
}

// Set the state of the pin's component at the pin 'index'.
void    AComponent::setStateAtPin(size_t index, nts::Tristate state)
{
  this->pins[index - 1].state = state;
}

void            AComponent::computeGates() {
    // Nothing to do there if it's not surcharged by inherited class.
}