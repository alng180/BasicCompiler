#ifndef OBJTABLE_H
#define OBJTABLE_H

#include <unordered_map>

#include "Object.h"

class ObjectTable {
public:
	std::unordered_map<std::string, Object*> objTable;
};

#endif