//
// Author: Marwane Khsime 
// Date: 2017-02-02 04:37:22 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-02 04:37:22
//

#ifndef _PARSER_HPP_
# define _PARSER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "IParser.hpp"
#include "RegParse.hpp"
#include "Factory.hpp"

// TODO : Pourquoi pas créer une classe CreateTree et ParseTree pour mieux
// segmenter le code et la classe Parser

class   Parser : public nts::IParser {
 public:

  Parser(int  ac, char **av);
  virtual ~Parser();

  nts::t_ast_node *getRoot() const;
  void feed(std::string const& input);
  void parseTree(nts::t_ast_node& root);
  nts::t_ast_node *createTree();

 private:
  // createTree's methods
  void  loadFile_c(char *file_content);
  void  loadComp_values(int ac, char **av);
  void  setDefaultTree();
  nts::t_ast_node  *generateTree();
  void  checkNormFile();
  RegParse  *regParse;
  void  checkTree();

  // parseTree's methods
  bool    basicChecks(const nts::t_ast_node &root);
  bool    doesContainOneCircuit(std::vector<nts::t_ast_node *> &components);
  bool    createCircuit(nts::t_ast_node &root);

 public:

  nts::t_ast_node *treeRoot;
  nts::IComponent *circuit;

  Factory factory;
  std::vector<std::string> availableCircuits;  

  std::vector<std::string> file;
  std::map<std::string, int>  comp_values;
  nts::t_ast_node *strings_t;
  nts::t_ast_node *newlines_t;
  nts::t_ast_node *comps_t;
  nts::t_ast_node *links_t;
  nts::t_ast_node *linksend_t;
  nts::t_ast_node *sections_t;
};

#endif /* _PARSER_HPP_ */