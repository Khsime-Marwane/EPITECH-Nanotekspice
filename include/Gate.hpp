#ifndef GATE_H_
  #define GATE_H_

#include <cstdlib>
#include "AComponent.hpp"

/*
** The Gate class contain all gates methods.
*/
class Gate
{

 public:
  Gate();
  ~Gate(){}
  nts::Tristate compute(std::string, nts::Tristate , nts::Tristate = nts::Tristate::UNDEFINED);

 private:
  bool        _not;

  std::map<std::string, std::function<nts::Tristate (nts::Tristate, nts::Tristate)> > computes;
  nts::Tristate computeOR(nts::Tristate, nts::Tristate);
  nts::Tristate computeAND(nts::Tristate, nts::Tristate);
  nts::Tristate computeXOR(nts::Tristate, nts::Tristate);
  nts::Tristate computeNO(nts::Tristate);
};

#endif