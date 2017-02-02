//
// Author: Marwane Khsime 
// Date: 2017-02-02 04:37:22 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-02 04:37:22
//

#ifndef _PARSER_HPP_
# define _PARSER_HPP_

#include "IParser.hpp"

class   Parser : public nts::IParser {
public:

Parser();
virtual ~Parser();

void feed(std::string const& input);
void parseTree(nts::t_ast_node& root);
nts::t_ast_node *createTree();


private:

};

#endif /* _PARSER_HPP_ */