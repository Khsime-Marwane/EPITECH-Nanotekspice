//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4071_HPP_
# define _C4071_HPP_

#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <functional>

#include "IComponent.hpp"
#include "Errors.hpp"

class   C4071 : public nts::IComponent {

public:
C4071();
virtual ~C4071();

// Basics
virtual nts::Tristate Compute(size_t pin_num_this = 1);
virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                     size_t pin_num_target);
virtual void SetTristate(size_t pin_num_this, nts::Tristate _value);
virtual void Dump() const;

// Additionnals
nts::Tristate   OR_Function(nts::Tristate first, nts::Tristate second) const;
nts::Tristate   computeInput(size_t pin_num_this);
nts::Tristate   computeOutput(size_t pin_num_this);
nts::Tristate   computeV(size_t pin_num_this);

private:
nts::IComponent *pins[14];
std::map<size_t, std::function<nts::Tristate(size_t)> > mapPins;
std::map<size_t, std::pair<size_t, size_t> > outputLinks;
std::map<size_t, std::pair<size_t, size_t> > links;
};

#endif /* _C4071_HPP_ */