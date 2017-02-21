//
// Author: Marwane Khsime 
// Date: 2017-02-20 02:22:21 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-20 02:22:21
//

#include "Cli.hpp"

Cli::Cli(const Parser &parser) {

  this->regParse = new RegParse();
  this->circuit = parser.getCircuit();
  this->outputs = parser.getOutputs();

  this->func["exit"] = std::bind(&Cli::Exit, this);
  this->func["display"] = std::bind(&Cli::Display, this);
  this->func["simulate"] = std::bind(&Cli::Simulate, this);
  this->func["dump"] = std::bind(&Cli::Dump, this);

  if (this->circuit.size() == 0 || this->outputs.size() == 0)
    throw Error("CLI cannot be setted because the circuit is empty or there is no output.\n");
  else
    this->init();
}

Cli::~Cli() {}

void    Cli::init()
{
  std::cout << std::endl << "=== CLI ===" << std::endl;
  std::string cmd;
  std::cout << "> ";
  while (getline(std::cin, cmd))
    {
      if (this->func.find(cmd) != this->func.end())
        this->func[cmd]();
      else if (this->regParse->exec(cmd.c_str(), regParse->cli_value))
          {
            std::pair<std::string, int> tmp = this->regParse->getInpValue();
            if (this->circuit.find(tmp.first) != this->circuit.end())
              this->circuit[tmp.first]->setValue(tmp.second);
          }
      std::cout << "> ";
    }
}

void    Cli::Exit() {
    exit(EXIT_SUCCESS);
}

void    Cli::Display() {
    std::vector<AComponent *>::iterator it;

    for (it = outputs.begin(); it != outputs.end(); it++) {
             (*it)->Dump();
    }
}

void    Cli::SetInput(const std::string &input) {
    (void)input;
}

void    Cli::Simulate() {
    std::map<std::string, AComponent *>::iterator it;

    for (it = this->circuit.begin(); it != this->circuit.end(); it++)
    {
        it->second->computeGates();
    }
}

void    Cli::Loop() {

}

void    Cli::Dump() {
    std::map<std::string, AComponent *>::iterator it;

    std::cout << "\n === DUMP === \n" << std::endl;
    for (it = this->circuit.begin(); it != this->circuit.end(); it++)
    {
        it->second->Dump();
        std::cout << std::endl;
    }
}