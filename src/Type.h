#ifndef TYPE_H
#define TYPE_H

#include <string>

// type
// type item used for type checking/declarations

enum TypeEnum {INT_TYPE, FLOAT_TYPE, BYTE_TYPE};

class Type {
public:
	std::string typeName;
	TypeEnum t;

	Type() {
		typeName = "";
	}

	Type(std::string str, TypeEnum tp) {
		typeName = str;
		t = tp;
	}
};

#endif