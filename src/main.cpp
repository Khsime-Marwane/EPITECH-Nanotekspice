#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include "Parser.hpp"
#include "../include/AComponent.hpp"
#include "Gate.hpp"
#include "RegParse.hpp"

int   main(int  ac, char *av[])
{
  if(ac > 1)
    {
      // Parser *test2 = new  Parser(ac, av);
      // (void)test2;

/*
      for (std::vector<std::string>::iterator it = test->file.begin(); it != test->file.end(); ++it)
        std::cout << *it << std::endl;
*/

  /*    test->createTree();

      std::cout << "STRINGS nodes :" << std::endl;
      for (std::vector<struct nts::s_ast_node*>::iterator it = test->strings_t->children->begin(); it != test->strings_t->children->end(); ++it)
        std::cout << "value = " << (*it)->value << std::endl;

      std::cout << "COMPONONENTS nodes :" << std::endl;
      for (std::vector<struct nts::s_ast_node*>::iterator it = test->comps_t->children->begin(); it != test->comps_t->children->end(); ++it)
        std::cout << "type = " << (*it)->lexeme << " | name = " << (*it)->value << std::endl;

      std::cout << "LINKS nodes : " << std::endl;
      int i = 0;
      for (std::vector<struct nts::s_ast_node*>::iterator it = test->links_t->children->begin(); it != test->links_t->children->end(); ++it)
        std::cout << "name = " << (*it)->lexeme << " | pin = " << (*it)->value << " | id = " << i++ << std::endl;

      std::cout << "LINKSEND nodes : " << std::endl;
      i = 0;
       for (std::vector<struct nts::s_ast_node*>::iterator it = test->linksend_t->children->begin(); it != test->linksend_t->children->end(); ++it)
        std::cout << "name = " << (*it)->lexeme << " | pin = " << (*it)->value << " | id = " << i++ << std::endl;*/


      AComponent *inp1 = new Input("input 1", 0);
      AComponent *inp2 = new Input("input 2", 1);
      AComponent *out = new Output("output 1");
      AComponent *out2 = new Output("output 2");
      AComponent *or1 = new C4071("OR");
      AComponent *or2 = new C4071("OR2");

      or1->SetLink(1, *inp1, 1);
      or1->SetLink(2, *inp2, 1);
      or1->SetLink(3, *out, 1);

      or2->SetLink(1, *or1, 2);
      or2->SetLink(2, *or1, 3);
      or2->SetLink(3, *out2, 1);

      or1->computeGates();
      or1->Dump();
      std::cout << "\n\n";
      or2->Compute(3);
      or2->Dump();
      // std::cout << "\n\n____________________\n\n" << std::endl;

      (void)inp1;
      (void)inp2;
      (void)out;
      (void)or1;
      (void)or2;
    }
}