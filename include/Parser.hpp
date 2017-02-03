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
#include "IParser.hpp"

class   Parser : public nts::IParser {
 public:

  Parser(int  ac, char **av);
  virtual ~Parser();

  nts::t_ast_node *getRoot() const;
  void feed(std::string const& input);
  void parseTree(nts::t_ast_node& root);
  nts::t_ast_node *createTree();

 private:
  void  loadFile_c(char *file_content);
  void  loadComp_values(int ac, char **av);
  void  setDefaultTree();

 public:
  nts::t_ast_node *treeRoot;
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