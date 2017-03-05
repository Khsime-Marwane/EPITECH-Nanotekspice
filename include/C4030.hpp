//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4030_HPP_
# define _C4030_HPP_

#include "AComponent.hpp"
namespace nts
{
  class   C4030 : public nts::AComponent {

   public:
// Constructor / Destructor
    C4030(const std::string &name);
    virtual ~C4030() { }

// Basics
    virtual nts::Tristate Compute(size_t pin_num_this = 1);
    virtual void computeGates();

   private:

// Gates
    Gate  gate;
    std::map<size_t, std::pair<size_t, size_t> > gateLinks;

  };

}
#endif /* _C4030_HPP_ */