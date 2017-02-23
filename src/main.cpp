#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>

#include "Parser.hpp"
#include "AComponent.hpp"
#include "Gate.hpp"
#include "RegParse.hpp"
#include "Cli.hpp"

int   main(int  ac, char *av[])
{
  if(ac > 1)
    {
      Parser  parser(ac, av);

      parser.createTree();
      parser.parseTree(*parser.getRoot());

      Cli     cli(parser);

      cli.init();
      std::cout << "fin du programme" << std::endl;
    }
  return (0);
}