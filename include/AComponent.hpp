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

// === FUNCTIONS
public:
// Constructor and Destructor.
AComponent(const std::string &name, const std::string &type);
virtual ~AComponent();

// Methods from IComponent Interface.
virtual nts::Tristate   Compute(size_t pin_num_this = 1) = 0;

virtual void            SetLink(size_t pin_num_this, nts::IComponent &component,
                                size_t pin_num_target);
virtual void            Dump() const;

// ==== Additional :
// Check if the pin we are computing exist or is valid.  
bool            pinIndexIsValid(size_t pin_num_this) const;
// Check, when we are linking in the same component, if we are linking an Output to an Input.
bool            doesPinsTypesMatch(size_t pin_num_this, size_t pin_num_target) const;
// Check if the component type match with the type expected by the pin.
bool            doesComponentTypeMatch(AComponent &component, size_t first, size_t second) const;
// Compute all gates in the component.
virtual void    computeGates();
// Get the name of the component.
std::string     getName() const;
// Get the type of the component.
std::string     getType() const;
// Get the value of the component at the pin 'index'
nts::Tristate   getStateAtPin(size_t target) const;
// Set the value of the component at the pin 'index'.
void            setStateAtPin(size_t index, nts::Tristate state);

// === VARIABLES
protected:

// Properties
const std::string   _name;
const std::string   _type;
size_t              _VSS;
size_t              _VDD;
size_t              _nbPins;
std::map<size_t, std::pair<size_t, size_t> >  links;

public:
// Pins
struct s_pin        *pins;

};

/*
**  Note: An Hybrid component can simulate an input or an output
*/

enum PinType { IGNORED = (-true), INPUT = 0, CLOCK = 1, OUTPUT = 2 };

// Pin Node
typedef struct      s_pin {
    AComponent      *component;
    nts::Tristate   state;
    PinType         type;
}                   Pin;

#endif // !_ACOMPONENT_HPP_
