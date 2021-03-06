#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType {
	IDENTIFIER, STRING_LIT, CHAR_LIT, FLOAT_LIT, BYTE_LIT, INT_LIT,
	BYTE, CONST, ELSE, END, EXIT, FLOAT, FOR, FUNCTION, IF, INT32, PRINT, RECORD, REF, RETURN, STATIC, TYPETOKEN, VAR, WHILE,
	EQUAL, NOT, TILDE, DASH, PLUS, ASTERIX, SLASH, COMMA, PERIOD, BITWISE_OR, BITWISE_AND, BITWISE_NOT, LEFTSHIFT, RIGHTSHIFT,
	LOGICAL_COMPARE, LOGICAL_NOT, LESSTHAN, LESSTHANEQUAL, GREATERTHAN, GREATERTHANEQUAL, LOGICAL_AND, LOGICAL_OR,
	OPEN_PARENTHESIS, CLOSED_PARENTHESIS, OPEN_BRACKET, CLOSED_BRACKET, UNDERSCORE, CURLY_BRACKET_OPEN, CURLY_BRACKET_CLOSED,
	SEMICOLON, COLON,
	UNKNOWN, PLACEHOLDER
};

#endif