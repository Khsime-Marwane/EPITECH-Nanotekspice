//
// Author: Marwane Khsime 
// Date: 2017-02-04 19:55:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-04 19:55:57
//

#ifndef _C4801_HPP_
# define _C4801_HPP_

#include "AComponent.hpp"

# define _WRITE_ENABLE_ 20
# define _OUTPUT_ENABLE_ 19
# define _NO_CONNECTION_ 18
# define _CHIP_ENABLE_ 17
# define _SIZE_ 1024
# define _COLUMNS_ 128
# define _HYBRID_ IGNORED
namespace nts
{
  class   C4801 : public nts::AComponent {

   public:
// Constructor / Destructor
    C4801(const std::string &name);
    virtual ~C4801() { }

// Basics
    virtual nts::Tristate Compute(size_t pin_num_this = 1);
    virtual void computeGates();

   private:
    int      memory[1024];


    size_t   getX() const;
    size_t   getY() const;

    void  refreshInputs();
    void  refreshOutputs();
    void  resetOutputs();
    void  setValueOnOutputs(int value);
    int   getValueFromOutputs();
  };
}
#endif /* _C4801_HPP_ */