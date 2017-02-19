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
    
    this->advancedConstructors["input"] = std::bind(&Factory::createInput, this, std::placeholders::_1, std::placeholders::_2);
}

Factory::~Factory() {

}

/*
** Create() call the constructor of the type of component send as parameter, and return
** a new instance of this class. If the type is unknown, it return NULL.
**
** Some specifics components (like input) need to be initialized with a value.
*/
nts::IComponent *Factory::create(const std::string &name,
                                 const std::string &component,
                                 size_t _value) {
    if (this->advancedConstructors.find(component) == this->advancedConstructors.end())
        return NULL;
    return this->advancedConstructors[component](name, _value);
}

nts::IComponent *Factory::create(const std::string &name, const std::string &component) {
    if (this->basicConstructors.find(component) == this->basicConstructors.end())
        return NULL;
    return this->basicConstructors[component](name);
}

nts::IComponent *Factory::createFalse(const std::string &name) const {
    std::cout << "Create FALSE component named '" << name << "'" << std::endl;
    return new False(name);
}

nts::IComponent *Factory::createTrue(const std::string &name) const {
    std::cout << "Create TRUE component named '" << name << "'" << std::endl;
    return new True(name);
}

nts::IComponent *Factory::createInput(const std::string &name, size_t value) const {
    std::cout << "Create INPUT component named '" << name << "'" << std::endl;
    return new Input(name, value);
}

nts::IComponent *Factory::createOutput(const std::string &name) const {
    std::cout << "Create OUTPUT component named '" << name << "'" << std::endl;
    return new Output(name);
}

nts::IComponent *Factory::createC4071(const std::string &name) const {
    std::cout << "Create C4071 component named '" << name << "'" << std::endl;
    return new C4071(name);
}