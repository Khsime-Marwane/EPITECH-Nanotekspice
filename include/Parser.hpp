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

#define STRINGS this->treeRoot->children->at(0)
#define NEWLINES this->treeRoot->children->at(1)
#define COMPONENTS this->treeRoot->children->at(2)
#define LINKS this->treeRoot->children->at(3)
#define LINKSEND this->treeRoot->children->at(4)
#define SECTIONS this->treeRoot->children->at(5)

class   Parser : public nts::IParser {
public:

Parser(char *file_content);
virtual ~Parser();

nts::t_ast_node *getRoot() const;
void feed(std::string const& input);
void parseTree(nts::t_ast_node& root);
nts::t_ast_node *createTree();


 public:
nts::t_ast_node *treeRoot;
std::vector<std::string> file;
};

#endif /* _PARSER_HPP_ */