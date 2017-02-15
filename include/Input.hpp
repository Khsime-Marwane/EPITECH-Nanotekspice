//
// Input.hh for Input in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/include/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 09:45:44 2017 Marwane Khsime
// Last update Wed Feb  1 09:49:17 2017 Marwane Khsime
//

#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include <iostream>
#include <string>
#include <utility>

#include "IComponent.hpp"
#include "Errors.hpp"

class Input : public nts::IComponent {

public:
  Input(const std::string &name, int _value);
  virtual ~Input();
  virtual std::string getName() const;
  virtual std::string getType() const;
  virtual nts::Tristate getValue() const;
  virtual nts::Tristate Compute(size_t pin_num_this = 1);
  virtual void SetTristate(size_t pin_num_this, nts::Tristate _value);
  virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                       size_t pin_num_target);
  virtual void Dump() const;

private:
  std::string name;
  nts::Tristate value;
  nts::IComponent *pins[1];

  // The first value correspond to the n° of the pin of this component,
  // whose is linked with the n° pin of the second component (second value).
  std::pair<size_t, size_t> links;
};

#endif /* end of include guard: _INPUT_HPP_ */
