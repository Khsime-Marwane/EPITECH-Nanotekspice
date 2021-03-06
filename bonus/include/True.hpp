//
// True.hh for True in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/include/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 09:45:44 2017 Marwane Khsime
// Last update Wed Feb  1 09:49:17 2017 Marwane Khsime
//

#ifndef _TRUE_HPP_
#define _TRUE_HPP_

#include "AComponent.hpp"
namespace nts
{
  class True : public nts::AComponent {

   public:
    True(const std::string &name);
    virtual ~True();

    // Inherited from IComponent
    virtual nts::Tristate Compute(size_t pin_num_this = 1);
    virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                         size_t pin_num_target);
  };

}
#endif /* end of include guard: _TRUE_HPP_ */
