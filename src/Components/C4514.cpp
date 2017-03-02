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

#include "C4514.hpp"

/*
** The component 4514 is composed of 14 pins. It has 4 OR gates
** which works for each of them with two inputs and one output.
*/
C4514::C4514(const std::string &name) : AComponent(name, "chipset") {
  this->_nbPins = 24;
  this->_VSS = 12;
  this->_VDD = 24;

  this->pins = new Pin[this->_nbPins];

  PinType pinsTypeTab[24] = {
          INPUT,    // Pin 1
          INPUT,    // Pin 2
          INPUT,    // Pin 3
          OUTPUT,   // Pin 4
          OUTPUT,   // Pin 5
          OUTPUT,   // Pin 6
          OUTPUT,   // Pin 7
          OUTPUT,   // Pin 8
          OUTPUT,   // Pin 9
          OUTPUT,   // Pin 10
          OUTPUT,   // Pin 11
          IGNORED,  // Pin 12 (VSS)
          OUTPUT,   // Pin 13
          OUTPUT,   // Pin 14
          OUTPUT,   // Pin 15
          OUTPUT,   // Pin 16
          OUTPUT,   // Pin 17
          OUTPUT,   // Pin 18
          OUTPUT,   // Pin 19
          OUTPUT,   // Pin 20
          INPUT,    // Pin 21
          INPUT,    // Pin 22
          INPUT,    // Pin 23
          IGNORED,  // Pin 24 (VDD)
  };

  // Create the pins of the chipset 4514 and set them.
  for (unsigned int i = 0; i < this->_nbPins; i++) {
      this->pins[i].state = nts::Tristate::FALSE;
      this->pins[i].component = NULL;
      this->pins[i].type = pinsTypeTab[i];
      this->links[i] = std::make_pair(0, 0);
    }

  // Output pins with their inputs index.
  this->gateLinks[4] = std::make_pair(0,0);
  this->gateLinks[5] = std::make_pair(0,0);
  this->gateLinks[6] = std::make_pair(0,0);
  this->gateLinks[7] = std::make_pair(0,0);
  this->gateLinks[8] = std::make_pair(0,0);
  this->gateLinks[9] = std::make_pair(0,0);
  this->gateLinks[10] = std::make_pair(0,0);
  this->gateLinks[11] = std::make_pair(0,0);
  this->gateLinks[13] = std::make_pair(0,0);
  this->gateLinks[14] = std::make_pair(0,0);
  this->gateLinks[15] = std::make_pair(0,0);
  this->gateLinks[16] = std::make_pair(0,0);
  this->gateLinks[17] = std::make_pair(0,0);
  this->gateLinks[18] = std::make_pair(0,0);
  this->gateLinks[19] = std::make_pair(0,0);
  this->gateLinks[20] = std::make_pair(0,0);

  initValuesOutputs();
}

/*
** Compute a pin of the component. If the component linked with
** the pin selected is a succesion of computes, all of these components
** will be computed.
*/
nts::Tristate   C4514::Compute(size_t pin_num_this) {

  if (pinIndexIsValid(pin_num_this))
    {
       // If the pin selected is an Output.
      if (this->gateLinks.find(pin_num_this) != this->gateLinks.end() && this->pins[0].state) {

          nts::Tristate A = (valOutputs["A"][pin_num_this - 1]) ? middleInputs["A"] : (nts::Tristate)(!middleInputs["A"]);
          nts::Tristate B = (valOutputs["B"][pin_num_this - 1]) ? middleInputs["B"] : (nts::Tristate)(!middleInputs["B"]);
          nts::Tristate C = (valOutputs["C"][pin_num_this - 1]) ? middleInputs["C"] : (nts::Tristate)(!middleInputs["C"]);
          nts::Tristate D = (valOutputs["D"][pin_num_this - 1]) ? middleInputs["D"] : (nts::Tristate)(!middleInputs["D"]);

//          std::cout << "valueOut : " << this->valOutputs["A"][pin_num_this - 1] << std::endl;
//          std::cout << "A = " << A << " | B = " << B << " | C = " << C << " | D = " << D << std::endl;

          if (this->pins[22].state)
            this->pins[pin_num_this - 1].state = nts::Tristate::FALSE;
          else
            this->pins[pin_num_this - 1].state = gate.compute("NAND", gate.compute("AND", A, B), gate.compute("AND", C, D), this->pins[22].state);
          if (this->pins[pin_num_this - 1].component)
            this->pins[pin_num_this - 1].component->setStateAtPin(this->links[pin_num_this - 1].second,
                                                                  this->pins[pin_num_this - 1].state);
      }

      // If the pin selected is an Input.
      else if (this->pins[pin_num_this - 1].component && this->pins[pin_num_this - 1].type == INPUT) {
        this->pins[pin_num_this - 1].state =
          this->pins[pin_num_this - 1].component->Compute(this->links[pin_num_this - 1].second);
      }
      
      // Return the value of the computed Pin.
      return (this->pins[pin_num_this - 1].state);
    }

  // If the pin doesn't exist, throw an error.
  throw Error("ERROR : [ " + this->_name + " | COMPUTE] : Invalid pin selected.");
  return nts::Tristate::UNDEFINED;
}

/*
** Compute all gates (outputs) of the chipset, if it can be computed.
*/
void            C4514::computeGates() {
  size_t        outputPins[] = {4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20};

  this->pins[0].state = this->pins[0].component->getStateAtPin(1);
  this->pins[22].state = this->pins[22].component->getStateAtPin(1);

  this->middleInputs["A"] = gate.compute("LATCH", this->pins[1].state, this->pins[0].state);
  this->middleInputs["B"] = gate.compute("LATCH", this->pins[2].state, this->pins[0].state);
  this->middleInputs["C"] = gate.compute("LATCH", this->pins[20].state, this->pins[0].state);
  this->middleInputs["D"] = gate.compute("LATCH", this->pins[21].state, this->pins[0].state);

  for (size_t i = 0; i < 16; i++) {
    Compute(outputPins[i]);
  }
}

void  C4514::initValuesOutputs()
{
  std::vector<int> vec1(20);
  std::vector<int> vec2(20);
  std::vector<int> vec3(20);
  std::vector<int> vec4(20);

  int tmp1[20] = {-1, -1, -1, 1, 0, 1, 0, 1, 1, 0, 0, -1, 1, 0, 1, 0, 1, 0, 1, 0};
  int tmp2[20] = {-1, -1, -1, 1, 1, 0, 0, 1, 0, 1, 0, -1, 0, 0, 1, 1, 0, 0, 1, 1};
  int tmp3[20] = {-1, -1, -1, 1, 1, 1, 1, 0, 0, 0, 0, -1, 1, 1, 1, 1, 0, 0, 0, 0};
  int tmp4[20] = {-1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, 1, 1, 1, 1, 1, 1, 1};

  vec1.insert(vec1.begin(), tmp1, tmp1+20);
  vec2.insert(vec2.begin(), tmp2, tmp2+20);
  vec3.insert(vec3.begin(), tmp3, tmp3+20);
  vec4.insert(vec4.begin(), tmp4, tmp4+20);

  this->valOutputs["A"] = vec1;
  this->valOutputs["B"] = vec2;
  this->valOutputs["C"] = vec3;
  this->valOutputs["D"] = vec4;

}