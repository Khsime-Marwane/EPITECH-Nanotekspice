//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4069_HPP_
# define _C4069_HPP_

#include "AComponent.hpp"
#include "Gate.hpp"

class   C4069 : public AComponent {

public:
// Constructor / Destructor
  C4069(const std::string &name);
  virtual ~C4069() { }

// Basics
  virtual nts::Tristate Compute(size_t pin_num_this = 1);
  virtual void computeGates();
 
private:

// Gates
  Gate  gate;
  std::map<size_t, std::pair<int, int> > gateLinks;
};

#endif /* _C4069_HPP_ */