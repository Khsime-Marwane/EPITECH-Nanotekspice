//
// Author: Marwane Khsime 
// Date: 2017-02-08 15:26:44 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-08 15:26:44
//

#include "../include/Factory.hpp"

Factory::Factory() {
    this->constructors["true"] = std::bind(&Factory::createTrue, this);
    this->constructors["false"] = std::bind(&Factory::createFalse, this);
    this->constructors["input"] = std::bind(&Factory::createInput, this);
    this->constructors["output"] = std::bind(&Factory::createOutput, this);
    this->constructors["4071"] = std::bind(&Factory::createC4071, this);
}

Factory::~Factory() {

}

nts::IComponent *Factory::create(const std::string &component) {

    if (this->constructors.find(component) == this->constructors.end())
        return NULL;
    return this->constructors[component]();
}

nts::IComponent *Factory::createFalse() const {
    std::cout << "Create FALSE" << std::endl;
    return new False;
}

nts::IComponent *Factory::createTrue() const {
    std::cout << "Create TRUE" << std::endl;
    return new True;
}

nts::IComponent *Factory::createInput() const {
    std::cout << "Create INPUT" << std::endl;
    return new Input;
}

nts::IComponent *Factory::createOutput() const {
    std::cout << "Create OUTPUT" << std::endl;
    return new Output;
}

nts::IComponent *Factory::createC4071() const {
    std::cout << "Create C4071" << std::endl;
    return new C4071;
}