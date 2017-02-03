//
// Author: Marwane Khsime 
// Date: 2017-02-02 04:44:16 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-02 04:44:16
//

#include "Parser.hpp"
#include "Errors.hpp"
#include <algorithm>

Parser::Parser(int ac, char **av) {

  // Get file content
  this->loadFile_c(av[1]);

  // Get components value
  this->loadComp_values(ac,av);

  // Create the tree's root
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
  if (this->file.size() > 0){
      int pos;
      std::string section;
      for (std::vector<std::string>::iterator it = this->file.begin(); it != this->file.end(); ++it)
        {
          if (section == ".chipsets:" && (*it).find('#') != 0)
            {
              if ((pos = (*it).find('\t')) > 1 || (pos = (*it).find(' ')) > 1)
                {
                  nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
                  tmp->type = nts::ASTNodeType::COMPONENT;
                  tmp->lexeme = (*it).substr(0, pos);
                  pos = (*it).rfind('\t');
                  tmp->value = (*it).substr(pos + 1);
                  tmp->value.erase(std::remove(tmp->value.begin(), tmp->value.end(), ' '), tmp->value.end());
                  this->comps_t->children->push_back(tmp);
                }
            } else if (section == ".links:" && (*it).find('#') != 0)
              {
                if ((pos = (*it).find('\t')) > 1 || (pos = (*it).find(' ')) > 1)
                  {
                    nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
                    nts::t_ast_node  *tmp2 = new nts::t_ast_node(NULL);
                    tmp->type = nts::ASTNodeType::LINK;
                    tmp->type = nts::ASTNodeType::LINK_END;
                    std::string tmp_str((*it).substr(0, pos));
                    tmp->lexeme = tmp_str.substr(0, tmp_str.find(':'));
                    tmp->value = tmp_str.substr(tmp_str.find(':') + 1);
                    this->links_t->children->push_back(tmp);
                    pos = (*it).rfind('\t');
                    tmp_str = (*it).substr(pos + 1, (*it).length());
                    tmp2->lexeme = tmp_str.substr(0, tmp_str.find(':'));
                    tmp2->value = tmp_str.substr(tmp_str.find(':') + 1);
                    tmp2->value.erase(std::remove(tmp2->value.begin(), tmp2->value.end(), ' '), tmp2->value.end());
                    this->linksend_t->children->push_back(tmp2);
                  }
              }
          if ((*it).length() == 0)
            {
              nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
              tmp->type = nts::ASTNodeType::NEWLINE;
              this->newlines_t->children->push_back(tmp);
            }
          if ((*it).find('.') == 0)
            {
              nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
              tmp->type = nts::ASTNodeType::SECTION;
              section = (*it);
              tmp->value = (*it);
              this->sections_t->children->push_back(tmp);
            }
          if ((*it).find('#') <= (*it).length())
            {
              nts::t_ast_node *tmp = new nts::t_ast_node(NULL);
              tmp->type = nts::ASTNodeType::STRING;
              tmp->value = (*it).substr((*it).find('#'));
              this->strings_t->children->push_back(tmp);
            }
        }
      return (this->treeRoot);
    }
  return NULL;
}

nts::t_ast_node *Parser::getRoot() const {
  return this->treeRoot;
}

void  Parser::loadFile_c(char *file_content)
{
  try {
      std::string tmp(file_content);
      if (((int)tmp.find(".nts") <= 0) && (tmp.find(".nts") != (tmp.length() - 4)))
        throw badExtensionFile("Bad extension of file", 0);
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
    } catch (badExtensionFile const &e) {
      std::cerr << "Error : " << e.what() << std::endl;
      std::abort();
    }
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