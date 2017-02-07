//
// Author: Marwane Khsime 
// Date: 2017-02-02 04:44:16 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-02 04:44:16
//

#include <algorithm>
#include "Parser.hpp"
#include "Errors.hpp"

Parser::Parser(int ac, char **av) {
  this->regParse = new RegParse();
  this->loadFile_c(av[1]);
  this->loadComp_values(ac,av);
  this->setDefaultTree();
}

Parser::~Parser() {}

void    Parser::feed(std::string const& input) {
  if (!input.empty())
    this->file.push_back(input);
}

void    Parser::parseTree(nts::t_ast_node &root) {
  (void)root;
}

nts::t_ast_node *Parser::createTree() {
  nts::t_ast_node *tmp;
  tmp = this->generateTree();
  return (tmp);
}

nts::t_ast_node *Parser::getRoot() const {
  return this->treeRoot;
}

void  Parser::loadFile_c(char *file_content)
{
  std::string tmp(file_content);
  if (((int)tmp.find(".nts") <= 0) && (tmp.find(".nts") != (tmp.length() - 4)))
    throw badExtensionFile("Bad extension of file");

  std::ifstream file_c(file_content);
  std::string   line;
  if (file_c.is_open())
    {
      while (getline(file_c, line))
        {
          int pos_end = line.length();
          if (line.find('#') > 0 && line.find('#') <= line.length())
            {
              pos_end = line.find('#');
              this->file.push_back(line.substr(0, pos_end));
              this->feed(line.substr(pos_end));
            }
          else
            this->file.push_back(line);
        }
    }
  file_c.close();
}

void  Parser::loadComp_values(int ac, char **av)
{
  if (ac > 2)
    {
      for (int i = 2; i < ac; ++i)
        {
          std::string tmp(av[i]);
          int pos = tmp.find('=');
          this->comp_values.insert(std::pair<std::string, int>(tmp.substr(0 ,pos), atoi(tmp.substr(pos + 1).c_str())));
        }
    }
}

void  Parser::setDefaultTree()
{
  this->treeRoot = new nts::t_ast_node(new std::vector<nts::t_ast_node*>);
  this->treeRoot->lexeme = "Default";
  this->treeRoot->type = nts::ASTNodeType::DEFAULT;
  this->treeRoot->value = "Default";

  for (int i = 0; i < 6; i++) {
      this->treeRoot->children->push_back(new nts::t_ast_node(new std::vector<nts::t_ast_node*>));
      this->treeRoot->children->at(i)->type = (nts::ASTNodeType)i;
    }

  this->strings_t = this->treeRoot->children->at(0);
  this->newlines_t = this->treeRoot->children->at(1);
  this->comps_t = this->treeRoot->children->at(2);
  this->links_t = this->treeRoot->children->at(3);
  this->linksend_t = this->treeRoot->children->at(4);
  this->sections_t = this->treeRoot->children->at(5);
}

nts::t_ast_node  *Parser::generateTree()
{
  if (this->file.size() > 0) {
      std::string section;
      int i = 1;
      for (std::vector<std::string>::iterator it = this->file.begin(); it != this->file.end(); ++it, ++i)
        {
          if (section == ".chipsets:" && (*it).find('#') != 0 && regParse->execComps((*it).c_str()))
            this->comps_t->children->push_back(regParse->getComps());
          if (section == ".links:" && (*it).find('#') != 0 && regParse->exec((*it).c_str(), regParse->regex_links))
            {
              this->links_t->children->push_back(regParse->getLinks());
              this->linksend_t->children->push_back(regParse->getLinks_end());
            }
          if ((*it).length() == 0)
            {
              nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
              tmp->type = nts::ASTNodeType::NEWLINE;
              this->newlines_t->children->push_back(tmp);
            }
          if (regParse->exec((*it).c_str(), regParse->regex_section_chipsets) || regParse->exec((*it).c_str(), regParse->regex_section_links))
            this->sections_t->children->push_back(regParse->getSection(section));
          if (regParse->exec((*it).c_str(), regParse->str_comment))
            this->strings_t->children->push_back(regParse->getString());
          if (!regParse->checkLine((*it).c_str()))
            throw incorrectLine("Line : " + std::to_string(i) + " is incorrect");
        }
      return (this->treeRoot);
    }
  return NULL;
}