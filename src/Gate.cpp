#include <iostream>
#include "Gate.hpp"

Gate::Gate(std::string type)
{
  this->_type = type;
  this->computes["AND"] = std::bind(&Gate::computeAND, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["OR"] = std::bind(&Gate::computeOR, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["XOR"] = std::bind(&Gate::computeXOR, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["NAND"] = std::bind(&Gate::computeAND, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["NOR"] = std::bind(&Gate::computeOR, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["XNOR"] = std::bind(&Gate::computeXOR, this, std::placeholders::_1, std::placeholders::_2);

  if (_type == "NAND" || _type == "NOR" || _type == "XNOR")
    this->_not = true;
  else
    this->_not = false;
}

nts::Tristate Gate::compute(AComponent* input1, AComponent* input2)
{
  if ((input1 && input1->getValue() == nts::Tristate::UNDEFINED) || (input2 && input2->getValue() == nts::Tristate::UNDEFINED))
    return (nts::Tristate::UNDEFINED);
  if (input2 != NULL && _type != "NOT")
    return (computes.find(_type)->second(input1, input2));
  return (computeNO(input1));
}

nts::Tristate Gate::computeAND(AComponent* &input1, AComponent* &input2)
{
  int v1 = input1->getValue();
  int v2 = input2->getValue();

  if (_not)
    return ((nts::Tristate)(!(v1 & v2)));
  return ((nts::Tristate)(v1 & v2));
}

nts::Tristate Gate::computeOR(AComponent* &input1, AComponent* &input2)
{
  int v1 = input1->getValue();
  int v2 = input2->getValue();

  if (_not)
    return ((nts::Tristate)(!(v1 | v2)));
  return ((nts::Tristate)(v1 | v2));
}

nts::Tristate Gate::computeXOR(AComponent* &input1, AComponent* &input2)
{
  int v1 = input1->getValue();
  int v2 = input2->getValue();

  if (_not)
    return ((nts::Tristate)(!(v1 ^ v2)));
  return ((nts::Tristate)(v1 ^ v2));
}

nts::Tristate Gate::computeNO(AComponent* &input)
{
  return ((nts::Tristate)(!input->getValue()));
}