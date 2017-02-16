//
// Author: Marwane Khsime 
// Date: 2017-02-16 00:25:01 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-16 00:25:01
//

#include "../include/AComponent.hpp"
#include "True.hpp"

AComponent::AComponent(const std::string &name, const std::string &type)
    : _name(name), _type(type) {
    this->_value = nts::Tristate::UNDEFINED;
}

AComponent::~AComponent() {

}

std::string     AComponent::getName() const {
    return this->_name;
}

std::string     AComponent::getType() const {
    return this->_type;
}

nts::Tristate   AComponent::getValue() const {
    return this->_value;
}

void  True::computeAll() {
  // Nothing to do here
}