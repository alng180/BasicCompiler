#include "AbstractSyntaxTree_Node.h"

#pragma region AbstractSyntaxTreeNode
//----------------------------------------------------------------
// AbstractSyntaxTreeNode Base Class

// constructor
AbstractSyntaxTreeNode::AbstractSyntaxTreeNode() {
	childNodeList = std::vector<AbstractSyntaxTreeNode*>();
	type = ROOT;
}

// constructor
// primarily used for expressions
AbstractSyntaxTreeNode::AbstractSyntaxTreeNode(AbstractSyntaxTreeNode* left, AbstractSyntaxTreeNode* right, NodeType t) {
	type = t;
	currNode = this;

	addChildNode(left);
	addChildNode(right);
}

// adds a node to the node's child list
void AbstractSyntaxTreeNode::addChildNode(AbstractSyntaxTreeNode* childNode) {
	childNodeList.push_back(childNode);
}

// get the child nodes list
std::vector<AbstractSyntaxTreeNode*> AbstractSyntaxTreeNode::getChildNodes() {
	return childNodeList;
}
//----------------------------------------------------------------
#pragma endregion

#pragma region AbstractSyntaxTreeLeafNode
//----------------------------------------------------------------
// leaf node
// used for the leafs of the ast
// usually contains numbers, characters, etc
AbstractSyntaxTreeLeafNode::AbstractSyntaxTreeLeafNode(int &currentToken, std::vector<Token> &tokenList, AbstractSyntaxTreeNode* parent, NodeType t) {
	type = t;
	parentNode = parent;
	childNodeList = std::vector<AbstractSyntaxTreeNode*>();
	Token curr = tokenList.at(currentToken);
	token = curr;
	currentToken++;
}
//----------------------------------------------------------------
#pragma endregion

#pragma region AbstractSyntaxTreeExpressionNode
//----------------------------------------------------------------
// constructor
AbstractSyntaxTreeExpressionNode::AbstractSyntaxTreeExpressionNode(int &currentToken, std::vector<Token> &tokenList, AbstractSyntaxTreeNode* parent, NodeType t) {
	type = t;
	parentNode = parent;
	currNode = this;
	childNodeList = std::vector<AbstractSyntaxTreeNode*>();

	processExpressionNode(currentToken, tokenList);
}

// parse the expression from the tokens and build the expression node
void AbstractSyntaxTreeExpressionNode::processExpressionNode(int &currentToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* root = parse_equals(currentToken, tokenList);
	addChildNode(root);
}

// variable = expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_equals(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_logicalor(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == EQUAL) {
		currToken++; // =
		node = new AbstractSyntaxTreeNode(node, parse_logicalor(currToken, tokenList), NodeType::EQUALS);
	}

	return node;
}

//  expression || expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_logicalor(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_logicaland(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == LOGICAL_OR) {
		currToken++; // ||
		node = new AbstractSyntaxTreeNode(node, parse_logicaland(currToken, tokenList), NodeType::LOG_OR);
	}

	return node;
}

//  expression && expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_logicaland(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_bitwiseor(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == LOGICAL_AND) {
		currToken++; // &&
		node = new AbstractSyntaxTreeNode(node, parse_bitwiseor(currToken, tokenList), NodeType::LOG_AND);
	}

	return node;
}

// expression | expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_bitwiseor(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_bitwisenot(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == BITWISE_OR) {
		currToken++; // |
		node = new AbstractSyntaxTreeNode(node, parse_bitwisenot(currToken, tokenList), NodeType::BIT_OR);
	}

	return node;
}

// expression ^ expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_bitwisenot(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_bitwiseand(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == BITWISE_NOT) {
		currToken++; // !
		node = new AbstractSyntaxTreeNode(node, parse_bitwiseand(currToken, tokenList), NodeType::BIT_NOT);
	}

	return node;
}

// expression & expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_bitwiseand(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_equalityandinequality(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == BITWISE_AND) {
		currToken++; // &
		node = new AbstractSyntaxTreeNode(node, parse_equalityandinequality(currToken, tokenList), NodeType::BIT_AND);
	}

	return node;
}

// expression == expression & expression != expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_equalityandinequality(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_greaterlessthan(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == LOGICAL_COMPARE || tokenList.at(currToken).tokenType == LOGICAL_NOT) {
		if (tokenList.at(currToken).tokenType == LOGICAL_COMPARE) {
			currToken++; // ==
			node = new AbstractSyntaxTreeNode(node, parse_greaterlessthan(currToken, tokenList), NodeType::EQUALITY);
		}
		else if (tokenList.at(currToken).tokenType == LOGICAL_NOT) {
			currToken++; // !=
			node = new AbstractSyntaxTreeNode(node, parse_greaterlessthan(currToken, tokenList), NodeType::INEQUALITY);
		}
	}

	return node;
}

// expression < expression & expression <= expression & expression > expression & expression >= expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_greaterlessthan(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_leftrightshift(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == GREATERTHAN || tokenList.at(currToken).tokenType == GREATERTHANEQUAL || tokenList.at(currToken).tokenType == LESSTHAN || tokenList.at(currToken).tokenType == LESSTHANEQUAL) {
		if (tokenList.at(currToken).tokenType == GREATERTHAN) {
			currToken++; // >
			node = new AbstractSyntaxTreeNode(node, parse_leftrightshift(currToken, tokenList), NodeType::GREATER_THAN);
		}
		else if (tokenList.at(currToken).tokenType == GREATERTHANEQUAL) {
			currToken++; // >=
			node = new AbstractSyntaxTreeNode(node, parse_leftrightshift(currToken, tokenList), NodeType::GREATER_THAN_EQUAL);
		}
		else if (tokenList.at(currToken).tokenType == LESSTHAN) {
			currToken++; // <
			node = new AbstractSyntaxTreeNode(node, parse_leftrightshift(currToken, tokenList), NodeType::LESS_THAN);
		}
		else if (tokenList.at(currToken).tokenType == LESSTHANEQUAL) {
			currToken++; // <=
			node = new AbstractSyntaxTreeNode(node, parse_leftrightshift(currToken, tokenList), NodeType::LESS_THAN_EQUAL);
		}
	}

	return node;
}

//  expression << expression & expression >> expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_leftrightshift(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_plusminus(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == LEFTSHIFT || tokenList.at(currToken).tokenType == RIGHTSHIFT) {
		if (tokenList.at(currToken).tokenType == LEFTSHIFT) {
			currToken++; // <<
			node = new AbstractSyntaxTreeNode(node, parse_plusminus(currToken, tokenList), NodeType::LEFT_SHIFT);
		}
		else if (tokenList.at(currToken).tokenType == RIGHTSHIFT) {
			currToken++; // >>
			node = new AbstractSyntaxTreeNode(node, parse_plusminus(currToken, tokenList), NodeType::RIGHT_SHIFT);
		}
	}

	return node;
}

// expression + expression & expression - expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_plusminus(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_multidivide(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == PLUS || tokenList.at(currToken).tokenType == DASH) {
		if (tokenList.at(currToken).tokenType == PLUS) {
			currToken++; // +
			node = new AbstractSyntaxTreeNode(node, parse_multidivide(currToken, tokenList), NodeType::ADDITION);
		}
		else if (tokenList.at(currToken).tokenType == DASH) {
			currToken++; // -
			node = new AbstractSyntaxTreeNode(node, parse_multidivide(currToken, tokenList), NodeType::SUBTRACTION);
		}
	}

	return node;
}

// expression * expression & expression / expression
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_multidivide(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_unaryminus_logicalnot_bitwisenot(currToken, tokenList);

	while (tokenList.at(currToken).tokenType == ASTERIX || tokenList.at(currToken).tokenType == SLASH) {
		if (tokenList.at(currToken).tokenType == ASTERIX) {
			currToken++; // *
			node = new AbstractSyntaxTreeNode(node, parse_unaryminus_logicalnot_bitwisenot(currToken, tokenList), NodeType::MULTIPLY);
		}
		else if (tokenList.at(currToken).tokenType == SLASH) {
			currToken++; // /
			node = new AbstractSyntaxTreeNode(node, parse_unaryminus_logicalnot_bitwisenot(currToken, tokenList), NodeType::DIVIDE);
		}
	}

	return node;
}

// DOES NOT HANDLE UNARY MINUS/PLUS
// - & ! & ~
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_unaryminus_logicalnot_bitwisenot(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeNode* node = parse_factor(currToken, tokenList);

	while (/*tokenList.at(currToken).tokenType == DASH ||*/ tokenList.at(currToken).tokenType == NOT || tokenList.at(currToken).tokenType == TILDE) {
		//if (tokenList.at(currToken).tokenType == DASH) {
		//	currToken++; // DASH
		//	node = new ASTNode_ExpressionTreeNode(node, parse_factor(currToken, tokenList), NodeType::UNARY_MINUS);
		//}
		//else 
		if (tokenList.at(currToken).tokenType == NOT) {
			currToken++; // NOT
			node = new AbstractSyntaxTreeNode(node, parse_factor(currToken, tokenList), NodeType::LOG_NOT);
		}
		else if (tokenList.at(currToken).tokenType == TILDE) {
			currToken++; // TILDE
			node = new AbstractSyntaxTreeNode(node, parse_factor(currToken, tokenList), NodeType::BIT_NOT);
		}
	}

	return node;
}

// (, char, float, int, identifiers
AbstractSyntaxTreeNode* AbstractSyntaxTreeExpressionNode::parse_factor(int &currToken, std::vector<Token> &tokenList) {
	Token curr = tokenList.at(currToken);
	if (curr.tokenType == OPEN_PARENTHESIS) {
		currToken++; // (
		AbstractSyntaxTreeNode* newExpr = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
		currToken++; // )
		return newExpr;
	}
	else if (curr.tokenType == CHAR_LIT) {
		AbstractSyntaxTreeNode* newCharLit = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::CHAR_LITERAL_N);
		return newCharLit;
	}
	else if (curr.tokenType == INT_LIT) {
		AbstractSyntaxTreeNode* newIntLit = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::INT_LITERAL_N);
		return newIntLit;
	}
	else if (curr.tokenType == FLOAT_LIT) {
		AbstractSyntaxTreeNode* newFloatLit = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::FLOAT_LITERAL_N);
		return newFloatLit;
	}
	else if (curr.tokenType == IDENTIFIER) {
		AbstractSyntaxTreeNode* newId = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::IDENT_N);
		return newId;
	}
	else {
		// error
	}
}
//----------------------------------------------------------------
#pragma endregion

#pragma region AbstractSyntaxTreeStatementNode
//----------------------------------------------------------------
// constructor
AbstractSyntaxTreeStatementNode::AbstractSyntaxTreeStatementNode(int &currentToken, std::vector<Token> &tokenList, AbstractSyntaxTreeNode* parent) {
	type = ROOT;
	parentNode = parent;
	currNode = this;
	childNodeList = std::vector<AbstractSyntaxTreeNode*>();

	processStatement(currentToken, tokenList);
}

// constructor
AbstractSyntaxTreeStatementNode::AbstractSyntaxTreeStatementNode(int &currentToken, std::vector<Token> &tokenList, AbstractSyntaxTreeNode* parent, NodeType t) {
	type = t;
	parentNode = parent;
	currNode = this;
	childNodeList = std::vector<AbstractSyntaxTreeNode*>();

	processStatement(currentToken, tokenList);
}

// constructor
AbstractSyntaxTreeStatementNode::AbstractSyntaxTreeStatementNode(int &currentToken, std::vector<Token> &tokenList) {
	childNodeList = std::vector<AbstractSyntaxTreeNode*>();
	type = ROOT;

	while (currentToken < tokenList.size()) {
		AbstractSyntaxTreeStatementNode* stmtNode = new AbstractSyntaxTreeStatementNode(currentToken, tokenList, this);
		addChildNode(stmtNode);
	}
}

// process the statement token and create a statement node
void AbstractSyntaxTreeStatementNode::processStatement(int &currentToken, std::vector<Token> &tokenList) {
	Token curr = tokenList.at(currentToken);

	TokenType currType = curr.tokenType;

	switch (currType) {
		case(TYPETOKEN): {
			type = NodeType::TYPEDECLARATION;
			typeDeclaration(currentToken, tokenList);
			break;
		}
		case(FUNCTION): {
			type = NodeType::FUNCTIONDECLARATION;
			functionDeclaration(currentToken, tokenList);
			break;
		}
		case(VAR):
		case(STATIC):
		case(CONST): {
			type = NodeType::VARIABLEDECLARATION;
			variableDeclaration(currentToken, tokenList);
			break;
		}
		case(CURLY_BRACKET_OPEN): {
			type = NodeType::BLOCKSTATEMENT;
			blockStatement(currentToken, tokenList);
			break;
		}
		case(FOR): {
			type = NodeType::FORSTATEMENT;
			forStatement(currentToken, tokenList);
			break;
		}
		case(WHILE): {
			type = NodeType::WHILESTATEMENT;
			whileStatement(currentToken, tokenList);
			break;
		}
		case(IF): {
			type = NodeType::IFSTATEMENT;
			ifStatement(currentToken, tokenList);
			break;
		}
		case(PRINT): {
			type = NodeType::PRINTSTATEMENT;
			printStatement(currentToken, tokenList);
			break;
		}
		case(RETURN): {
			type = NodeType::RETURNSTATEMENT;
			returnStatement(currentToken, tokenList);
			break;
		}
		case(EXIT): {
			type = NodeType::EXITSTATEMENT;
			exitStatement(currentToken, tokenList);
			break;
		}
		default: {
			type = NodeType::EXPRESSIONSTATEMENT;
			expressionStatement(currentToken, tokenList);
			break;
		}
	}
}

// type declaration
void AbstractSyntaxTreeStatementNode::typeDeclaration(int &currentToken, std::vector<Token> &tokenList) {
	currentToken++; //type

	AbstractSyntaxTreeLeafNode* typeDecId = new AbstractSyntaxTreeLeafNode(currentToken, tokenList, currNode, NodeType::IDENT_N);
	addChildNode(typeDecId);

	AbstractSyntaxTreeStatementNode* typeDescript = new AbstractSyntaxTreeStatementNode(currentToken, tokenList, currNode, NodeType::TYPE_DESCRIPTOR);
	addChildNode(typeDescript);

	currentToken++; // ;
}

// function declaration
void AbstractSyntaxTreeStatementNode::functionDeclaration(int &currentToken, std::vector<Token> &tokenList) {
	currentToken++; //function

	AbstractSyntaxTreeLeafNode* funcDecId = new AbstractSyntaxTreeLeafNode(currentToken, tokenList, currNode, NodeType::IDENT_N);
	addChildNode(funcDecId);

	Token curr = tokenList.at(currentToken);
	if (curr.tokenType == OPEN_PARENTHESIS) {
		currentToken++; // (

		bool contParams = true;
		while (contParams) {
			AbstractSyntaxTreeStatementNode* newparams = new AbstractSyntaxTreeStatementNode(currentToken, tokenList, currNode, NodeType::PARAMETER);
			addChildNode(newparams);

			curr = tokenList.at(currentToken);

			if (curr.tokenType == COMMA) {
				currentToken++; // ,
			}
			else {
				contParams = false;
			}
		}
		currentToken++; // )
	}

	if (curr.tokenType != CURLY_BRACKET_OPEN) {
		AbstractSyntaxTreeStatementNode* functypedec = new AbstractSyntaxTreeStatementNode(currentToken, tokenList, currNode, NodeType::TYPE_DESCRIPTOR);
		addChildNode(functypedec);
	}

	AbstractSyntaxTreeStatementNode* funcblockstate = new AbstractSyntaxTreeStatementNode(currentToken, tokenList, currNode, NodeType::BLOCKSTATEMENT);
	addChildNode(funcblockstate);
}

// variable declaration
void AbstractSyntaxTreeStatementNode::variableDeclaration(int &currToken, std::vector<Token> &tokenList) {
	Token curr = tokenList.at(currToken);

	if (curr.tokenType == STATIC) {
		AbstractSyntaxTreeLeafNode* staticvarflag = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::VAR_STATIC_N);
		addChildNode(staticvarflag);
		curr = tokenList.at(currToken);
	}

	if (curr.tokenType == CONST) {
		AbstractSyntaxTreeLeafNode* constvarflag = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::VAR_CONST_N);
		addChildNode(constvarflag);
		curr = tokenList.at(currToken);
	}

	currToken++; // var

	AbstractSyntaxTreeLeafNode* varId = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::IDENT_N);
	addChildNode(varId);

	curr = tokenList.at(currToken);
	if (curr.tokenType == EQUAL) {
		currToken++; // =

		AbstractSyntaxTreeExpressionNode* varExpr = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
		addChildNode(varExpr);
	}
	else {
		AbstractSyntaxTreeStatementNode* varTypeDes = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::TYPE_DESCRIPTOR);
		addChildNode(varTypeDes);
	}

	currToken++; // ;
}

// block statement
void AbstractSyntaxTreeStatementNode::blockStatement(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // {

	while (tokenList.at(currToken).tokenType != CURLY_BRACKET_CLOSED) {
		processStatement(currToken, tokenList);
	}

	currToken++; // }
}

// for statement
void AbstractSyntaxTreeStatementNode::forStatement(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // for
	currToken++; // (

				 // expression
	AbstractSyntaxTreeExpressionNode* expr_1 = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
	addChildNode(expr_1);

	currToken++; // ;

				 // expression
	AbstractSyntaxTreeExpressionNode* expr_2 = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
	addChildNode(expr_2);

	currToken++; // ;

				 // expression
	AbstractSyntaxTreeExpressionNode* expr_3 = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
	addChildNode(expr_3);

	currToken++; // )

				 // block statement
	AbstractSyntaxTreeStatementNode* forblockstate = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::BLOCKSTATEMENT);
	addChildNode(forblockstate);
}

// while statement
void AbstractSyntaxTreeStatementNode::whileStatement(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // while
	currToken++; // (

				 // expression
	AbstractSyntaxTreeExpressionNode* expr_w = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
	addChildNode(expr_w);

	currToken++; // )

				 // block statement
	AbstractSyntaxTreeStatementNode* whileblockstate = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::BLOCKSTATEMENT);
	addChildNode(whileblockstate);
}

// if statement
void AbstractSyntaxTreeStatementNode::ifStatement(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // if
	currToken++; // (

				 // expression
	AbstractSyntaxTreeExpressionNode* expr_i = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
	addChildNode(expr_i);

	currToken++; // )

				 // block statement
	AbstractSyntaxTreeStatementNode* ifblockstate = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::BLOCKSTATEMENT);
	addChildNode(ifblockstate);

	Token curr = tokenList.at(currToken);
	if (curr.tokenType == ELSE) {
		currToken++; // else

					 // block statement
		AbstractSyntaxTreeStatementNode* elseblockstate = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::BLOCKSTATEMENT);
		addChildNode(elseblockstate);
	}
}

// print statement
void AbstractSyntaxTreeStatementNode::printStatement(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // print

	AbstractSyntaxTreeExpressionNode* printexpr = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
	addChildNode(printexpr);

	currToken++; // ;
}

// return statement
void AbstractSyntaxTreeStatementNode::returnStatement(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // return

	if (tokenList.at(currToken).tokenType != SEMICOLON) {
		AbstractSyntaxTreeExpressionNode* returnexpr = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
		addChildNode(returnexpr);
	}

	currToken++; // ;
}

// exit statement
void AbstractSyntaxTreeStatementNode::exitStatement(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // exit

	if (tokenList.at(currToken).tokenType != SEMICOLON) {
		AbstractSyntaxTreeExpressionNode* exitexpr = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
		addChildNode(exitexpr);
	}

	currToken++; // ;
}

// expression statement
void AbstractSyntaxTreeStatementNode::expressionStatement(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeExpressionNode* expr = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, NodeType::EXPRESSIONROOT);
	addChildNode(expr);

	currToken++; // ;
}

// type descriptor
void AbstractSyntaxTreeStatementNode::typeDescriptor(int &currToken, std::vector<Token> &tokenList) {
	Token curr = tokenList.at(currToken);

	switch (curr.tokenType) {
	case(RECORD): {
		AbstractSyntaxTreeStatementNode* newRec = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::RECORD_DESCRIPTOR);
		addChildNode(newRec);
		break;
	}
	case(BYTE): {
		AbstractSyntaxTreeLeafNode* newBasic = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::BYTE_N);
		addChildNode(newBasic);
		break;
	}
	case(INT32): {
		AbstractSyntaxTreeLeafNode* newBasic = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::INT_N);
		addChildNode(newBasic);
		break;
	}
	case(FLOAT): {
		AbstractSyntaxTreeLeafNode* newBasic = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::FLOAT_N);
		addChildNode(newBasic);
		break;
	}
	case(IDENTIFIER): {
		AbstractSyntaxTreeLeafNode* newIdent = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::IDENT_N);
		addChildNode(newIdent);
		break;
	}
	}

	curr = tokenList.at(currToken);

	if (curr.tokenType == OPEN_BRACKET) {
		AbstractSyntaxTreeStatementNode* dimen = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::DIMENSION);
		addChildNode(dimen);
	}
}

// record descriptor
void AbstractSyntaxTreeStatementNode::recordDescriptor(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // record

	bool recordCont = true;
	Token curr = tokenList.at(currToken);

	while (recordCont) {
		AbstractSyntaxTreeStatementNode* fielddec = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::FIELD_DECLARATION);
		addChildNode(fielddec);

		curr = tokenList.at(currToken);
		if (curr.tokenType == COMMA) {
			currToken++;
		}
		else {
			recordCont = false;
		}
	}

	currToken++; // end
}

// field declaration
void AbstractSyntaxTreeStatementNode::fieldDeclaration(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeLeafNode* fieldid = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::IDENT_N);
	addChildNode(fieldid);

	AbstractSyntaxTreeStatementNode* fieldtypedes = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::TYPE_DESCRIPTOR);
	addChildNode(fieldtypedes);
}

// expression
void AbstractSyntaxTreeStatementNode::expression(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeExpressionNode* expressionTree = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, EXPRESSIONROOT);
	addChildNode(expressionTree);
}

// typecast
void AbstractSyntaxTreeStatementNode::typecast(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeLeafNode* typecastbasic = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::BASIC_TYPE);
	addChildNode(typecastbasic);

	currToken++; // (

	AbstractSyntaxTreeStatementNode* typecastexpr = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::EXPRESSION);
	addChildNode(typecastexpr);

	currToken++; // )
}

// function calls
void AbstractSyntaxTreeStatementNode::functionCall(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeLeafNode* funcid = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::IDENT_N);
	addChildNode(funcid);

	currToken++; // (

	while (tokenList.at(currToken).tokenType != CLOSED_PARENTHESIS) {
		AbstractSyntaxTreeStatementNode* funcexpr = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::EXPRESSION);
		addChildNode(funcexpr);
	}

	currToken++; // )
}

// variable
void AbstractSyntaxTreeStatementNode::variable(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeLeafNode* varId = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::IDENT_N);
	addChildNode(varId);

	if (tokenList.at(currToken).tokenType == OPEN_BRACKET) {
		while (tokenList.at(currToken).tokenType != CLOSED_BRACKET) {
			AbstractSyntaxTreeStatementNode* expr = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::EXPRESSION);
			addChildNode(expr);
		}
	}

	while (tokenList.at(currToken).tokenType == PERIOD) {
		AbstractSyntaxTreeStatementNode* newVar = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::VARIABLE);
		addChildNode(newVar);
	}
}

// string literal
void AbstractSyntaxTreeStatementNode::stringliteral(int &currToken, std::vector<Token> &tokenList) {
	AbstractSyntaxTreeLeafNode* stringLit = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::STRING);
	addChildNode(stringLit);
}

// dimension
void AbstractSyntaxTreeStatementNode::dimension(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // [

	while (tokenList.at(currToken).tokenType != CLOSED_BRACKET) {
		AbstractSyntaxTreeStatementNode* funcexpr = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::EXPRESSION);
		addChildNode(funcexpr);
	}

	currToken++; // ]
}

// parameter
void AbstractSyntaxTreeStatementNode::parameter(int &currToken, std::vector<Token> &tokenList) {
	Token curr = tokenList.at(currToken);

	if (curr.tokenType == REF) {
		AbstractSyntaxTreeLeafNode* refFlag = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::VAR_REF_N);
		addChildNode(refFlag);
		curr = tokenList.at(currToken);
	}

	if (curr.tokenType == CONST) {
		AbstractSyntaxTreeLeafNode* constFlag = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::VAR_CONST_N);
		addChildNode(constFlag);
		curr = tokenList.at(currToken);
	}

	AbstractSyntaxTreeLeafNode* paraId = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::IDENT_N);
	addChildNode(paraId);
	curr = tokenList.at(currToken);

	if (curr.tokenType == EQUAL) {
		currToken++; // =

		AbstractSyntaxTreeExpressionNode* expressionTree = new AbstractSyntaxTreeExpressionNode(currToken, tokenList, currNode, EXPRESSIONROOT);
		addChildNode(expressionTree);
	}
	else {
		switch (curr.tokenType) {
		case(RECORD): {
			AbstractSyntaxTreeStatementNode* newRec = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::RECORD_DESCRIPTOR);
			addChildNode(newRec);
			break;
		}
		case(BYTE):
		case(INT32):
		case(FLOAT): {
			AbstractSyntaxTreeLeafNode* newBasic = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::BASIC_TYPE);
			addChildNode(newBasic);
			break;
		}
		case(IDENTIFIER): {
			AbstractSyntaxTreeLeafNode* newIdent = new AbstractSyntaxTreeLeafNode(currToken, tokenList, currNode, NodeType::IDENT_N);
			addChildNode(newIdent);
			break;
		}
		}

		curr = tokenList.at(currToken);

		if (curr.tokenType == OPEN_BRACKET) {
			AbstractSyntaxTreeStatementNode* dimen = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::DIMENSION);
			addChildNode(dimen);
		}
	}
}


// dimension wildcard
void AbstractSyntaxTreeStatementNode::dimensionWildcard(int &currToken, std::vector<Token> &tokenList) {
	currToken++; // [


	while (tokenList.at(currToken).tokenType != CLOSED_BRACKET) {
		AbstractSyntaxTreeStatementNode* funcexpr = new AbstractSyntaxTreeStatementNode(currToken, tokenList, currNode, NodeType::EXPRESSION);
		addChildNode(funcexpr);

		currToken++; // ,
	}

	currToken++; // ]
}
//----------------------------------------------------------------
#pragma endregion