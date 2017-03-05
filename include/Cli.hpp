//
// Author: Marwane Khsime 
// Date: 2017-02-20 02:22:57 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-20 02:22:57
//

#ifndef _CLI_HPP_
# define _CLI_HPP_

#include <csignal>
#include <cstdlib>
#include <cstdio>

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
#include <sstream>
namespace nts
{
  class   Cli {
   public:
    // Constructor / Destructor
    Cli(const Parser &parser);
    ~Cli();

    // The init initialize the Cli and launch it.
    void        init();

    // Commands avalaible
    void        Exit();
    void        Display();
    void        SetInput();
    void        Simulate();
    void        Loop();
    void        Dump();
    void        Help();
    void        Clear();

   private:
    // Private Methods
    static void        signalHandler(int signum);
    bool                looping;

    // Circuits
    std::map<std::string, AComponent *> circuit;
    std::map<std::string, AComponent *> outputs;
    std::vector<AComponent *> clocks;

    // Functions
    std::map<const std::string, std::function<void ()> > func;

    RegParse *regParse;
  };

}
#endif /* _CLI_HPP_ */