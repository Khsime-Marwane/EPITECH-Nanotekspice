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

int   main(int  ac, char *av[])
{
  if(ac > 1)
    {
      Parser *test2 = new  Parser(ac, av);
      (void)test2;

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


      AComponent *inp1 = new Input("inp1", 1);
      AComponent *inp2 = new Input("inp2", 1);

      Gate test;
      int res = test.compute("AND", inp1, inp2);
      (void)res;
      C4071  chip("4071");
      chip.SetLink(1, *inp1, 1);
      chip.SetLink(1, *inp2, 2);
      std::cout << "pin[1] : " << chip.pins[0]->component->getValue() << std::endl;
      std::cout << "pin[2] : " << chip.pins[1]->component->getValue() << std::endl;
      chip.Compute(3);
      std::cout << "pin[3] : " << chip.pins[2]->state << std::endl;
    }
}