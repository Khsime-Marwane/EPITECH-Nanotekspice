#ifndef GATE_H_
  #define GATE_H_

#include <map>
#include <cstdlib>
#include <functional>
#include <utility>
#include "IComponent.hpp"

class Gate
{
  std::string _type;
  bool        _not;
  std::map<std::string, std::function<nts::Tristate (nts::IComponent* &, nts::IComponent* &)> > computes;

 public:
  Gate(std::string);
  ~Gate(){}
  nts::Tristate compute(nts::IComponent* , nts::IComponent* = NULL);

 private:
  nts::Tristate computeOR(nts::IComponent* &, nts::IComponent* &);
  nts::Tristate computeAND(nts::IComponent* &, nts::IComponent* &);
  nts::Tristate computeXOR(nts::IComponent* &, nts::IComponent* &);
  nts::Tristate computeNO(nts::IComponent* &);
};
#endif