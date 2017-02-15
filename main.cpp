#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>
#include "Parser.hpp"
#include "IComponent.hpp"
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

      nts::IComponent *inp1 = new Input("inp1", 1);
      nts::IComponent *inp2 = new Input("inp2", 0);

      Gate test("AND");
      int res = test.compute(inp1, inp2);
      std::cout << res << std::endl;
      //C4071  chip;
    }
}