//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4017_HPP_
# define _C4017_HPP_

#include "AComponent.hpp"

class   C4017 : public AComponent {

public:
// Constructor / Destructor
  C4017(const std::string &name);
  virtual ~C4017() { }

// Basics
  virtual nts::Tristate Compute(size_t pin_num_this = 1);
  virtual void computeGates();

private:
  size_t  current;
// Pins Order.
  std::map<size_t, size_t>  order;

  void            reset();
};

#endif /* _C4017_HPP_ */