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
#include "Gate.hpp"

class   AComponent : public nts::IComponent {

public:

// Constructor and Destructor.
AComponent(const std::string &name, const std::string &type);
virtual ~AComponent();

// Methods from IComponent Interface.
virtual nts::Tristate   Compute(size_t pin_num_this = 1) = 0;
virtual void            SetLink(size_t pin_num_this, nts::IComponent &component,
                                size_t pin_num_target) = 0;
virtual void            Dump() const = 0;

// Additional :
// Compute all gates in the component.
virtual void            computeGates();

// Get the name of the component.
std::string     getName() const;
// Get the type of the component.
std::string     getType() const;

void            setValue(int val);

protected:

// Properties
const std::string   _name;
const std::string   _type;

public:
// Pins
struct s_pin        *pins;

};

// Pin Node
typedef struct      s_pin {
    AComponent      *component;
    nts::Tristate   state;
}                   Pin;

#endif // !_ACOMPONENT_HPP_
