#ifndef TYPETABLE_H
#define TYPETABLE_H

#include <unordered_map>
#include <string>

#include "Type.h"

class TypeTable {
public:
	std::unordered_map<std::string, Type> table;

	TypeTable() {
		table = std::unordered_map<std::string, Type>();

		Type int_32 = Type("int32", INT_TYPE);
		Type byte = Type("byte", BYTE_TYPE);
		Type float_64 = Type("float64", FLOAT_TYPE);
		table.emplace("int32", int_32);
		table.emplace("byte", byte);
		table.emplace("float64", float_64);
	}

	bool typeExists(std::string type) {
		if (table.find(type) != table.end()) {
			return true;
		}

		return false;
	}

	Type getType(std::string type) {
		return table.at(type);
	}

	void addType(std::string t, TypeEnum te) {
		Type newType = Type(t, te);
		table.emplace(t, newType);
	}
};

#endif