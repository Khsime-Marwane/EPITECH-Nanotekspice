//
// Author: Marwane Khsime 
// Date: 2017-02-20 02:22:21 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-20 02:22:21
//

#include "Cli.hpp"

Cli::Cli(const Parser &parser) {

    this->circuit = parser.getCircuit();
    this->outputs = parser.getOutputs();

    if (this->circuit.size() == 0 ||
        this->outputs.size() == 0)
        throw Error("CLI cannot be setted because the circuit is empty or there is no output.\n");
}

Cli::~Cli() {}

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