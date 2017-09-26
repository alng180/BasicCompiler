#ifndef SEMANA_H
#define SEMANA_H

#include "AbstractSyntaxTree.h"

#include <vector>

class SemanticAnalyzer {
public:
	AbstractSyntaxTree* tree;

	SemanticAnalyzer(AbstractSyntaxTree* t);
	void performSemAna();
	void processNode(AbstractSyntaxTreeNode* node);
private:
	void processTypeDeclaration(AbstractSyntaxTreeNode* node);
	void processVariableDeclaration(AbstractSyntaxTreeNode* node);
};

#endif