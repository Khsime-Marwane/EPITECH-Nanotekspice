//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4514_HPP_
# define _C4514_HPP_

#include "AComponent.hpp"
#include "Gate.hpp"

class   C4514 : public AComponent {

 public:
// Constructor / Destructor
  C4514(const std::string &name);
  virtual ~C4514() { }

// Basics
  virtual nts::Tristate Compute(size_t pin_num_this = 1);
  virtual void  computeGates();

 private:

// Gates
  Gate  gate;
  std::map<size_t, std::pair<size_t, size_t> > gateLinks;

  void            initValuesOutputs();

  std::map<std::string, nts::Tristate> middleInputs;
  std::map<std::string, std::vector<int> > valOutputs;

};

#endif /* _C4514_HPP_ */