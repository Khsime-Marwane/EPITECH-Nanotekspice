//
// Author: Marwane Khsime 
// Date: 2017-02-20 02:22:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-20 02:22:57
//

#ifndef _CLI_HPP_
# define _CLI_HPP_

#include "Parser.hpp"


/*
**  The CLI (command line interface) allow to use 
**  few functions to manipulate the circuit :
**
**  • exit - closes the program.
**
**  • display - It prints on stdout the value of all outputs sorted by name.
**
**  • <input Name>=<value> - It changes the value of an input. (Not a clock)
**
**  • simulate - It launches a simulation.
**
**  • loop - Simulate without prompting again until SIGINT.
**
**  • dump - Call the Dump method of every IComponent
**
*/
class   Cli {
public:
    // Constructor / Destructor
    Cli(const Parser &parser);
    ~Cli();

    // Commands avalaible
    void    Exit();
    void    Display();
    void    SetInput(const std::string &name);
    void    Simulate();
    void    Loop();
    void    Dump();

private:
    // Circuits
    std::map<std::string, AComponent *> circuit;
    std::vector<AComponent *> outputs;
};

#endif /* _CLI_HPP_ */