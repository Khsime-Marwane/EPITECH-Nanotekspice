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
    this->_value = nts::Tristate::UNDEFINED;
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

// return the value of the component (if it's a special component).
nts::Tristate   AComponent::getValue() const {
    return this->_value;
}

void            AComponent::computeAll() {
    // nothing to do there if it's not surcharged by inherited class.
}