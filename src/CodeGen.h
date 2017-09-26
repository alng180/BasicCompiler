#ifndef CODEGEN_H
#define CODEGEN_H

#include "AbstractSyntaxTree.h"
#include "AbstractSyntaxTree_Node.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

class CodeGenerator {
public:
	std::unordered_map<std::string, int> intTable;
	int intCount = 0;
	std::unordered_map<std::string, float> floatTable;
	int floatCount = 0;

	CodeGenerator(std::string outputfile, AbstractSyntaxTree ast);
	void readNodes(AbstractSyntaxTreeNode* node);

private:
	std::ofstream output;

	void variableDeclaration(AbstractSyntaxTreeNode* node);
	void generateExpression(AbstractSyntaxTreeNode* node, bool &intFlag);

	void addition(AbstractSyntaxTreeNode* node, bool &intFlag);
	void subtraction(AbstractSyntaxTreeNode* node, bool &intFlag);
	void multiplication(AbstractSyntaxTreeNode* node, bool &intFlag);
	void division(AbstractSyntaxTreeNode* node, bool &intFlag);

	void checkChildExpressionNode(AbstractSyntaxTreeNode* node, bool &intFlag);
	void saveLiteral(double lit, bool isFloat);
	void outputVariables();
};

#endif