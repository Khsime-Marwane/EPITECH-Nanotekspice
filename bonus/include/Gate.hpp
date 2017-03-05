#ifndef GATE_H_
  #define GATE_H_

#include <cstdlib>
#include "AComponent.hpp"

/*
** The Gate class contain all gates methods.
*/

namespace nts
{
  class Gate
  {

   public:
    Gate();
    ~Gate(){}
    nts::Tristate compute(std::string, nts::Tristate , nts::Tristate = nts::Tristate::UNDEFINED, nts::Tristate = nts::Tristate::UNDEFINED);
    nts::Tristate getTmpQ();
    nts::Tristate getTmpQ2();

   private:
    bool          _not;
    nts::Tristate  tmpQ;
    nts::Tristate  tmpQ2;

    std::map<std::string, std::function<nts::Tristate (nts::Tristate, nts::Tristate)> > basiComputes;
    std::map<std::string, std::function<nts::Tristate (nts::Tristate, nts::Tristate, nts::Tristate)> > AdvanceComputes;
    nts::Tristate computeOR(nts::Tristate, nts::Tristate);
    nts::Tristate computeAND(nts::Tristate, nts::Tristate);
    nts::Tristate computeXOR(nts::Tristate, nts::Tristate);
    nts::Tristate computeLATCH(nts::Tristate, nts::Tristate);
    nts::Tristate computeNO(nts::Tristate);
    nts::Tristate computeSUM(nts::Tristate, nts::Tristate, nts::Tristate);
    nts::Tristate computeSUMC(nts::Tristate, nts::Tristate, nts::Tristate);
    nts::Tristate computeAND2(nts::Tristate, nts::Tristate, nts::Tristate);
  };
}

#endif