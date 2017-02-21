//
// Author: Marwane Khsime 
// Date: 2017-02-02 04:44:16 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-02 04:44:16
//

#include <algorithm>
#include "../include/Parser.hpp"
#include "Errors.hpp"

Parser::Parser(int ac, char **av) {
  this->regParse = new RegParse();
  this->loadFile_c(av[1]);
  this->loadComp_values(ac,av);
  this->setDefaultTree();

  this->availableCircuits = {
    "4001", "4008", "4011", "4013", "4017",
    "4030", "4040", "4069", "4071", "4081",
    "4094", "4514", "4081", "2716"
  };
}

Parser::~Parser() {}

// GETTERS
std::map<std::string, AComponent *> Parser::getCircuit() const {
  return this->circuit;
}

std::vector<AComponent *> Parser::getOutputs() const {
  return this->outputs;
}

nts::t_ast_node *Parser::getRoot() const {
  return this->treeRoot;
}

// FEED Part
void    Parser::feed(std::string const& input) {
  if (!input.empty())
    this->file.push_back(input);
}

// PARSE TREE PART
void    Parser::parseTree(nts::t_ast_node &root) {
  // Basic Checks
  if (basicChecks(root)) return ;
  // Build Circuit and check logic errors
  if (createCircuit(root)) return ;
  if (linkComponents(root)) return ;
}

bool    Parser::basicChecks(const nts::t_ast_node &root) {
  // If the tree's base is correct.
  if (!root.children || root.children->size() != 6) return true;

  // Check if there is at least one component and at least one link.
  if (!root.children->at(2)->children->size() ||
      !root.children->at(3)->children->size() ||
      !root.children->at(4)->children->size()) return true;
  return false;
}

const std::string Parser::getCircuitType(std::vector<nts::t_ast_node *> &components) {
  unsigned int index = 0;
  std::string ret;

  for (std::vector<nts::t_ast_node *>::iterator it = components.begin(); it != components.end(); ++it, ++index) {
    if (std::find(this->availableCircuits.begin(),
                  this->availableCircuits.end(),
                  (*it)->lexeme) != this->availableCircuits.end()) {
        ret = (*it)->lexeme;
        return ret;
      }
  }
  return "";
}

bool    Parser::createCircuit(nts::t_ast_node &root) {

  // For Debug
  std::cout << "[COMPONENTS]" << std::endl;
  for (std::vector<nts::t_ast_node *>::iterator it = root.children->at(2)->children->begin(); it != root.children->at(2)->children->end(); ++it) {
    std::cout << (*it)->lexeme << std::endl;
  }
  std::cout << "\n" << std::endl;
  // *******

  for (std::vector<nts::t_ast_node *>::iterator it = root.children->at(2)->children->begin();
       it != root.children->at(2)->children->end(); ++it) {

        AComponent *newComponent;

        if ((*it)->lexeme == "input") {
          if (this->comp_values.find((*it)->value) == this->comp_values.end()) {
            throw Error("Error on parseTree : Input/Clock '" + (*it)->value + "' isn't set.\n");
          }
          newComponent = this->factory.create((*it)->value, (*it)->lexeme, this->comp_values[(*it)->value]);
          this->circuit.insert(std::pair<std::string, AComponent *>((*it)->value, newComponent));
        } else 
        {
          newComponent = this->factory.create((*it)->value, (*it)->lexeme);
          this->circuit.insert(std::pair<std::string, AComponent *>((*it)->value, newComponent));
          if ((*it)->lexeme == "output") {
            this->outputs.push_back(newComponent);
          }
        }
  }
  return false;
}

bool    Parser::linkComponents(nts::t_ast_node &root) {
  std::vector<nts::t_ast_node *> *Left = root.children->at(3)->children;
  std::vector<nts::t_ast_node *> *Right = root.children->at(4)->children;

  for (size_t i = 0; i < Right->size(); i++) {
    std::cout << Left->at(i)->lexeme << "   ";
    std::cout << Right->at(i)->lexeme << std::endl;
  }
  (void)Right;
  (void)Left;
}

// CREATE TREE PART
nts::t_ast_node *Parser::createTree() {
  nts::t_ast_node *tmp;
  tmp = this->generateTree();
  this->checkTree();
  return (tmp);
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
          if ((pos + 1 == (int)tmp.length()) || checkComp_value(tmp.substr(pos + 1).c_str()))
            throw missingInput("Missing input value on command line");
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
      int chipsets = 0;
      int links = 0;
      for (std::vector<std::string>::iterator it = this->file.begin(); it != this->file.end(); ++it, ++i)
        {
          if (section == ".chipsets:" && (*it).find('#') != 0 && regParse->execComps((*it).c_str()))
            {
              chipsets = 1;
              this->comps_t->children->push_back(regParse->getComps());
            }
          if (section == ".links:" && (*it).find('#') != 0 && regParse->exec((*it).c_str(), regParse->regex_links))
            {
              links = 1;
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
      if (!chipsets || !links)
        {
          std::cout << "chipset : " << chipsets << " | links : " << links << std::endl;
          std::string tmp = (!chipsets) ? "chipset" : "links";
          throw missingSection("No " + tmp + " section");
        }
      return (this->treeRoot);
    }
  return NULL;
}

void  Parser::checkTree()
{
  int same = 0;
  int i = 0;
  for (std::map<std::string, int>::iterator it = this->comp_values.begin(); it != this->comp_values.end(); ++it, ++i)
    {
      int same2 = 0;
      for (std::vector<struct nts::s_ast_node*>::iterator it2 = this->comps_t->children->begin(); it2 != this->comps_t->children->end(); ++it2)
        {
          if (it->first == (*it2)->value && same < regParse->nb_inputs && !same2)
            {
              same++;
              same2 = 1;
            }
          else if (it->first == (*it2)->value  && same2)
              throw sameName("Several components share the same name");
        }
      if (!same2)
        throw unknownInput("Unknown input specified by command line");
    }
  if (i < regParse->nb_inputs || !same)
    throw missingInput("Missing input value on command line");
  this->checkLinks();
}

void  Parser::checkLinks()
{
  for (std::vector<struct nts::s_ast_node*>::iterator it = this->links_t->children->begin(); it != this->links_t->children->end(); ++it)
    {
      int same = 0;
      for (std::vector<struct nts::s_ast_node*>::iterator it2 = this->comps_t->children->begin(); it2 != this->comps_t->children->end(); ++it2)
        {
          if ((*it)->lexeme == (*it2)->value)
            same = 1;
        }
      if (!same)
        throw unknownLink("This link is unknown : " + (*it)->lexeme);
    }
  for (std::vector<struct nts::s_ast_node*>::iterator it = this->linksend_t->children->begin(); it != this->linksend_t->children->end(); ++it)
    {
      int same = 0;
      for (std::vector<struct nts::s_ast_node*>::iterator it2 = this->comps_t->children->begin(); it2 != this->comps_t->children->end(); ++it2)
        {
          if ((*it)->lexeme == (*it2)->value)
            same = 1;
        }
      if (!same)
        throw unknownLink("This link is unknown : " + (*it)->lexeme);
    }
}

bool  Parser::checkComp_value(const char* str)
{
  int i = 0;

  while (str[i])
    i++;
  if (i == 1)
    {
      if (!(str[0] >= '0' && str[0] <= '1'))
        throw incorrectValue("input value is incorrect");
      return (false);
    }
  return (true);
}
