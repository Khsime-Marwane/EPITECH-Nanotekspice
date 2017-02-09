#include <regex>
#include "RegParse.hpp"

RegParse::RegParse()
{
  this->regex_section_chipsets = "(^.chipsets:)";
  this->regex_section_links = "(^.links:)";
  this->regex_links = "(^.*\\:[[:digit:]]*\\s+.*\\:[[:digit:]]*)";
  this->str_comment = "(#.*)";
  this->nb_inputs = 0;

  this->generateAllowedVec();
}

void  RegParse::generateAllowedVec()
{
  this->allowed_chips.push_back("(^4001\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4008\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4011\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4013\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4017\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4030\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4030\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4040\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4069\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4071\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4081\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4094\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4514\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^4801\\s+[_[:alnum:]]+)");
  this->allowed_chips.push_back("(^2716\\s+[_[:alnum:]]+)");

  this->allowed_comps.push_back("(^input\\s+[_[:alnum:]]+)");
  this->allowed_comps.push_back("(^clock\\s+[_[:alnum:]]+)");
  this->allowed_comps.push_back("(^true\\s+[_[:alnum:]]+)");
  this->allowed_comps.push_back("(^false\\s+[_[:alnum:]]+)");
  this->allowed_comps.push_back("(^output\\s+[_[:alnum:]]+)");
}

bool RegParse::exec(const char* str_request, const char* str_regex)
{
  std::smatch m;
  std::string tmp(str_request);
  if (std::regex_match(tmp, m, std::regex(str_regex)))
    {
      std::smatch::iterator it = m.begin();
      this->str_match = *it;
      return (true);
    }
  return (false);
}

bool RegParse::execComps(const char* str)
{
  int state = 0;

  for (std::vector<std::string>::iterator it = this->allowed_comps.begin(); it != this->allowed_comps.end(); ++it)
    if (this->exec(str, (*it).c_str()))
      state = 1;
  for (std::vector<std::string>::iterator it = this->allowed_chips.begin(); it != this->allowed_chips.end(); ++it)
    if (this->exec(str, (*it).c_str()))
      state = 1;
  if (state)
    return (true);
  return (false);
}

nts::t_ast_node* RegParse::getComps()
{
  int pos = this->str_match.find('\t');

  nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
  tmp->type = nts::ASTNodeType::COMPONENT;
  tmp->lexeme = this->str_match.substr(0, pos);
  pos = this->str_match.rfind('\t');
  tmp->value = this->str_match.substr(pos + 1);
  tmp->value.erase(std::remove(tmp->value.begin(), tmp->value.end(), ' '), tmp->value.end());
  if (tmp->lexeme == "input")
    this->nb_inputs++;
  return (tmp);
}


nts::t_ast_node* RegParse::getLinks()
{
  int pos = this->str_match.find('\t');

  nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
  tmp->type = nts::ASTNodeType::LINK;
  tmp->type = nts::ASTNodeType::LINK_END;
  std::string tmp_str(this->str_match.substr(0, pos));
  tmp->lexeme = tmp_str.substr(0, tmp_str.find(':'));
  tmp->value = tmp_str.substr(tmp_str.find(':') + 1);
  return (tmp);
}

nts::t_ast_node* RegParse::getLinks_end()
{
  int pos = this->str_match.rfind('\t');

  nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
  std::string tmp_str = this->str_match.substr(pos + 1, this->str_match.length());
  tmp->lexeme = tmp_str.substr(0, tmp_str.find(':'));
  tmp->value = tmp_str.substr(tmp_str.find(':') + 1);
  tmp->value.erase(std::remove(tmp->value.begin(), tmp->value.end(), ' '), tmp->value.end());
  return (tmp);
}

nts::t_ast_node*  RegParse::getSection(std::string &section)
{
  nts::t_ast_node  *tmp = new nts::t_ast_node(NULL);
  tmp->type = nts::ASTNodeType::SECTION;
  section = this->str_match;
  tmp->value = this->str_match;
  return (tmp);
}

nts::t_ast_node*  RegParse::getString()
{
  nts::t_ast_node *tmp = new nts::t_ast_node(NULL);
  tmp->type = nts::ASTNodeType::STRING;
  tmp->value = this->str_match.substr(this->str_match.find('#'));
  return (tmp);
}

bool  RegParse::checkLine(const char* str)
{
  if (this->execComps(str) || this->exec(str, this->regex_section_chipsets) || this->exec(str, this->regex_section_links)
      || this->exec(str, this->regex_links) || this->exec(str, this->str_comment) || strlen(str) == 0)
    return (true);
  return (false);
}