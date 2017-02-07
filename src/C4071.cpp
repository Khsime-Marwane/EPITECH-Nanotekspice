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

#include "../include/C4071.hpp"

C4071::C4071() {
    for (unsigned int i = 0; i < 14; i++) this->pins[i] = NULL;

    // Assign Functions to mapPins
    // Assign Inputs Functions
    this->mapPins[1] = std::bind(&C4071::computeInput, this, std::placeholders::_1);
    this->mapPins[2] = std::bind(&C4071::computeInput, this, std::placeholders::_1);
    this->mapPins[5] = std::bind(&C4071::computeInput, this, std::placeholders::_1);
    this->mapPins[6] = std::bind(&C4071::computeInput, this, std::placeholders::_1);
    this->mapPins[8] = std::bind(&C4071::computeInput, this, std::placeholders::_1);
    this->mapPins[9] = std::bind(&C4071::computeInput, this, std::placeholders::_1);
    this->mapPins[12] = std::bind(&C4071::computeInput, this, std::placeholders::_1);
    this->mapPins[13] = std::bind(&C4071::computeInput, this, std::placeholders::_1);

    // // Assign Outputs Functions and create their pairs links
    this->mapPins[3] = std::bind(&C4071::computeOutput, this, std::placeholders::_1);
    this->outputLinks[3] = std::make_pair(1, 2);
    this->mapPins[4] = std::bind(&C4071::computeOutput, this, std::placeholders::_1);
    this->outputLinks[4] = std::make_pair(5, 6);
    this->mapPins[10] = std::bind(&C4071::computeOutput, this, std::placeholders::_1);
    this->outputLinks[10] = std::make_pair(8, 9);
    this->mapPins[11] = std::bind(&C4071::computeOutput, this, std::placeholders::_1);
    this->outputLinks[11] = std::make_pair(12, 13);

    // VSS and VDD, unused
    this->mapPins[7] = std::bind(&C4071::computeV, this, std::placeholders::_1);
    this->mapPins[14] = std::bind(&C4071::computeV, this, std::placeholders::_1);
}

C4071::~C4071() {

}

nts::Tristate   C4071::OR_Function(nts::Tristate first,
                                   nts::Tristate second) const {
    return ((nts::Tristate)((int)first || (int)second));
}

nts::Tristate   C4071::Compute(size_t pin_num_this) {
    return mapPins[pin_num_this](pin_num_this);
}

nts::Tristate   C4071::computeInput(size_t pin_num_this) {
    if ((pin_num_this == 3 || pin_num_this == 4 || pin_num_this == 10 || pin_num_this == 11 ||
         pin_num_this == 14 || pin_num_this == 7 || pin_num_this > 14))
        throw Error("[C4071 ComputeInput] : Invalid Input Pin selected.\n");
    return this->pins[pin_num_this]->Compute();
}

nts::Tristate   C4071::computeOutput(size_t pin_num_this) {
    if (!(pin_num_this == 3 || pin_num_this == 4 || pin_num_this == 10 || pin_num_this == 11))
        throw Error("[C4071 ComputeOutput] : Invalid Output Pin selected.\n");
    OR_Function(this->pins[this->outputLinks[pin_num_this].first]->Compute(),
                this->pins[this->outputLinks[pin_num_this].second]->Compute());
    return nts::Tristate::UNDEFINED;
}

nts::Tristate   C4071::computeV(size_t pin_num_this) {
    std::string err = "Impossible to compute a ";

    err += pin_num_this == 7 ? "VSS.\n" : "VDD.\n";
    throw Error(err);
    return nts::Tristate::UNDEFINED;
}

void    C4071::SetLink(size_t pin_num_this,
                nts::IComponent &component,
                size_t pin_num_target) {
  if (pin_num_this != 1) {
    throw Error("ERROR : [C4071 COMPONENT | LINK] : pin does not exist.\n");
  }
  if (!this->pins[pin_num_this]) {
    this->links[pin_num_this].first = pin_num_this;
    this->links[pin_num_this].second = pin_num_target;
    this->pins[pin_num_this] = &component;
    try {
        this->pins[pin_num_this]->SetLink(this->links[pin_num_this].second, *this, this->links[pin_num_this].first);
    } catch (const std::exception& err) {
        throw err;
    }
  }
}

void    C4071::Dump() const {
    std::cout << "[CHIPSET 4071] :" << std::endl;
    for (unsigned int i = 0; i < 14; i++) {
        std::cout << "Pin [" << i + 1 << "] : ";
        if (this->pins[i]) std::cout << (int)this->pins[i]->Compute(1) << std::endl;
        else std::cout << "NULL" << std::endl;
     }
}