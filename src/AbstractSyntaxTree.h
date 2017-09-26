#ifndef AST_H
#define AST_H

#include "AbstractSyntaxTree_Node.h"

#include "SymbolTable.h"
#include "TypeTable.h"

class AbstractSyntaxTree {
public:
	AbstractSyntaxTreeNode* root;
	std::vector<Token> tokens;

	SymbolTable symTable;
	TypeTable typeTable;

	AbstractSyntaxTree() {
		tokens = std::vector<Token>();
	}

	AbstractSyntaxTree(std::vector<Token> tokenList) {
		tokens = tokenList;
		SymbolTable symTable;
		TypeTable typeTable;
	}

	void buildSyntaxTree() {
		int currentToken = 0;
		root = new AbstractSyntaxTreeStatementNode(currentToken, tokens);
	}
};

#endif