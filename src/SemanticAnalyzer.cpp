#include "SemanticAnalyzer.h"

// process type declaration 
void SemanticAnalyzer::processTypeDeclaration(AbstractSyntaxTreeNode* node) {
	std::vector<AbstractSyntaxTreeNode*> children = node->childNodeList;

	AbstractSyntaxTreeNode* identifier = children.at(0);
	std::string idName = identifier->token.stringval;

	AbstractSyntaxTreeNode* typeDes = children.at(1);
	AbstractSyntaxTreeNode* typeDesChild = typeDes->childNodeList.at(0);

	switch (typeDesChild->type) {
	case(RECORD_DESCRIPTOR): {
		// not handled yet
		break;
	}
	case(BYTE_N): {
		if (!tree->typeTable.typeExists(idName)) {
			tree->typeTable.addType(idName, BYTE_TYPE);
		}
		break;
	}
	case(INT_N): {
		if (!tree->typeTable.typeExists(idName)) {
			tree->typeTable.addType(idName, INT_TYPE);
		}
		break;
	}
	case(FLOAT_N): {
		if (!tree->typeTable.typeExists(idName)) {
			tree->typeTable.addType(idName, FLOAT_TYPE);
		}
		break;
	}
	case(IDENT_N): {
		// not handled yet
		break;
	}
	}
}

// process variable declaration
void SemanticAnalyzer::processVariableDeclaration(AbstractSyntaxTreeNode* node) {
	std::vector<AbstractSyntaxTreeNode*> children = node->childNodeList;

	AbstractSyntaxTreeNode* identifier = nullptr;

	for (int i = 0; i < children.size(); i++) {
		AbstractSyntaxTreeNode* tnode = children.at(i);
		if (tnode->type == NodeType::IDENT_N) {
			identifier = tnode;
		}
	}

	if (identifier != nullptr) {
		std::string idName = identifier->token.stringval;

		if (tree->symTable.symbolExists(idName)) {
			// error : double declaration
		}
		else {
			tree->symTable.addSymbol(idName);
		}
	}
}

// constructor
SemanticAnalyzer::SemanticAnalyzer(AbstractSyntaxTree* t) {
	tree = t;

	performSemAna();
}

// start the semantic analysis
void SemanticAnalyzer::performSemAna() {
	AbstractSyntaxTreeNode* root = tree->root;

	std::vector<AbstractSyntaxTreeNode*> children = root->childNodeList;
	int currChild = 0;

	while (currChild < children.size()) {
		processNode(children.at(currChild));
		currChild++;
	}
}

// process a node and do semantic analysis on it
void SemanticAnalyzer::processNode(AbstractSyntaxTreeNode* node) {
	NodeType nt = node->type;

	switch (nt) {
	case(TYPEDECLARATION): {
		processTypeDeclaration(node);
		break;
	}
	case(VARIABLEDECLARATION): {
		processVariableDeclaration(node);
		break;
	}
	}
}