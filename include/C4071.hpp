//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4071_HPP_
# define _C4071_HPP_

#include "AComponent.hpp"
#include "Gate.hpp"

class   C4071 : public AComponent {

public:
C4071(const std::string &name);
virtual ~C4071() { }

// Basics
virtual nts::Tristate Compute(size_t pin_num_this = 1);
virtual void computeAllGates();
virtual void computeGate(size_t gate);
virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                     size_t pin_num_target);
// virtual void SetTristate(size_t pin_num_this, nts::Tristate _value);
virtual void Dump() const;

// Additionnals

private:

Pin             *pins[14];
std::map<size_t, std::pair<size_t, size_t> > outputLinks;
std::map<size_t, std::pair<size_t, size_t> > links;

// Gates
Gate                gate;

// For checking pin index parameter. return true if it's valid.
bool            pinIndexIsValid(size_t pin_num_this);

};

#endif /* _C4071_HPP_ */