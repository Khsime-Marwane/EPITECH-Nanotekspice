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

//      cli.Dump();

      // AComponent *inp1 = new Input("input 1", 0);
      // AComponent *inp2 = new Input("input 2", 1);
      // AComponent *out = new Output("output 1");
      // AComponent *out2 = new Output("output 2");
      // AComponent *or1 = new C4071("OR");
      // AComponent *or2 = new C4071("OR2");

      // or1->SetLink(1, *inp1, 1);
      // or1->SetLink(2, *inp2, 1);
      // or1->SetLink(3, *out, 1);

      // or2->SetLink(1, *or1, 2);
      // or2->SetLink(2, *or1, 3);
      // or2->SetLink(3, *out2, 1);

      // or1->computeGates();
      // or1->Dump();
      // std::cout << "\n\n";
      // or2->Compute(3);
      // or2->Dump();
      // std::cout << "\n\n____________________\n\n" << std::endl;

      // (void)inp1;
      // (void)inp2;
      // (void)out;
      // (void)or1;
      // (void)or2;
    }
  return (0);
}