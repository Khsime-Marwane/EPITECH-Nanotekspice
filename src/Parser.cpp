//
// Author: Marwane Khsime 
// Date: 2017-02-02 04:44:16 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-02-02 04:44:16
//

#include "../include/Parser.hpp"

Parser::Parser() : nts::IParser() {

    // Create the tree's root
    this->treeRoot = new nts::t_ast_node(new std::vector<nts::t_ast_node* >);
    this->treeRoot->lexeme = "Default";
    this->treeRoot->type = nts::ASTNodeType::DEFAULT;
    this->treeRoot->value = "Default";

    for (int i = 0; i < 6; i++) {
        this->treeRoot->children->push_back(new nts::t_ast_node(NULL));
        this->treeRoot->children->at(i)->type = (nts::ASTNodeType)i;
    }
}

Parser::~Parser() {

}

void    Parser::feed(std::string const& input) {
    (void)input;
}

void    Parser::parseTree(nts::t_ast_node &root) {
    (void)root;
}

nts::t_ast_node *Parser::createTree() {
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