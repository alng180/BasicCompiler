#ifndef AST_NODE_H
#define AST_NODE_H

#include <vector>

#include "Token.h"

enum NodeType {
	ROOT, EXPRESSIONROOT,
	// statements
	TYPEDECLARATION, FUNCTIONDECLARATION, VARIABLEDECLARATION,
	BLOCKSTATEMENT, FORSTATEMENT, WHILESTATEMENT, IFSTATEMENT, PRINTSTATEMENT, RETURNSTATEMENT, EXITSTATEMENT, EXPRESSIONSTATEMENT,
	TYPE_DESCRIPTOR, NON_ARRAY_TYPE_DESCRIPTOR, DIMENSION, RECORD_DESCRIPTOR, FIELD_DECLARATION,
	PARAMETER, DIMENSION_WILDCARD, EXPRESSION, TYPE_CAST, FUNCTION_CALL, VARIABLE,
	// expressions
	MULTIPLY, DIVIDE, ADDITION, SUBTRACTION, LEFT_SHIFT, RIGHT_SHIFT,
	LESS_THAN, LESS_THAN_EQUAL, GREATER_THAN, GREATER_THAN_EQUAL, EQUALITY, INEQUALITY, BIT_AND, BIT_XOR,
	BIT_OR, LOG_AND, LOG_OR, EQUALS, UNARY_MINUS, LOG_NOT, BIT_NOT,
	// leaf
	NULL_N, IDENT_N, BYTE_N, INT_N, FLOAT_N, CHAR_LITERAL_N, INT_LITERAL_N, FLOAT_LITERAL_N, BASIC_TYPE, STRING,
	VAR_CONST_N, VAR_STATIC_N, VAR_REF_N, LEAF
	// helper nodes

};

class AbstractSyntaxTreeNode {
public:
	NodeType type;

	AbstractSyntaxTreeNode* parentNode;
	AbstractSyntaxTreeNode* currNode;

	Token token;
	std::vector<AbstractSyntaxTreeNode*> childNodeList;

	AbstractSyntaxTreeNode();
	AbstractSyntaxTreeNode(AbstractSyntaxTreeNode* left, AbstractSyntaxTreeNode* right, NodeType t);

	virtual void addChildNode(AbstractSyntaxTreeNode* childNode);
	virtual std::vector<AbstractSyntaxTreeNode*> getChildNodes();
};

class AbstractSyntaxTreeLeafNode : public AbstractSyntaxTreeNode {
public:
	AbstractSyntaxTreeLeafNode(int &currentToken, std::vector<Token> &tokenList, AbstractSyntaxTreeNode* parent, NodeType t);
};

class AbstractSyntaxTreeExpressionNode : public AbstractSyntaxTreeNode {
public:
	AbstractSyntaxTreeExpressionNode(int &currentToken, std::vector<Token> &tokenList, AbstractSyntaxTreeNode* parent, NodeType t);
	void processExpressionNode(int &currentToken, std::vector<Token> &tokenList);
private:
	AbstractSyntaxTreeNode* parse_equals(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_logicalor(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_logicaland(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_bitwiseor(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_bitwisenot(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_bitwiseand(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_equalityandinequality(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_greaterlessthan(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_leftrightshift(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_plusminus(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_multidivide(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_unaryminus_logicalnot_bitwisenot(int &currToken, std::vector<Token> &tokenList);
	AbstractSyntaxTreeNode* parse_factor(int &currToken, std::vector<Token> &tokenList);
};

class AbstractSyntaxTreeStatementNode : public AbstractSyntaxTreeNode {
public:
	AbstractSyntaxTreeStatementNode(int &currentToken, std::vector<Token> &tokenList, AbstractSyntaxTreeNode* parent);
	AbstractSyntaxTreeStatementNode(int &currentToken, std::vector<Token> &tokenList, AbstractSyntaxTreeNode* parent, NodeType t);
	AbstractSyntaxTreeStatementNode(int &currentToken, std::vector<Token> &tokenList);
	void processStatement(int &currentToken, std::vector<Token> &tokenList);
private:
	void typeDeclaration(int &currentToken, std::vector<Token> &tokenList);
	void functionDeclaration(int &currentToken, std::vector<Token> &tokenList);
	void variableDeclaration(int &currToken, std::vector<Token> &tokenList);
	void blockStatement(int &currToken, std::vector<Token> &tokenList);
	void forStatement(int &currToken, std::vector<Token> &tokenList);
	void whileStatement(int &currToken, std::vector<Token> &tokenList);
	void ifStatement(int &currToken, std::vector<Token> &tokenList);
	void printStatement(int &currToken, std::vector<Token> &tokenList);
	void returnStatement(int &currToken, std::vector<Token> &tokenList);
	void exitStatement(int &currToken, std::vector<Token> &tokenList);
	void expressionStatement(int &currToken, std::vector<Token> &tokenList);
	void typeDescriptor(int &currToken, std::vector<Token> &tokenList);
	void recordDescriptor(int &currToken, std::vector<Token> &tokenList);
	void fieldDeclaration(int &currToken, std::vector<Token> &tokenList);
	void expression(int &currToken, std::vector<Token> &tokenList);
	void typecast(int &currToken, std::vector<Token> &tokenList);
	void functionCall(int &currToken, std::vector<Token> &tokenList);
	void variable(int &currToken, std::vector<Token> &tokenList);
	void stringliteral(int &currToken, std::vector<Token> &tokenList);
	void dimension(int &currToken, std::vector<Token> &tokenList);
	void parameter(int &currToken, std::vector<Token> &tokenList);
	void dimensionWildcard(int &currToken, std::vector<Token> &tokenList);
};




#endif