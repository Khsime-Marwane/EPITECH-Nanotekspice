//
// Author: Marwane Khsime 
// Date: 2017-02-08 15:26:44 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-08 15:26:44
//

#include "Factory.hpp"

Factory::Factory() {
    this->basicConstructors["true"] = std::bind(&Factory::createTrue, this);
    this->basicConstructors["false"] = std::bind(&Factory::createFalse, this);
    this->basicConstructors["output"] = std::bind(&Factory::createOutput, this);
    this->basicConstructors["4071"] = std::bind(&Factory::createC4071, this);
    
    this->advancedConstructors["input"] = std::bind(&Factory::createInput, this, std::placeholders::_1);
}

Factory::~Factory() {

}

nts::IComponent *Factory::create(const std::string &component,
                                 size_t _value) {
    if (this->advancedConstructors.find(component) == this->advancedConstructors.end())
        return NULL;
    return this->advancedConstructors[component](_value);
}

nts::IComponent *Factory::create(const std::string &component) {
    if (this->basicConstructors.find(component) == this->basicConstructors.end())
        return NULL;
    return this->basicConstructors[component]();
}

nts::IComponent *Factory::createFalse() const {
    std::cout << "Create FALSE" << std::endl;
    return new False;
}

nts::IComponent *Factory::createTrue() const {
    std::cout << "Create TRUE" << std::endl;
    return new True;
}

nts::IComponent *Factory::createInput(size_t value) const {
    std::cout << "Create INPUT" << std::endl;
    return new Input(value);
}

nts::IComponent *Factory::createOutput() const {
    std::cout << "Create OUTPUT" << std::endl;
    return new Output;
}

nts::IComponent *Factory::createC4071() const {
    std::cout << "Create C4071" << std::endl;
    return new C4071;
}