#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "Token.h"
#include "Type.h"

// symbol
// single entry in the symbol table

class Symbol {
	public:
	std::string symbolName;

	Symbol(std::string name) {
		symbolName = name;
	}
};

#endif