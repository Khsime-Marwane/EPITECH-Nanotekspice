//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4040_HPP_
# define _C4040_HPP_

#include "AComponent.hpp"

class   C4040 : public AComponent {

 public:
// Constructor / Destructor
  C4040(const std::string &name);
  virtual ~C4040() { }

// Basics
  virtual nts::Tristate Compute(size_t pin_num_this = 1);
  virtual void  computeGates();

 private:
  bool  previous;
  int   current;
  std::map<size_t, size_t>  order;

  // Gates
  Gate  gate;
  std::map<size_t, std::pair<size_t, size_t> > gateLinks;

};

#endif /* _C4040_HPP_ */