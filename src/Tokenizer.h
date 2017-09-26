#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <fstream>
#include <cctype>

#include "Token.h"
#include "ObjectTable.h"
#include "Object.h"

// Tokenizer
// Reads the input text file and converts it into a list of tokens
class Tokenizer {
public:
	// constructors
	Tokenizer(std::string file);

	int performParse();
	std::vector<Token> getTokenList();
private:
	std::string filename;
	std::vector<Token> tokenList;

	bool parseLine(std::string line, int lineCount, bool&commentFlag);

	std::string getStringLiteral(std::string line, int columnCount, bool &success, int &size);
	std::string getCharLiteral(std::string line, int columnCount, bool &success, int &size);
	bool getNumber(std::string line, int columnCount, double &value, int &size);

	void getIdentifierToken(std::string line, int &columnCount, int lineCount);
	void createIdentifierToken(std::string identifierName, int colCount, int lineCount);

	bool isReservedWord(std::string line, int columnCount, std::string word);
	bool checkNextChar(std::string line, int columnCount, char c);


};

#endif