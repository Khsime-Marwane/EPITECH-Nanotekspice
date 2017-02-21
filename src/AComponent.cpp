//
// Author: Marwane Khsime 
// Date: 2017-02-16 00:25:01 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-16 00:25:01
//

#include "../include/AComponent.hpp"
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

void    AComponent::setValue(int val)
{
  this->pins[0].state = (nts::Tristate)val;
}

// return the state of the component (if it's special)

void            AComponent::computeGates() {
    // nothing to do there if it's not surcharged by inherited class.
}