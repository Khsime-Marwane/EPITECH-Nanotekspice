#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <algorithm>
#include <vector>
#include "IParser.hpp"

#ifndef REGPARSE_H_
  #define REGPARSE_H_

class RegParse {
 private:
  std::string str_match;
  void  generateAllowedVec();

 public:
  RegParse();
  ~RegParse(){}
  bool exec(const char* str_request, const char* str_regex);
  bool execComps(const char* str);
  bool checkLine(const char* str);
  nts::t_ast_node *getComps();
  nts::t_ast_node *getLinks();
  nts::t_ast_node *getLinks_end();
  nts::t_ast_node *getSection(std::string&);
  nts::t_ast_node *getString();
  std::pair<std::string, int> getInpValue();

  int nb_inputs;
  const char *regex_section_chipsets;
  const char *regex_section_links;
  const char *regex_links;
  const char *str_comment;
  const char *cli_value;
  std::vector<std::string>  allowed_chips;
  std::vector<std::string>  allowed_comps;
};

#endif