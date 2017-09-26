#include "CodeGen.h"

// constructor
CodeGenerator::CodeGenerator(std::string outputfile, AbstractSyntaxTree ast) {
	output.open(outputfile);

	AbstractSyntaxTreeNode* root = ast.root;

	std::vector<AbstractSyntaxTreeNode*> list = root->childNodeList;
	for (int i = 0; i < list.size(); i++) {
		AbstractSyntaxTreeNode* node = list.at(i);
		readNodes(node);
	}

	// exit program
	output << "load0" << std::endl;
	output << "exit" << std::endl;

	outputVariables();
	output.close();
}

// process a node
void CodeGenerator::readNodes(AbstractSyntaxTreeNode* node) {
	switch (node->type) {
		case(NodeType::VARIABLEDECLARATION): {
			variableDeclaration(node);
			break;
		}
		case(NodeType::EXPRESSIONROOT):
		case(NodeType::EXPRESSIONSTATEMENT): {
			bool intFlag = false;
			AbstractSyntaxTreeNode* exprRoot = node->childNodeList.at(0);	// ignore expression root node
			AbstractSyntaxTreeNode* exprNode = exprRoot->childNodeList.at(0);
			generateExpression(exprNode, intFlag);
			break;
		}
		case(NodeType::PRINTSTATEMENT): {
			bool intFlag = false;
			AbstractSyntaxTreeNode* exprRoot = node->childNodeList.at(0);	// ignore expression root node
			AbstractSyntaxTreeNode* exprNode = exprRoot->childNodeList.at(0);
			generateExpression(exprNode, intFlag);

			if (intFlag) {
				output << "print_int" << std::endl;
			}
			else {
				output << "print_float" << std::endl;
			}
			break;
		}
		default:
		{
			// nothing
		}
	}
}

// variable declaration
void CodeGenerator::variableDeclaration(AbstractSyntaxTreeNode* node) {
	// to do
}

// generate expression text
void CodeGenerator::generateExpression(AbstractSyntaxTreeNode* node, bool &intFlag) {
	NodeType nt = node->type;

	switch (nt) {
		case(NodeType::ADDITION): {
			addition(node, intFlag);
			break;
		}
		case(NodeType::SUBTRACTION): {
			subtraction(node, intFlag);
			break;
		}
		case(NodeType::MULTIPLY): {
			multiplication(node, intFlag);
			break;
		}
		case(NodeType::DIVIDE): {
			division(node, intFlag);
			break;
		}
		default:
		{
		}
	}
}

// addition
void CodeGenerator::addition(AbstractSyntaxTreeNode* node, bool &intFlag) {
	std::vector<AbstractSyntaxTreeNode*> list = node->childNodeList;

	bool intFlagLeft = false;
	bool intFlagRight = false;

	AbstractSyntaxTreeNode* left = list.at(0);
	AbstractSyntaxTreeNode* right = list.at(1);

	checkChildExpressionNode(left, intFlagLeft);
	checkChildExpressionNode(right, intFlagRight);

	if (intFlagLeft && !intFlagRight) output << "to_int" << std::endl;
	if (intFlagRight && !intFlagLeft) {
		output << "load1" << std::endl;
		output << "pickf" << std::endl;
		output << "to_int" << std::endl;
	}

	intFlag = intFlagLeft || intFlagRight;

	std::string add = (intFlag) ? "add" : "add_f";
	output << add << std::endl;
}

// subtraction
void CodeGenerator::subtraction(AbstractSyntaxTreeNode* node, bool &intFlag) {
	std::vector<AbstractSyntaxTreeNode*> list = node->childNodeList;

	bool intFlagLeft = false;
	bool intFlagRight = false;

	AbstractSyntaxTreeNode* left = list.at(0);
	AbstractSyntaxTreeNode* right = list.at(1);

	checkChildExpressionNode(left, intFlagLeft);
	checkChildExpressionNode(right, intFlagRight);

	if (intFlagLeft && !intFlagRight) output << "to_int" << std::endl;
	if (intFlagRight && !intFlagLeft) {
		output << "load1" << std::endl;
		output << "pickf" << std::endl;
		output << "to_int" << std::endl;
	}

	intFlag = intFlagLeft || intFlagRight;

	std::string sub = (intFlag) ? "sub" : "sub_f";
	output << sub << std::endl;
}

// multiplication
void CodeGenerator::multiplication(AbstractSyntaxTreeNode* node, bool &intFlag) {
	std::vector<AbstractSyntaxTreeNode*> list = node->childNodeList;

	bool intFlagLeft = false;
	bool intFlagRight = false;

	AbstractSyntaxTreeNode* left = list.at(0);
	AbstractSyntaxTreeNode* right = list.at(1);

	checkChildExpressionNode(left, intFlagLeft);
	checkChildExpressionNode(right, intFlagRight);

	if (intFlagLeft && !intFlagRight) output << "to_int" << std::endl;
	if (intFlagRight && !intFlagLeft) {
		output << "load1" << std::endl;
		output << "pickf" << std::endl;
		output << "to_int" << std::endl;
	}

	intFlag = intFlagLeft || intFlagRight;

	std::string mul = (intFlag) ? "mul" : "mul_f";
	output << mul << std::endl;
}

// division
void CodeGenerator::division(AbstractSyntaxTreeNode* node, bool &intFlag) {
	std::vector<AbstractSyntaxTreeNode*> list = node->childNodeList;

	bool intFlagLeft = false;
	bool intFlagRight = false;

	AbstractSyntaxTreeNode* left = list.at(0);
	AbstractSyntaxTreeNode* right = list.at(1);
	
	checkChildExpressionNode(left, intFlagLeft);
	checkChildExpressionNode(right, intFlagRight);

	if (intFlagLeft && !intFlagRight) output << "to_int" << std::endl;
	if (intFlagRight && !intFlagLeft) {
		output << "load1" << std::endl;
		output << "pickf" << std::endl;
		output << "to_int" << std::endl;
		output << "load1" << std::endl;
		output << "pick" << std::endl;
	}

	intFlag = intFlagLeft || intFlagRight;

	std::string div = (intFlag) ? "div" : "div_f";
	output << div << std::endl;
}

// check a node's child nodes
void CodeGenerator::checkChildExpressionNode(AbstractSyntaxTreeNode* node, bool &intFlag) {
	switch (node->type) {
		case(NodeType::INT_LITERAL_N):
		case(NodeType::INT_N):
		{
			std::string s1 = "load_label I" + std::to_string(intCount);
			std::string s2 = "load_mem_int";
			saveLiteral(node->token.value, false);
			output << s1 << std::endl;
			output << s2 << std::endl;
			intFlag = true;
			break;
		}
		case(NodeType::FLOAT_LITERAL_N):
		case(NodeType::FLOAT_N):
		{
			std::string s1 = "load_label F" + std::to_string(floatCount);
			std::string s2 = "load_mem_float";
			saveLiteral(node->token.value, true);
			output << s1 << std::endl;
			output << s2 << std::endl;
			intFlag = false;
			break;
		}
		case(NodeType::BYTE_N):
		{
			// not handled
			break;
		}
		case(NodeType::ADDITION):
		case(NodeType::SUBTRACTION):
		case(NodeType::MULTIPLY):
		case(NodeType::DIVIDE):
		{
			generateExpression(node, intFlag);
			break;
		}
		default:
		{
			// error
		}
	}
}

// save the int/float literal into the float/int tables
void CodeGenerator::saveLiteral(double lit, bool isFloat) {
	if (isFloat) {
		floatTable.emplace("F" + std::to_string(floatCount), (float)lit);
		floatCount++;
	}
	else {
		intTable.emplace("I" + std::to_string(intCount), (int)lit);
		intCount++;
	}
}

// output the contents in float/int tables to the end of the ir/output
void CodeGenerator::outputVariables() {
	for (int i = 0; i < intCount; i++) {
		int temp = intTable.at("I" + std::to_string(i));

		output << "I" << std::to_string(i) << ":" << std::endl;
		output << "int_literal " << temp << std::endl;
	}

	for (int i = 0; i < floatCount; i++) {
		float temp = floatTable.at("F" + std::to_string(i));

		output << "F" << std::to_string(i) << ":" << std::endl;
		output << "float_literal " << temp << std::endl;
	}
}