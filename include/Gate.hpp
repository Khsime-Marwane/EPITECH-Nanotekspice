#ifndef GATE_H_
  #define GATE_H_

#include <cstdlib>
#include "AComponent.hpp"

class Gate
{

 public:
  Gate();
  ~Gate(){}
  nts::Tristate compute(std::string, AComponent* , AComponent* = NULL);

 private:
  bool        _not;

  std::map<std::string, std::function<nts::Tristate (AComponent* &, AComponent* &)> > computes;
  nts::Tristate computeOR(AComponent* &, AComponent* &);
  nts::Tristate computeAND(AComponent* &, AComponent* &);
  nts::Tristate computeXOR(AComponent* &, AComponent* &);
  nts::Tristate computeNO(AComponent* &);
};

#endif