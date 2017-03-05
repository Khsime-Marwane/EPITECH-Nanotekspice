//
// Author: Marwane Khsime 
// Date: 2017-02-08 15:26:44 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-08 15:26:44
//

#include "Factory.hpp"

/*
**  Create the maps of functions in order to create properly the components send as parameter
**  to the 'create()' function which is the constructor of component.
*/
nts::Factory::Factory() {
  this->basicConstructors["true"] = std::bind(&Factory::createTrue, this, std::placeholders::_1);
  this->basicConstructors["false"] = std::bind(&Factory::createFalse, this, std::placeholders::_1);
  this->basicConstructors["output"] = std::bind(&Factory::createOutput, this, std::placeholders::_1);
  this->basicConstructors["4071"] = std::bind(&Factory::createC4071, this, std::placeholders::_1);
  this->basicConstructors["4030"] = std::bind(&Factory::createC4030, this, std::placeholders::_1);
  this->basicConstructors["4081"] = std::bind(&Factory::createC4081, this, std::placeholders::_1);
  this->basicConstructors["4001"] = std::bind(&Factory::createC4001, this, std::placeholders::_1);
  this->basicConstructors["4011"] = std::bind(&Factory::createC4011, this, std::placeholders::_1);
  this->basicConstructors["4013"] = std::bind(&Factory::createC4013, this, std::placeholders::_1);
  this->basicConstructors["4017"] = std::bind(&Factory::createC4017, this, std::placeholders::_1);
  this->basicConstructors["4069"] = std::bind(&Factory::createC4069, this, std::placeholders::_1);
  this->basicConstructors["4008"] = std::bind(&Factory::createC4008, this, std::placeholders::_1);
  this->basicConstructors["4801"] = std::bind(&Factory::createC4801, this, std::placeholders::_1);
  this->basicConstructors["4514"] = std::bind(&Factory::createC4514, this, std::placeholders::_1);
  this->basicConstructors["4094"] = std::bind(&Factory::createC4094, this, std::placeholders::_1);
  this->basicConstructors["4040"] = std::bind(&Factory::createC4040, this, std::placeholders::_1);

  this->advancedConstructors["input"] = std::bind(&Factory::createInput, this, std::placeholders::_1, std::placeholders::_2);
  this->advancedConstructors["clock"] = std::bind(&Factory::createClock, this, std::placeholders::_1, std::placeholders::_2);
}

nts::Factory::~Factory() {}

/*
** Create() call the constructor of the type of component send as parameter, and return
** a new instance of this class. If the type is unknown, it return NULL.
**
** Some specifics components (like input) need to be initialized with a value.
*/
nts::AComponent *nts::Factory::create(const std::string &name,
                            const std::string &component,
                            size_t _value) {
  if (this->advancedConstructors.find(component) == this->advancedConstructors.end())
    return NULL;
  return this->advancedConstructors[component](name, _value);
}

nts::AComponent *nts::Factory::create(const std::string &name, const std::string &component) {
  if (this->basicConstructors.find(component) == this->basicConstructors.end())
    return NULL;
  return this->basicConstructors[component](name);
}

nts::AComponent *nts::Factory::createFalse(const std::string &name) const {
  //  std::cout << "Create FALSE component named '" << name << "'" << std::endl;
  return new False(name);
}

nts::AComponent *nts::Factory::createTrue(const std::string &name) const {
  // std::cout << "Create TRUE component named '" << name << "'" << std::endl;
  return new True(name);
}

nts::AComponent *nts::Factory::createInput(const std::string &name, size_t value) const {
  // std::cout << "Create INPUT component named '" << name << "'" << ", value : " << value << std::endl;
  return new Input(name, value);
}

nts::AComponent *nts::Factory::createClock(const std::string &name, size_t value) const {
  // std::cout << "Create CLOCK component named '" << name << "'" << ", value : " << value << std::endl;
  return new Clock(name, value);
}

nts::AComponent *nts::Factory::createOutput(const std::string &name) const {
  // std::cout << "Create OUTPUT component named '" << name << "'" << std::endl;
  return new Output(name);
}

nts::AComponent *nts::Factory::createC4071(const std::string &name) const {
  // std::cout << "Create C4071 component named '" << name << "'" << std::endl;
  return new C4071(name);
}

nts::AComponent *nts::Factory::createC4011(const std::string &name) const {
  // std::cout << "Create C4011 component named '" << name << "'" << std::endl;
  return new C4011(name);
}

nts::AComponent *nts::Factory::createC4013(const std::string &name) const {
  // std::cout << "Create C4013 component named '" << name << "'" << std::endl;
  return new C4013(name);
}

nts::AComponent *nts::Factory::createC4017(const std::string &name) const {
  // std::cout << "Create C4017 component named '" << name << "'" << std::endl;
  return new C4017(name);
}

nts::AComponent *nts::Factory::createC4081(const std::string &name) const {
  // std::cout << "Create C4081 component named '" << name << "'" << std::endl;
  return new C4081(name);
}

nts::AComponent *nts::Factory::createC4030(const std::string &name) const {
  // std::cout << "Create C4030 component named '" << name << "'" << std::endl;
  return new C4030(name);
}

nts::AComponent *nts::Factory::createC4001(const std::string &name) const {
  // std::cout << "Create C4001 component named '" << name << "'" << std::endl;
  return new C4001(name);
}

nts::AComponent *nts::Factory::createC4069(const std::string &name) const {
  // std::cout << "Create C4069 component named '" << name << "'" << std::endl;
  return new C4069(name);
}

nts::AComponent *nts::Factory::createC4008(const std::string &name) const {
  // std::cout << "Create C4008 component named '" << name << "'" << std::endl;
  return new C4008(name);
}

nts::AComponent *nts::Factory::createC4801(const std::string &name) const {
  // std::cout << "Create C48001 component named '" << name << "'" << std::endl;
  return new C4801(name);
}

nts::AComponent *nts::Factory::createC4514(const std::string &name) const {
  // std::cout << "Create C4514 component named '" << name << "'" << std::endl;
  return new C4514(name);
}

nts::AComponent *nts::Factory::createC4094(const std::string &name) const {
  // std::cout << "Create C4094 component named '" << name << "'" << std::endl;
  return new C4094(name);
}

nts::AComponent *nts::Factory::createC4040(const std::string &name) const {
  // std::cout << "Create C4040 component named '" << name << "'" << std::endl;
  return new C4040(name);
}
