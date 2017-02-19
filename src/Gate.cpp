#include "Gate.hpp"

Gate::Gate()
{
  // Create the map of functions. It's useful to call properly the associated function of the type
  // sent as parameter to the compute function.
  this->computes["AND"] = std::bind(&Gate::computeAND, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["OR"] = std::bind(&Gate::computeOR, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["XOR"] = std::bind(&Gate::computeXOR, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["NAND"] = std::bind(&Gate::computeAND, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["NOR"] = std::bind(&Gate::computeOR, this, std::placeholders::_1, std::placeholders::_2);
  this->computes["XNOR"] = std::bind(&Gate::computeXOR, this, std::placeholders::_1, std::placeholders::_2);
}

/*
** The compute function takes as parameter the type of the door which we want to use,
** and the values of the inputs. In the case of the door NO, the second value is set
** to undefined because we don't use it. If among the values needed, one or more is
** UNDEFINED, or if the _type is unknown, it return UNDEFINED.
*/
nts::Tristate Gate::compute(std::string _type, nts::Tristate v1, nts::Tristate v2)
{
  this->_not = (_type == "NAND" || _type == "NOR" || _type == "XNOR") ? true : false;

  if (_type == "NOT" && v1 != nts::Tristate::UNDEFINED)
    return (computeNO(v1));
  if ((v1 == nts::Tristate::UNDEFINED) || (v2 == nts::Tristate::UNDEFINED))
    return (nts::Tristate::UNDEFINED);
  return (computes.find(_type)->second(v1, v2));
}

/*
**   a | b | s
** +-----------
** | 0 | 0 | 0
** | 0 | 1 | 0
** | 1 | 0 | 0
** | 1 | 1 | 1
*/
nts::Tristate Gate::computeAND(nts::Tristate v1, nts::Tristate v2)
{
  if (_not)
    return ((nts::Tristate)(!(v1 & v2)));
  return ((nts::Tristate)(v1 & v2));
}

/*
**   a | b | s
** +-----------
** | 0 | 0 | 0
** | 0 | 1 | 1
** | 1 | 0 | 1
** | 1 | 1 | 1
*/
nts::Tristate Gate::computeOR(nts::Tristate v1, nts::Tristate v2)
{
  if (_not)
    return ((nts::Tristate)(!(v1 || v2)));
  return ((nts::Tristate)(v1 || v2));
}

/*
**   a | b | s
** +-----------
** | 0 | 0 | 0
** | 0 | 1 | 1
** | 1 | 0 | 1
** | 1 | 1 | 0
*/
nts::Tristate Gate::computeXOR(nts::Tristate v1, nts::Tristate v2)
{
  if (_not)
    return ((nts::Tristate)(!(v1 ^ v2)));
  return ((nts::Tristate)(v1 ^ v2));
}

/*
**   a | s
** +-----------
** | 0 | 1
** | 1 | 0
*/
nts::Tristate Gate::computeNO(nts::Tristate v)
{
  return ((nts::Tristate)(!v));
}