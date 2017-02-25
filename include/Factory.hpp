//
// Author: Marwane Khsime 
// Date: 2017-02-08 15:27:03 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-08 15:27:03
//

#ifndef _FACTORY_HPP_
# define _FACTORY_HPP_

#include <map>
#include <functional>
#include <utility>

#include "Errors.hpp"
#include "IComponent.hpp"

#include "False.hpp"
#include "True.hpp"
#include "Output.hpp"
#include "Input.hpp"
#include "C4071.hpp"
#include "C4081.hpp"
#include "C4001.hpp"
#include "C4030.hpp"
#include "C4011.hpp"
#include "C4069.hpp"
#include "C4008.hpp"


class   Factory {
 public:
  Factory();
  ~Factory();

  AComponent *create(const std::string &, const std::string &);
  AComponent *create(const std::string &, const std::string &, size_t);
 private:
  std::map<const std::string, std::function<AComponent *(const std::string &)> > basicConstructors;
  std::map<const std::string, std::function<AComponent *(const std::string &, size_t)> > advancedConstructors;

  AComponent *createFalse(const std::string &) const;
  AComponent *createTrue(const std::string &) const;
  AComponent *createInput(const std::string &, size_t value = nts::Tristate::UNDEFINED) const;
  AComponent *createOutput(const std::string &) const;
  AComponent *createC4071(const std::string &) const;
  AComponent *createC4081(const std::string &) const;
  AComponent *createC4001(const std::string &) const;
  AComponent *createC4030(const std::string &) const;
  AComponent *createC4011(const std::string &) const;
  AComponent *createC4069(const std::string &) const;
  AComponent *createC4008(const std::string &) const;
};

#endif /* _FACTORY_HPP_ */