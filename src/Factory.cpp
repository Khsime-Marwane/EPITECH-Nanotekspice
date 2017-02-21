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
Factory::Factory() {
  this->basicConstructors["true"] = std::bind(&Factory::createTrue, this, std::placeholders::_1);
  this->basicConstructors["false"] = std::bind(&Factory::createFalse, this, std::placeholders::_1);
  this->basicConstructors["output"] = std::bind(&Factory::createOutput, this, std::placeholders::_1);
  this->basicConstructors["4071"] = std::bind(&Factory::createC4071, this, std::placeholders::_1);
  this->basicConstructors["4030"] = std::bind(&Factory::createC4030, this, std::placeholders::_1);
  this->basicConstructors["4081"] = std::bind(&Factory::createC4081, this, std::placeholders::_1);
  this->basicConstructors["4001"] = std::bind(&Factory::createC4001, this, std::placeholders::_1);
  this->basicConstructors["4011"] = std::bind(&Factory::createC4011, this, std::placeholders::_1);


  this->advancedConstructors["input"] = std::bind(&Factory::createInput, this, std::placeholders::_1, std::placeholders::_2);
}

Factory::~Factory() {}

/*
** Create() call the constructor of the type of component send as parameter, and return
** a new instance of this class. If the type is unknown, it return NULL.
**
** Some specifics components (like input) need to be initialized with a value.
*/
AComponent *Factory::create(const std::string &name,
                            const std::string &component,
                            size_t _value) {
  if (this->advancedConstructors.find(component) == this->advancedConstructors.end())
    return NULL;
  return this->advancedConstructors[component](name, _value);
}

AComponent *Factory::create(const std::string &name, const std::string &component) {
  if (this->basicConstructors.find(component) == this->basicConstructors.end())
    return NULL;
  return this->basicConstructors[component](name);
}

AComponent *Factory::createFalse(const std::string &name) const {
  std::cout << "Create FALSE component named '" << name << "'" << std::endl;
  return new False(name);
}

AComponent *Factory::createTrue(const std::string &name) const {
  std::cout << "Create TRUE component named '" << name << "'" << std::endl;
  return new True(name);
}

AComponent *Factory::createInput(const std::string &name, size_t value) const {
  std::cout << "Create INPUT component named '" << name << "'" << ", value : " << value << std::endl;
  return new Input(name, value);
}

AComponent *Factory::createOutput(const std::string &name) const {
  std::cout << "Create OUTPUT component named '" << name << "'" << std::endl;
  return new Output(name);
}

AComponent *Factory::createC4071(const std::string &name) const {
  std::cout << "Create C4071 component named '" << name << "'" << std::endl;
  return new C4071(name);
}

AComponent *Factory::createC4011(const std::string &name) const {
  std::cout << "Create C4011 component named '" << name << "'" << std::endl;
  return new C4011(name);
}

AComponent *Factory::createC4081(const std::string &name) const {
  std::cout << "Create C4081 component named '" << name << "'" << std::endl;
  return new C4081(name);
}

AComponent *Factory::createC4030(const std::string &name) const {
  std::cout << "Create C4030 component named '" << name << "'" << std::endl;
  return new C4030(name);
}

AComponent *Factory::createC4001(const std::string &name) const {
  std::cout << "Create C4001 component named '" << name << "'" << std::endl;
  return new C4001(name);
}