//
// Author: Marwane Khsime 
// Date: 2017-02-02 04:44:16 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-02 04:44:16
//

#include "Parser.hpp"

Parser::Parser(char *file_content) {

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

  // Create the tree's root
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
          if (section == ".chipsets:")
            {
              if ((pos = (*it).find('\t')) > 1 || (pos = (*it).find(' ')) > 1)
                {
                  nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
                  tmp->type = nts::ASTNodeType::COMPONENT;
                  tmp->lexeme = (*it).substr(0, pos);
                  pos = (*it).rfind('\t');
                  tmp->value = (*it).substr(pos + 1);
                  this->comps_t->children->push_back(tmp);
                }
            } else if (section == ".links:")
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

// int main() {
//     Parser  p;

//     std::cout << p.getRoot()->lexeme << std::endl;
//     std::cout << (int)p.getRoot()->type << std::endl;
//     std::cout << p.getRoot()->value << std::endl;
//     std::cout << p.getRoot()->children->size() << std::endl;
//     (void)p;
//     return 0;
// }