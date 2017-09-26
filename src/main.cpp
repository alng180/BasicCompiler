#include <iostream>

#include "Tokenizer.h"
#include "Parser.h"
#include "SemanticAnalyzer.h"
#include "CodeGen.h"

#include "Test.h"

int main(int argc, char *argv[]) {
	// check arguments
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << "<INPUT FILE>" << std::endl;
		return 0;
	}
	// open file
	std::string filename = argv[1];
	std::cout << "Using file: " << argv[1] << std::endl;

	// tokenizer
	Tokenizer tokenizer(filename);
	int success = tokenizer.performParse();

	if (success != 0) {
		std::cout << "Error on line " << success << std::endl;
		return 0;
 	}

	// parse token list and create basic ast
	Parser parser(tokenizer.getTokenList());
	AbstractSyntaxTree ast = parser.getAST();

	// perform semantic analysis
	SemanticAnalyzer sa = SemanticAnalyzer(&ast);

	// perform code generation
	CodeGenerator cg = CodeGenerator("output.txt", ast);

	// done
	std::cout << "Intermediate Representation outputted to output.ir" << std::endl;
	std::cout << "Press any button to exit" << std::endl;
	std::cin.get();
	return 0; 
}