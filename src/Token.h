#ifndef TOKEN_H
#define TOKEN_H

#include <string>

#include "TokenType.h"

// Token
// single token produced by the tokenizer

class Token {
public:
	int lineNumber;
	int columnNumber;

	TokenType tokenType;

	double value;
	std::string stringval;

	Token() {
		lineNumber = 0;
		columnNumber = 0;
		value = 0.0;
		stringval = "";
		tokenType = PLACEHOLDER;
	}

	Token(TokenType t, int linenum, int columnnum) {
		lineNumber = linenum;
		columnNumber = columnnum;
		value = 0.0;
		stringval = "";
		tokenType = t;
	}

	Token(TokenType t, int linenum, int columnnum, double val) {
		lineNumber = linenum;
		columnNumber = columnnum;
		value = val;
		stringval = "";
		tokenType = t;
	}

	Token(TokenType t, int linenum, int columnnum, std::string str) {
		lineNumber = linenum;
		columnNumber = columnnum;
		value = 0.0;
		stringval = str;
		tokenType = t;
	}
};

#endif