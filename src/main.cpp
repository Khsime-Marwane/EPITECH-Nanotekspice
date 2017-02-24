#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>

#include "Output.hpp"

int   main(int  ac, char *av[])
{
  if(ac > 1)
    {
      AComponent  *out = new Output("Acid rain");
      // Parser  parser(ac, av);

      // parser.createTree();
      // parser.parseTree(*parser.getRoot());

      // Cli     cli(parser);

      // cli.init();
      (void)out;
    }
  (void)ac;
  (void)av;
  return (0);
}