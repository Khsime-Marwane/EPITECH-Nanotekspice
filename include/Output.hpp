//
// Output.hh for Output in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/include/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 09:45:44 2017 Marwane Khsime
// Last update Wed Feb  1 09:49:17 2017 Marwane Khsime
//

#ifndef _OUTPUT_HPP_
#define _OUTPUT_HPP_

#include <iostream>
#include <string>
#include <utility>

#include "IComponent.hpp"
#include "Errors.hpp"

class Output : public nts::IComponent {

public:
  Output();
  virtual ~Output();
  virtual nts::Tristate Compute(size_t pin_num_this = 1);
  virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                       size_t pin_num_target);
  virtual void Dump() const;
  nts::Tristate getValue() const;
  nts::Tristate value;

private:
  nts::IComponent *pins[1];

  // The first value correspond to the n° of the pin of this component,
  // whose is linked with the n° pin of the second component (second value).
  std::pair<size_t, size_t> links;
};

#endif /* end of include guard: _OUTPUT_HPP_ */
