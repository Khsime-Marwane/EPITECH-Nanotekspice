//
// False.hh for False in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/include/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 09:45:44 2017 Marwane Khsime
// Last update Wed Feb  1 09:49:17 2017 Marwane Khsime
//

#ifndef _FALSE_HPP_
#define _FALSE_HPP_

#include "AComponent.hpp"

class False : public AComponent {

public:
  False(const std::string &name);
  virtual ~False();

  virtual nts::Tristate Compute(size_t pin_num_this = 1);
  virtual void computeAll();
  virtual void SetTristate(size_t pin_num_this, nts::Tristate _value);
  virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                       size_t pin_num_target);
  virtual void Dump() const;

private:
  // Pin of the component  
  nts::IComponent *pins[1];

  // The first value correspond to the n° of the pin of this component,
  // whose is linked with the n° pin of the second component (second value).
  std::pair<size_t, size_t> links;
};

#endif /* end of include guard: _FALSE_HPP_ */
