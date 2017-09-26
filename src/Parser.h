#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "Token.h"
#include "AbstractSyntaxTree.h"

class Parser {
public:
	Parser();
	Parser(std::vector<Token> tokenList);

	AbstractSyntaxTree getAST();
private:
	AbstractSyntaxTree tree;
};

#endif