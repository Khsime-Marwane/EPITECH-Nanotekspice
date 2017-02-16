//
// Chipset4001.cpp for 4001 in
// /home/marwane/Projets/Epitech/CPP/cpp_nanotekspice/Chipsets/
//
// Made by Marwane Khsime
// Login   <marwane.khsime@epitech.eu@epitech.eu>
//
// Started on  Wed Feb  1 02:16:32 2017 Marwane Khsime
// Last update Thu Feb  2 04:19:53 2017 Marwane
//

#include "C4071.hpp"

C4071::C4071(const std::string &name) : AComponent(name, "4071") {

    for (unsigned int i = 0; i < 14; i++) {
        this->pins[i]->state = nts::UNDEFINED;
        this->pins[i]->component = NULL;
    }
    this->outputLinks[1] = std::make_pair(1, 2);
    this->outputLinks[2] = std::make_pair(5, 6);
    this->outputLinks[3] = std::make_pair(8, 9);
    this->outputLinks[4] = std::make_pair(12, 13);

    this->gate = Gate();
    std::cout << "OK" << std::endl;
    exit (0);
}

bool            C4071::pinIndexIsValid(size_t pin_num_this) {
    return pin_num_this > 0 && pin_num_this < 15;
}

nts::Tristate   C4071::Compute(size_t pin_num_this) {
    return pinIndexIsValid(pin_num_this) ?
            this->pins[pin_num_this]->state : nts::Tristate::UNDEFINED;
}

void            C4071::computeAllGates() {
    for (unsigned int i = 1; i < 5; i++) {
        this->pins[i]->state = this->gate.compute("OR",
            this->pins[this->outputLinks[i].first]->component,
            this->pins[this->outputLinks[i].second]->component);
        this->pins[i]->component->setTristate(this->pins[i]->state);
    }
}

void            C4071::computeGate(size_t gate) {
    this->pins[gate]->state = this->gate.compute("OR",
        this->pins[this->outputLinks[gate].first]->component,
        this->pins[this->outputLinks[gate].second]->component);
    this->pins[gate]->component->setTristate(this->pins[gate]->state);
}

// void    C4071::SetTristate(size_t pin_num_this, nts::Tristate _value) {
//     if (pinIndexIsValid(pin_num_this))
//         this->pins[pin_num_this - 1]->SetTristate(1, _value);
// }

void    C4071::SetLink(size_t pin_num_this,
                nts::IComponent &component,
                size_t pin_num_target) {
  if (!pinIndexIsValid(pin_num_this)) {
    throw Error("ERROR : [C4071 COMPONENT | LINK] : pin does not exist.\n");
  }
  
  if (!this->pins[pin_num_this - 1]) {
    this->links[pin_num_this].first = pin_num_this;
    this->links[pin_num_this].second = pin_num_target;
    this->pins[pin_num_this - 1]->component = dynamic_cast<AComponent *>(&component);
    try {
        this->pins[pin_num_this - 1]->component->SetLink(this->links[pin_num_this].second,
                                                        *this, this->links[pin_num_this].first);
    } catch (const std::exception& err) {
        throw err;
    }
  }
}

void    C4071::Dump() const {
    std::cout << "[CHIPSET 4071] :" << std::endl;

    for (unsigned int i = 0; i < 14; i++) {
        std::cout << "Pin [" << i + 1 << "] : ";
        if (this->pins[i] && this->pins[i]->component)
            std::cout << (int)this->pins[i]->component->Compute(1) << std::endl;
        else std::cout << "NULL" << std::endl;
     }
}