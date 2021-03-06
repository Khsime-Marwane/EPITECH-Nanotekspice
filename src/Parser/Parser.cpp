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

nts::Parser::Parser(int ac, char **av) {
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

nts::Parser::~Parser() {}

// GETTERS
std::map<std::string, nts::AComponent *> nts::Parser::getCircuit() const {
  return this->circuit;
}

std::map<std::string, nts::AComponent *> nts::Parser::getOutputs() const {
  return this->outputs;
}

std::vector<nts::AComponent *> nts::Parser::getClocks() const {
  return this->clocks;
}

nts::t_ast_node *nts::Parser::getRoot() const {
  return this->treeRoot;
}

// FEED Part
void    nts::Parser::feed(std::string const& input) {
  if (!input.empty())
    this->file.push_back(input);
}

// PARSE TREE PART
void    nts::Parser::parseTree(nts::t_ast_node &root) {

  // Basic Checks
  basicChecks(root);
  // Build Circuit and check logic errors
  createCircuit(root);
  // Link Components
  linkComponents(root);
  // Check if all Output Components are linked.
  checkLinksInCircuit();
}

void    nts::Parser::basicChecks(const nts::t_ast_node &root) {
  // If the tree's base is correct.
  if (!root.children || root.children->size() != 6)
      throw Error("Can't parse the tree, the root is incomplete.");

  // Check if there is at least one component and at least one link.
  if (!root.children->at(2)->children->size() ||
      !root.children->at(3)->children->size() ||
      !root.children->at(4)->children->size())
      throw Error("Can't parse the tree, there is no components and/or links.");
}

const std::string nts::Parser::getCircuitType(std::vector<nts::t_ast_node *> &components) {
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

void    nts::Parser::createCircuit(nts::t_ast_node &root) {

  for (std::vector<nts::t_ast_node *>::iterator it = root.children->at(2)->children->begin();
       it != root.children->at(2)->children->end(); ++it) {

        AComponent *newComponent;

        if ((*it)->lexeme == "input" || (*it)->lexeme == "clock") {
          if (this->comp_values.find((*it)->value) == this->comp_values.end()) {
            throw Error("Error on parseTree : Input/Clock '" + (*it)->value + "' isn't set.");
          }
          newComponent = this->factory.create((*it)->value, (*it)->lexeme, this->comp_values[(*it)->value]);
          this->circuit.insert(std::pair<std::string, nts::AComponent *>((*it)->value, newComponent));
          if ((*it)->lexeme == "clock")
            this->clocks.push_back(newComponent);
        } else 
        {
          newComponent = this->factory.create((*it)->value, (*it)->lexeme);
          this->circuit.insert(std::pair<std::string, nts::AComponent *>((*it)->value, newComponent));
          if ((*it)->lexeme == "output") {
            this->outputs.insert(std::pair<std::string, nts::AComponent *>((*it)->value, newComponent));
          }
        }
  }
}

void    nts::Parser::linkComponents(nts::t_ast_node &root) {
  std::vector<nts::t_ast_node *> *Left = root.children->at(3)->children;
  std::vector<nts::t_ast_node *> *Right = root.children->at(4)->children;

  for (size_t i = 0; i < Right->size(); i++) {
      size_t pin_num_this = std::stoi(Right->at(i)->value);
      size_t pin_num_target = std::stoi(Left->at(i)->value);

      // Check if one of the components linked is unknown.
      if (this->circuit.find(Right->at(i)->lexeme) == this->circuit.end())
        throw Error("'" + Right->at(i)->lexeme + "' doesn't exist.");
      if (this->circuit.find(Left->at(i)->lexeme) == this->circuit.end())
        throw Error("'" + Left->at(i)->lexeme + "' doesn't exist.");

      // Check if we are linking the same component and at the same pin
      if (pin_num_this == pin_num_target &&
          this->circuit[Right->at(i)->lexeme] == this->circuit[Left->at(i)->lexeme])
            throw Error("Trying to link the component '" + Right->at(i)->lexeme +
                        "' with itself at the same pin.");
      this->circuit[Right->at(i)->lexeme]->SetLink(pin_num_this,
                                                  *this->circuit[Left->at(i)->lexeme],
                                                  pin_num_target);
    }
}

void      nts::Parser::checkLinksInCircuit() const {
  std::string errMsg;
  bool    isError = false;

  for (std::map<std::string, nts::AComponent *>::const_iterator it = circuit.begin(); it != circuit.end(); it++) {
    if (it->second->getType() == "output" && !it->second->pins[0].component) {
      if (!isError) errMsg += "Some Outputs are not linked :\n";
      errMsg += ("Output '" + it->second->getName() + "' is not linked to anything.\n");
      isError = true;
    }
  }

  if (isError)
    throw Error(errMsg);
}

// CREATE TREE PART
nts::t_ast_node *nts::Parser::createTree() {
  nts::t_ast_node *tmp;
  tmp = this->generateTree();
  this->checkTree();
  return (tmp);
}

void  nts::Parser::loadFile_c(char *file_content)
{
  std::string tmp(file_content);
  if (((int)tmp.find(".nts") <= 0) && (tmp.find(".nts") != (tmp.length() - 4)))
    throw badExtensionFile("Bad extension of file.");

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
  else
    throw Error("This file doesn't exist.");
  file_c.close();
}

void  nts::Parser::loadComp_values(int ac, char **av)
{
  if (ac > 2)
    {
      for (int i = 2; i < ac; ++i)
        {
          std::string tmp(av[i]);
          int pos = tmp.find('=');
          if ((pos + 1 == (int)tmp.length()) || checkComp_value(tmp.substr(pos + 1).c_str()))
            throw missingInput("Missing input value on command line.");
          this->comp_values.insert(std::pair<std::string, int>(tmp.substr(0 ,pos), atoi(tmp.substr(pos + 1).c_str())));
        }
    }
}

void  nts::Parser::setDefaultTree()
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

nts::t_ast_node  *nts::Parser::generateTree()
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
              continue;
            }
          if (section == ".links:" && (*it).find('#') != 0 && regParse->exec((*it).c_str(), regParse->regex_links))
            {
              links = 1;
              this->links_t->children->push_back(regParse->getLinks());
              this->linksend_t->children->push_back(regParse->getLinks_end());
              continue;
            }
          if ((*it).length() == 0)
            {
              nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
              tmp->type = nts::ASTNodeType::NEWLINE;
              this->newlines_t->children->push_back(tmp);
              continue;
            }
          if (regParse->exec((*it).c_str(), regParse->regex_section_chipsets) || regParse->exec((*it).c_str(), regParse->regex_section_links))
            {
              this->sections_t->children->push_back(regParse->getSection(section));
              continue;
            }
          if (regParse->exec((*it).c_str(), regParse->str_comment))
            {
              this->strings_t->children->push_back(regParse->getString());
              continue;
            }
          if (!regParse->checkLine((*it).c_str()))
            throw incorrectLine("Line : " + std::to_string(i) + " is incorrect.");
        }
      if (!chipsets || !links)
        {
          std::cout << "chipset : " << chipsets << " | links : " << links << std::endl;
          std::string tmp = (!chipsets) ? "chipset" : "links";
          throw missingSection("No " + tmp + " section.");
        }
      return (this->treeRoot);
    }
  return NULL;
}

void  nts::Parser::checkTree()
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
          else if (it->first == (*it2)->value && same2)
              throw sameName("Several components share the same name.");
        }
      if (!same2)
        throw unknownInput("Unknown input specified by command line.");
    }
  if (i < regParse->nb_inputs)
    throw missingInput("Missing input value on command line.");
  this->checkLinks();
}

void  nts::Parser::checkLinks()
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
        throw unknownLink("component '" + (*it)->lexeme + "' is unknown.");
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
        throw unknownLink("component '" + (*it)->lexeme + "' is unknown.");
    }
}

bool  nts::Parser::checkComp_value(const char* str)
{
  int i = 0;

  while (str[i])
    i++;
  if (i == 1)
    {
      if (!(str[0] >= '0' && str[0] <= '1'))
        throw incorrectValue("input value is incorrect.");
      return (false);
    }
  return (true);
}
