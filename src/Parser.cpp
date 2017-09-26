#include "Parser.h"

// constructor
Parser::Parser() {
	tree = AbstractSyntaxTree();
}

// constructor
Parser::Parser(std::vector<Token> tokenList) {
	tree = AbstractSyntaxTree(tokenList);
	tree.buildSyntaxTree();
}

// returns the ast
AbstractSyntaxTree Parser::getAST() {
	return tree;
}