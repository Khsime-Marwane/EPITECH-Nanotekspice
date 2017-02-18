#include "Gate.hpp"

Gate::Gate()
{
  this->computes["AND"] = std::bind(&Gate::computeAND, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["OR"] = std::bind(&Gate::computeOR, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["XOR"] = std::bind(&Gate::computeXOR, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["NAND"] = std::bind(&Gate::computeAND, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["NOR"] = std::bind(&Gate::computeOR, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["XNOR"] = std::bind(&Gate::computeXOR, this, std::placeholders::_1, std::placeholders::_2);
}

nts::Tristate Gate::compute(std::string _type, AComponent* input1, AComponent* input2)
{
  if ((input1 && input1->getState() == nts::Tristate::UNDEFINED) || (input2 && input2->getState() == nts::Tristate::UNDEFINED))
    return (nts::Tristate::UNDEFINED);
  this->_not = (_type == "NAND" || _type == "NOR" || _type == "XNOR") ? true : false;
  if (input2 != NULL && _type != "NOT")
    return (computes.find(_type)->second(input1, input2));
  return (computeNO(input1));
}

nts::Tristate Gate::computeAND(AComponent* &input1, AComponent* &input2)
{
  int v1 = input1->getState();
  int v2 = input2->getState();

  if (_not)
    return ((nts::Tristate)(!(v1 & v2)));
  return ((nts::Tristate)(v1 & v2));
}

nts::Tristate Gate::computeOR(AComponent* &input1, AComponent* &input2)
{
  int v1 = input1->getState();
  int v2 = input2->getState();

  if (_not)
    return ((nts::Tristate)(!(v1 || v2)));
  return ((nts::Tristate)(v1 || v2));
}

nts::Tristate Gate::computeXOR(AComponent* &input1, AComponent* &input2)
{
  int v1 = input1->getState();
  int v2 = input2->getState();

  if (_not)
    return ((nts::Tristate)(!(v1 ^ v2)));
  return ((nts::Tristate)(v1 ^ v2));
}

nts::Tristate Gate::computeNO(AComponent* &input)
{
  return ((nts::Tristate)(!input->getState()));
}