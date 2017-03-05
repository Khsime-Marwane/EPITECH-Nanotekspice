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

#include "C4801.hpp"

/*
** The component 4801 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4801::C4801(const std::string &name) : AComponent(name, "chipset") {
  this->_nbPins = 24;
  this->_VSS = 12;
  this->_VDD = 24;

  this->pins = new Pin[this->_nbPins];

  PinType pinsTypeTab[this->_nbPins] = {
    INPUT,    // Pin 1 A7
    INPUT,    // Pin 2 A6
    INPUT,    // Pin 3 A5
    INPUT,    // Pin 4 A4
    INPUT,    // Pin 5 A3
    INPUT,    // Pin 6 A2
    INPUT,    // Pin 7 A1
    INPUT,    // Pin 8 A0
    _HYBRID_, // Pin 9 DQ0
    _HYBRID_, // Pin 10 DQ1
    _HYBRID_, // Pin 11 DQ2
    IGNORED,  // Pin 12 (VSS)
    _HYBRID_, // Pin 13 DQ3
    _HYBRID_, // Pin 14 DQ4
    _HYBRID_, // Pin 15 DQ5
    _HYBRID_, // Pin 16 DQ6
    _HYBRID_, // Pin 17 DQ7
    INPUT,    // Pin 18 Chipset Enable
    INPUT,    // Pin 19 No Connection
    INPUT,    // Pin 20 Output Enable
    INPUT,    // Pin 21 Write Enable
    INPUT,    // Pin 22 A8
    INPUT,    // Pin 23 A9
    IGNORED   // Pin 24 (VCC)
  };

  // Create the pins of the chipset 4801 and set them.
  for (unsigned int i = 0; i < this->_nbPins; i++) {
      this->pins[i].state = nts::Tristate::FALSE;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
  }

  // Memset the memory
  for (size_t i = 0; i < _SIZE_; i++) {
    this->memory[i] = 0;
  }
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4801::Compute(size_t pin_num_this) {
  if (pinIndexIsValid(pin_num_this))
      return this->pins[pin_num_this - 1].state;

  // If the pin doesn't exist, throw an error.
  throw Error("ERROR : [ " + this->_name + " | COMPUTE] : Invalid pin selected.");
  return nts::Tristate::UNDEFINED;
}

void            C4801::setValueOnOutputs(int value) {
  size_t dqOutputs[8] = { 8, 9, 10, 12, 13, 14, 15, 16 };

  for (int i = 7; i >= 0; i--) {
    this->pins[dqOutputs[i]].state = (nts::Tristate)(value % 2);
    value /= 2;
  }
}

int             C4801::getValueFromOutputs() {
  size_t        dqOutputs[8] = { 16, 15, 14, 13, 12, 10, 9, 8 };
  int           value = 0;

  for (int i = 0, mult = 1; i < 8; i++, mult *= 2) {
    value += this->pins[dqOutputs[i]].state * mult;
  }

  return value;
}

/*
** Compute all gates (outputs) of the chipset, if it can be computed.
*/
void            C4801::computeGates() {

  refreshInputs();  
  // Check if the chipset is enable.
  if ((!this->pins[_CHIP_ENABLE_].state) == nts::Tristate::FALSE) {

    // If we are in Write Mode
    if ((!this->pins[_WRITE_ENABLE_].state) == nts::Tristate::FALSE) {
      refreshOutputs();
      int pos = (getY() * _COLUMNS_) + getX();
      this->memory[pos] = getValueFromOutputs();
    }
    
    // If we are in Read Mode
    else if ((!this->pins[_OUTPUT_ENABLE_].state == nts::Tristate::FALSE)) {
      int pos = (getY() * _COLUMNS_) + getX();

      setValueOnOutputs(this->memory[pos]);
    }

    else  // We reset the outputs
      resetOutputs();
  }
  
  else  // Reset the Outputs
    resetOutputs();
}

void            C4801::refreshInputs() {
  size_t        inputs_to_refresh[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 22, 21, 20, 19, 18, 17 };

  for (size_t i = 0; i < 14; i++) {
    if (this->pins[inputs_to_refresh[i]].component) {
      this->pins[inputs_to_refresh[i]].state =
      this->pins[inputs_to_refresh[i]].component->Compute(this->links[inputs_to_refresh[i]].second);
    }
  }
}

void            C4801::refreshOutputs() {
  size_t        outputs_to_refresh[8] = { 8, 9, 10, 16, 15, 14, 13, 12 };

  for (size_t i = 0; i < 8; i++) {
    if (this->pins[outputs_to_refresh[i]].component) {
      this->pins[outputs_to_refresh[i]].state =
      this->pins[outputs_to_refresh[i]].component->Compute(this->links[outputs_to_refresh[i]].second);
    }
  }
}

void            C4801::resetOutputs() {
  this->pins[8].state = nts::Tristate::UNDEFINED;
  this->pins[9].state = nts::Tristate::UNDEFINED;
  this->pins[10].state = nts::Tristate::UNDEFINED;
  this->pins[16].state = nts::Tristate::UNDEFINED;
  this->pins[15].state = nts::Tristate::UNDEFINED;
  this->pins[14].state = nts::Tristate::UNDEFINED;
  this->pins[13].state = nts::Tristate::UNDEFINED;
  this->pins[12].state = nts::Tristate::UNDEFINED;
}

size_t             C4801::getY() const {
  int value = 0;

  value += 1 * this->pins[6].state;   // A1
  value += 2 * this->pins[1].state;   // A6
  value += 4 * this->pins[21].state;  // A8
  return value;
}

size_t             C4801::getX() const {
  int           value = 0;

  value += 1 * this->pins[7].state;    // A0
  value += 2 * this->pins[5].state;    // A2
  value += 4 * this->pins[4].state;    // A3
  value += 8 * this->pins[3].state;    // A4
  value += 16 * this->pins[0].state;    // A7
  value += 32 * this->pins[22].state;   // A9
  value += 64 * this->pins[2].state;    // A5
  return value;
}