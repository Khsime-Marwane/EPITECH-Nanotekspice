#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>

#include "Cli.hpp"

void  Helper() {
  std::cout <<
  "Usage:     ./nanotekspice [FILE] [INPUTS]" << std::endl << std::endl
  << "| CLI COMMANDS :" << std::endl
  << "|__ display\t\tprints on stdout the value of all outputs sorted by name." << std::endl
  << "|__ simulate\t\tlaunches a simulation." << std::endl
  << "|__ loop\t\tlaunches simulations without prompting again until SIGINT." << std::endl
  << "|__ dump\t\tcall the Dump method of every component." << std::endl
  << "|__ [INPUT]=[VALUE]\tchanges the value of an input. (Not a clock)" << std::endl
  << "|__ exit\t\tcloses the program." << std::endl
  << "|__ help\t\tdisplay this help." << std::endl;
}

int   nanotekspice(int  ac, char *av[])
{
  if(ac > 1) {
    // Try to launch the init.
    try {
      Parser  parser(ac, av);

      parser.createTree();
      parser.parseTree(*parser.getRoot());

      Cli     cli(parser);

      cli.init();
    }

    catch(std::exception const &err) {
      std::cerr << "Error : " << err.what() << std::endl;
      return EXIT_FAILURE;
    }
  }
  
  // Print the usage
  else {
    Helper();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int   main(int argc, char *argv[]) {
  if (nanotekspice(argc, argv) == EXIT_FAILURE)
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}