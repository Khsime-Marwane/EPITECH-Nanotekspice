//
// Author: Marwane Khsime 
// Date: 2017-02-15 21:51:55 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-15 21:51:55
//

#ifndef _ACOMPONENT_HPP_
# define _ACOMPONENT_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <functional>

#include "IComponent.hpp"
#include "Errors.hpp"

class   AComponent : public nts::IComponent {

public:

// Constructor and Destructor
AComponent(const std::string &name, const std::string &type);
~AComponent();

// Methods from IComponent Interface
virtual nts::Tristate   Compute(size_t pin_num_this = 1) = 0;
virtual void            SetLink(size_t pin_num_this, nts::IComponent &component,
                                size_t pin_num_target) = 0;
virtual void            Dump() const = 0;

// Set the tristate value of the pin_num_this' pin
virtual void  SetTristate(size_t pin_num_this,
                  nts::Tristate value) = 0;
// Compute all gates in the component.
virtual void  computeAll() = 0;

// Get the name of the component.
std::string getName() const;
// Get the type of the component.
std::string getType() const;
// Get the value of the component (if it's special).
nts::Tristate   getValue() const;


protected:
const std::string   _name;
const std::string   _type;
nts::Tristate       _value;

};

#endif // !_ACOMPONENT_HPP_
