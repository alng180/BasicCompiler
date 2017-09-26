#ifndef TEST_H
#define TEST_H

#include "Token.h"
#include "AbstractSyntaxTree.h"
#include "AbstractSyntaxTree_Node.h"

#include <iostream>

class Test {
public:
	void outputTokenContents(std::vector<Token> tokenList) {
		for (int i = 0; i < tokenList.size(); i++) {
			Token currToken = tokenList.at(i);

			std::cout << "[" << currToken.lineNumber << "," << currToken.columnNumber + 1 << "] ";

			std::string tokenText = "";
			std::string auxText = "";
			bool outputAux = false;

			switch (currToken.tokenType) {
			case(IDENTIFIER):
			{
				std::cout << "IDENTIFIER" << " (" << currToken.stringval << ")" << std::endl;
				break;
			}
			case(STRING_LIT):
			{
				std::cout << "STRING_LITERAL" << " (" << currToken.stringval << ")" << std::endl;
				break;
			}
			case(CHAR_LIT):
			{
				std::cout << "CHAR_LITERAL" << " (" << currToken.stringval << ")" << std::endl;
				break;
			}
			case(BYTE_LIT):
			{
				std::cout << "BYTE_LITERAL" << " (" << currToken.stringval << ")" << std::endl;
				break;
			}
			case(FLOAT_LIT):
			{
				std::cout << "FLOAT_LITERAL" << " (" << currToken.value << ")" << std::endl;
				break;
			}
			case(INT_LIT):
			{
				std::cout << "INT_LITERAL" << " (" << currToken.value << ")" << std::endl;
				break;
			}
			case(BYTE):
			{
				std::cout << "BYTE_SYMBOL" << std::endl;
				break;
			}
			case(CONST):
			{
				std::cout << "CONST_SYMBOL" << std::endl;
				break;
			}
			case(ELSE):
			{
				std::cout << "ELSE_SYMBOL" << std::endl;
				break;
			}
			case(END):
			{
				std::cout << "END_SYMBOL" << std::endl;
				break;
			}
			case(EXIT):
			{
				std::cout << "EXIT_SYMBOL" << std::endl;
				break;
			}
			case(FLOAT):
			{
				std::cout << "FLOAT_SYMBOL" << std::endl;
				break;
			}
			case(FOR):
			{
				std::cout << "FOR_SYMBOL" << std::endl;
				break;
			}
			case(FUNCTION):
			{
				std::cout << "FUNCTION_SYMBOL" << std::endl;
				break;
			}
			case(IF):
			{
				std::cout << "IF_SYMBOL" << std::endl;
				break;
			}
			case(INT32):
			{
				std::cout << "INT32_SYMBOL" << std::endl;
				break;
			}
			case(PRINT):
			{
				std::cout << "PRINT_SYMBOL" << std::endl;
				break;
			}
			case(RECORD):
			{
				std::cout << "RECORD_SYMBOL" << std::endl;
				break;
			}
			case(REF):
			{
				std::cout << "REF_SYMBOL" << std::endl;
				break;
			}
			case(RETURN):
			{
				std::cout << "RETURN_SYMBOL" << std::endl;
				break;
			}
			case(STATIC):
			{
				std::cout << "STATIC_SYMBOL" << std::endl;
				break;
			}
			case(TYPETOKEN):
			{
				std::cout << "TYPE_SYMBOL" << std::endl;
				break;
			}
			case(VAR):
			{
				std::cout << "VAR_SYMBOL" << std::endl;
				break;
			}
			case(WHILE):
			{
				std::cout << "WHILE_SYMBOL" << std::endl;
				break;
			}
			case(EQUAL):
			{
				std::cout << "EQUAL" << std::endl;
				break;
			}
			case(NOT):
			{
				std::cout << "NOT" << std::endl;
				break;
			}
			case(TILDE):
			{
				std::cout << "TILDE" << std::endl;
				break;
			}
			case(DASH):
			{
				std::cout << "DASH" << std::endl;
				break;
			}
			case(PLUS):
			{
				std::cout << "PLUS" << std::endl;
				break;
			}
			case(ASTERIX):
			{
				std::cout << "ASTERIX" << std::endl;
				break;
			}
			case(SLASH):
			{
				std::cout << "SLASH" << std::endl;
				break;
			}
			case(BITWISE_OR):
			{
				std::cout << "BITWISE_OR" << std::endl;
				break;
			}
			case(BITWISE_AND):
			{
				std::cout << "BITWISE_AND" << std::endl;
				break;
			}
			case(BITWISE_NOT):
			{
				std::cout << "BITWISE_NOT" << std::endl;
				break;
			}
			case(LEFTSHIFT):
			{
				std::cout << "LEFTSHIFT" << std::endl;
				break;
			}
			case(RIGHTSHIFT):
			{
				std::cout << "RIGHTSHIFT" << std::endl;
				break;
			}
			case(LOGICAL_COMPARE):
			{
				std::cout << "LOGICAL_COMPARE" << std::endl;
				break;
			}
			case(LOGICAL_NOT):
			{
				std::cout << "LOGICAL_NOT" << std::endl;
				break;
			}
			case(LESSTHAN):
			{
				std::cout << "LESSTHAN" << std::endl;
				break;
			}
			case(LESSTHANEQUAL):
			{
				std::cout << "LESSTHANEQUAL" << std::endl;
				break;
			}
			case(GREATERTHAN):
			{
				std::cout << "GREATERTHAN" << std::endl;
				break;
			}
			case(GREATERTHANEQUAL):
			{
				std::cout << "GREATERTHANEQUAL" << std::endl;
				break;
			}
			case(LOGICAL_AND):
			{
				std::cout << "LOGICAL_AND" << std::endl;
				break;
			}
			case(LOGICAL_OR):
			{
				std::cout << "LOGICAL_OR" << std::endl;
				break;
			}
			case(OPEN_PARENTHESIS):
			{
				std::cout << "OPEN_PARENTHESIS" << std::endl;
				break;
			}
			case(CLOSED_PARENTHESIS):
			{
				std::cout << "CLOSED_PARENTHESIS" << std::endl;
				break;
			}
			case(OPEN_BRACKET):
			{
				std::cout << "OPEN_BRACKET" << std::endl;
				break;
			}
			case(CLOSED_BRACKET):
			{
				std::cout << "CLOSED_BRACKET" << std::endl;
				break;
			}
			case (COMMA):
			{
				std::cout << "COMMA" << std::endl;
				break;
			}
			case (PERIOD):
			{
				std::cout << "PERIOD" << std::endl;
				break;
			}
			case (UNDERSCORE):
			{
				std::cout << "UNDERSCORE" << std::endl;
				break;
			}
			case (CURLY_BRACKET_CLOSED):
			{
				std::cout << "CURLY_BRACKET_CLOSED" << std::endl;
				break;
			}
			case (CURLY_BRACKET_OPEN):
			{
				std::cout << "CURLY_BRACKET_OPEN" << std::endl;
				break;
			}
			case (COLON):
			{
				std::cout << "COLON" << std::endl;
				break;
			}
			case (SEMICOLON):
			{
				std::cout << "SEMICOLON" << std::endl;
				break;
			}
			case(UNKNOWN):
			{
				std::cout << "UNKNOWN_TOKEN" << " (" << currToken.stringval << ")" << std::endl;
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}

	void outputASTContents(AbstractSyntaxTree ast) {
		AbstractSyntaxTreeNode* root = ast.root;
		outputNodeText(root, 0);

		int nodeLevel = 0;

		std::vector<AbstractSyntaxTreeNode*> list = root->childNodeList;
		for (int i = 0; i < list.size(); i++) {
			outputNode(list.at(i), nodeLevel + 1);
		}
	}

	void outputNode(AbstractSyntaxTreeNode* node, int nodeLevel) {
		outputNodeText(node, nodeLevel);
		std::vector<AbstractSyntaxTreeNode*> list = node->childNodeList;
		for (int i = 0; i < list.size(); i++) {
			outputNode(list.at(i), nodeLevel + 1);
		}

	}

	void outputNodeText(AbstractSyntaxTreeNode* node, int nodeLevel) {
		NodeType t = node->type;
		switch (t) {
		case(NodeType::MULTIPLY): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - multiply" << std::endl;
			break;
		}
		case(NodeType::DIVIDE): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - divide" << std::endl;
			break;
		}
		case(NodeType::ADDITION): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - addition" << std::endl;
			break;
		}
		case(NodeType::SUBTRACTION): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - subtraction" << std::endl;
			break;
		}
		case(NodeType::LEFT_SHIFT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - left shift" << std::endl;
			break;
		}
		case(NodeType::RIGHT_SHIFT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - right shift" << std::endl;
			break;
		}
		case(NodeType::LESS_THAN): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - less than" << std::endl;
			break;
		}
		case(NodeType::LESS_THAN_EQUAL): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - less than equal" << std::endl;
			break;
		}
		case(NodeType::GREATER_THAN): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - greater than" << std::endl;
			break;
		}
		case(NodeType::GREATER_THAN_EQUAL): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - greater than equal" << std::endl;
			break;
		}
		case(NodeType::EQUALITY): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - equality" << std::endl;
			break;
		}
		case(NodeType::INEQUALITY): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - inquality" << std::endl;
			break;
		}
		case(NodeType::BIT_AND): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - bitwise and" << std::endl;
			break;
		}
		case(NodeType::BIT_XOR): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - bitwise xor" << std::endl;
			break;
		}
		case(NodeType::BIT_OR): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - bitwise or" << std::endl;
			break;
		}
		case(NodeType::LOG_AND): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - logical and" << std::endl;
			break;
		}
		case(NodeType::LOG_OR): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - logical or" << std::endl;
			break;
		}
		case(NodeType::EQUALS): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - equals" << std::endl;
			break;
		}
		case(NodeType::UNARY_MINUS): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - unary minus" << std::endl;
			break;
		}
		case(NodeType::LOG_NOT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - logical not" << std::endl;
			break;
		}
		case(NodeType::BIT_NOT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression - bitwise not" << std::endl;
			break;
		}
		case(NodeType::ROOT): {
			std::cout << "root node" << std::endl;
			break;
		}
		case(NodeType::TYPEDECLARATION): {
			std::cout << nodeLevelPrefix(nodeLevel) << "type declaration" << std::endl;
			break;
		}
		case(NodeType::FUNCTIONDECLARATION): {
			std::cout << nodeLevelPrefix(nodeLevel) << "function declaration" << std::endl;
			break;
		}
		case(NodeType::VARIABLEDECLARATION): {
			std::cout << nodeLevelPrefix(nodeLevel) << "variable declaration" << std::endl;
			break;
		}
		case(NodeType::BLOCKSTATEMENT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "block statement" << std::endl;
			break;
		}
		case(NodeType::FORSTATEMENT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "for statement" << std::endl;
			break;
		}
		case(NodeType::WHILESTATEMENT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "while statement" << std::endl;
			break;
		}
		case(NodeType::IFSTATEMENT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "if statement" << std::endl;
			break;
		}
		case(NodeType::PRINTSTATEMENT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "print statement" << std::endl;
			break;
		}
		case(NodeType::RETURNSTATEMENT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "return statement" << std::endl;
			break;
		}
		case(NodeType::EXITSTATEMENT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "exit statement" << std::endl;
			break;
		}
		case(NodeType::EXPRESSIONSTATEMENT): {
			std::cout << nodeLevelPrefix(nodeLevel) << "expression statement" << std::endl;
			break;
		}
		case(NodeType::TYPE_DESCRIPTOR): {
			std::cout << nodeLevelPrefix(nodeLevel) << "type descriptor" << std::endl;
			break;
		}
		case(NodeType::RECORD_DESCRIPTOR): {
			std::cout << nodeLevelPrefix(nodeLevel) << "record descriptor" << std::endl;
			break;
		}
		case(NodeType::FIELD_DECLARATION): {
			std::cout << nodeLevelPrefix(nodeLevel) << "field declaration" << std::endl;
			break;
		}
		case(NodeType::DIMENSION): {
			std::cout << nodeLevelPrefix(nodeLevel) << "dimension" << std::endl;
			break;
		}
		case(NodeType::PARAMETER): {
			std::cout << nodeLevelPrefix(nodeLevel) << "parameter" << std::endl;
			break;
		}
		case(NodeType::DIMENSION_WILDCARD): {
			std::cout << nodeLevelPrefix(nodeLevel) << "dimension wildcard" << std::endl;
			break;
		}
		case(NodeType::IDENT_N):
		case(NodeType::STRING): {
			std::cout << nodeLevelPrefix(nodeLevel) << "symbol : " << node->token.stringval << std::endl;
			break;
		}
		case(NodeType::CHAR_LITERAL_N): {
				std::cout << nodeLevelPrefix(nodeLevel) << "char literal : " << node->token.stringval << std::endl;
				break;
		}
		case(NodeType::INT_LITERAL_N): {
			std::cout << nodeLevelPrefix(nodeLevel) << "int literal : " << node->token.value << std::endl;
			break;
		}
		case(NodeType::FLOAT_LITERAL_N): {
			std::cout << nodeLevelPrefix(nodeLevel) << "float literal : " << node->token.value << std::endl;
			break;
		}
		case(NodeType::BASIC_TYPE): {
			std::cout << nodeLevelPrefix(nodeLevel) << "basic type : ";
			if (node->token.tokenType == TokenType::BYTE) {
				std::cout << "byte";
			}
			else if (node->token.tokenType == TokenType::FLOAT) {
				std::cout << "float";
			}
			else {
				std::cout << "int";
			}
			std::cout << std::endl;
			break;
		}
		}
	}

	std::string nodeLevelPrefix(int level) {
		std::string output = "";
		for (int i = 0; i < level; i++) {
			output += "*";
		}

		return output;
	}
};

#endif