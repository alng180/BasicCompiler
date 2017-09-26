#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>

#include "Symbol.h"

// symbol table

class SymbolTable {
public:
	std::unordered_map<std::string, Symbol> table;

	SymbolTable() {
		table = std::unordered_map<std::string, Symbol>();
	}

	void addSymbol(std::string sym) {
		Symbol s = Symbol(sym);
		table.emplace(sym, s);
	}

	Symbol getSymbol(std::string sym) {
		return table.at(sym);
	}

	bool symbolExists(std::string sym) {
		if (table.find(sym) != table.end()) {
			return true;
		}

		return false;
	}
};

#endif