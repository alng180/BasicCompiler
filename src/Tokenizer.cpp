#include "Tokenizer.h"

// constructor
Tokenizer::Tokenizer(std::string file) {
	tokenList = std::vector<Token>();
	filename = file;
}

// main function
// starts the parse of the input
int Tokenizer::performParse() {
	if (filename == "") {
		return false;
	}

	std::string line;
	std::ifstream input;

	input.open(filename, std::ios::in);

	int lineCount = 0;
	bool commentFlag = false;

	while (std::getline(input, line)) {
		lineCount++;
		bool success = parseLine(line, lineCount, commentFlag);
		if (!success) {
			return lineCount;
		}
	}

	return 0;
}

// return the token list
std::vector<Token> Tokenizer::getTokenList() {
	return tokenList;
}

// parse a single line of input
bool Tokenizer::parseLine(std::string line, int lineCount, bool &commentFlag) {
	int lineLen = line.length();
	int columnCount = 0;

	// iterate through all characters in line
	while (columnCount < lineLen) {
		char currChar = line.at(columnCount);

		if (commentFlag) {
			if (currChar == '*') {
				if (checkNextChar(line, columnCount, '/')) {
					commentFlag = false;
					columnCount++;
				}
			}
			columnCount++;
			continue;
		}

		// check current character
		switch (currChar) {
			// cases for reserved words first
		case 'b': 	// byte
		{
			bool isByte = isReservedWord(line, columnCount, "byte");
			if (isByte) {
				Token byteToken = Token(BYTE, lineCount, columnCount);
				tokenList.push_back(byteToken);
				columnCount += 3;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 'c':	// const
		{
			bool isConst = isReservedWord(line, columnCount, "const");
			if (isConst) {
				Token constToken = Token(CONST, lineCount, columnCount);
				tokenList.push_back(constToken);
				columnCount += 4;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 'e':	// else, end, exit
		{
			bool isElse = isReservedWord(line, columnCount, "else");
			if (isElse) {
				Token elseToken = Token(ELSE, lineCount, columnCount);
				tokenList.push_back(elseToken);
				columnCount += 3;
				break;
			}

			bool isEnd = isReservedWord(line, columnCount, "end");
			if (isEnd) {
				Token endToken = Token(END, lineCount, columnCount);
				tokenList.push_back(endToken);
				columnCount += 2;
				break;
			}

			bool isExit = isReservedWord(line, columnCount, "exit");
			if (isExit) {
				Token exitToken = Token(EXIT, lineCount, columnCount);
				tokenList.push_back(exitToken);
				columnCount += 3;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 'f':	// float64, for, function
		{
			bool isFloat = isReservedWord(line, columnCount, "float64");
			if (isFloat) {
				Token floatToken = Token(FLOAT, lineCount, columnCount);
				tokenList.push_back(floatToken);
				columnCount += 6;
				break;
			}

			bool isFor = isReservedWord(line, columnCount, "for");
			if (isFor) {
				Token forToken = Token(FOR, lineCount, columnCount);
				tokenList.push_back(forToken);
				columnCount += 2;
				break;
			}

			bool isFunction = isReservedWord(line, columnCount, "function");
			if (isFunction) {
				Token functionToken = Token(FUNCTION, lineCount, columnCount);
				tokenList.push_back(functionToken);
				columnCount += 7;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 'i':	// if, int32
		{
			bool isIf = isReservedWord(line, columnCount, "if");
			if (isIf) {
				Token ifToken = Token(IF, lineCount, columnCount);
				tokenList.push_back(ifToken);
				columnCount += 1;
				break;
			}

			bool isInt = isReservedWord(line, columnCount, "int32");
			if (isInt) {
				Token intToken = Token(INT32, lineCount, columnCount);
				tokenList.push_back(intToken);
				columnCount += 4;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 'p':	// print
		{
			bool isPrint = isReservedWord(line, columnCount, "print");
			if (isPrint) {
				Token printToken = Token(PRINT, lineCount, columnCount);
				tokenList.push_back(printToken);
				columnCount += 4;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 'r':	// record, ref, return
		{
			bool isRecord = isReservedWord(line, columnCount, "record");
			if (isRecord) {
				Token recordToken = Token(RECORD, lineCount, columnCount);
				tokenList.push_back(recordToken);
				columnCount += 5;
				break;
			}

			bool isRef = isReservedWord(line, columnCount, "ref");
			if (isRef) {
				Token refToken = Token(REF, lineCount, columnCount);
				tokenList.push_back(refToken);
				columnCount += 2;
				break;
			}

			bool isReturn = isReservedWord(line, columnCount, "return");
			if (isReturn) {
				Token returnToken = Token(RETURN, lineCount, columnCount);
				tokenList.push_back(returnToken);
				columnCount += 5;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 's':	// static
		{
			bool isStatic = isReservedWord(line, columnCount, "static");
			if (isStatic) {
				Token staticToken = Token(STATIC, lineCount, columnCount);
				tokenList.push_back(staticToken);
				columnCount += 5;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 't':	// type
		{
			bool isType = isReservedWord(line, columnCount, "type");
			if (isType) {
				Token typeToken = Token(TYPETOKEN, lineCount, columnCount);
				tokenList.push_back(typeToken);
				columnCount += 3;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 'v':	// var
		{
			bool isVar = isReservedWord(line, columnCount, "var");
			if (isVar) {
				Token varToken = Token(VAR, lineCount, columnCount);
				tokenList.push_back(varToken);
				columnCount += 2;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}
		case 'w':	// while
		{
			bool isWhile = isReservedWord(line, columnCount, "while");
			if (isWhile) {
				Token whileToken = Token(WHILE, lineCount, columnCount);
				tokenList.push_back(whileToken);
				columnCount += 4;
				break;
			}

			getIdentifierToken(line, columnCount, lineCount);
			break;
		}

		// remaining letters - identifers
		case 'a': case 'A': case 'B': case 'C': case 'd': case 'D': case 'E': case 'F': case 'g': case 'G':
		case 'h': case 'H': case 'I': case 'j': case 'J': case 'k': case 'K': case 'l': case 'L': case 'm':
		case 'M': case 'n': case 'N': case 'o': case 'O': case 'P': case 'q': case 'Q': case 'R': case 'S':
		case 'T': case 'u': case 'U': case 'V': case 'W': case 'x': case 'X': case 'y': case 'Y': case 'z':
		case 'Z':
		{
			getIdentifierToken(line, columnCount, lineCount);
			break;
		}

		// numbers
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8':	case '9': case '0':
		{
			double val = 0.0;
			int size = 0;
			bool isAFloat = getNumber(line, columnCount, val, size);
			if (isAFloat) {
				Token floatToken = Token(FLOAT_LIT, lineCount, columnCount, val);
				tokenList.push_back(floatToken);
			}
			else {
				Token intToken = Token(INT_LIT, lineCount, columnCount, val);
				tokenList.push_back(intToken);
			}
			columnCount += size - 1;
			break;
		}

		// special characters
		case '=':
			if (checkNextChar(line, columnCount, '=')) {	// ==
				Token logEqualsToken = Token(LOGICAL_COMPARE, lineCount, columnCount);
				tokenList.push_back(logEqualsToken);
				columnCount++;
			}
			else {	// =
				Token equalsToken = Token(EQUAL, lineCount, columnCount);
				tokenList.push_back(equalsToken);
			}
			break;
		case '!':
			if (checkNextChar(line, columnCount, '='))		// !=
			{
				Token notEqualsToken = Token(LOGICAL_NOT, lineCount, columnCount);
				tokenList.push_back(notEqualsToken);
				columnCount++;
			}
			else {
				Token notToken = Token(NOT, lineCount, columnCount);
				tokenList.push_back(notToken);
			}
			break;
		case '~':
		{
			Token tildeToken = Token(TILDE, lineCount, columnCount);
			tokenList.push_back(tildeToken);
			break;
		}
		case '-':
		{
			Token dashToken = Token(DASH, lineCount, columnCount);
			tokenList.push_back(dashToken);
			break;
		}
		case '+':
		{
			Token plusToken = Token(PLUS, lineCount, columnCount);
			tokenList.push_back(plusToken);
			break;
		}
		case '*':	// asterix
		{
			Token asterixToken = Token(ASTERIX, lineCount, columnCount);
			tokenList.push_back(asterixToken);
			break;
		}
		case '/':	// slash
		{
			if (checkNextChar(line, columnCount, '/')) {	//	//
				columnCount = lineLen;
				break;
			}

			if (checkNextChar(line, columnCount, '*')) {	//	/*
				commentFlag = true;	// set comment flag to true (multi line commenting)
				columnCount++;
				break;
			}

			Token slashToken = Token(SLASH, lineCount, columnCount);
			tokenList.push_back(slashToken);
			break;
		}
		case '|':
		{
			if (checkNextChar(line, columnCount, '|')) {	// ||
				Token logOrToken = Token(LOGICAL_OR, lineCount, columnCount);
				tokenList.push_back(logOrToken);
				columnCount++;
				break;
			}
			else {											// |
				Token orToken = Token(BITWISE_OR, lineCount, columnCount);
				tokenList.push_back(orToken);
				break;
			}
		}
		case '&':
			if (checkNextChar(line, columnCount, '&')) {	// &&
				Token logAndToken = Token(LOGICAL_AND, lineCount, columnCount);
				tokenList.push_back(logAndToken);
				columnCount++;
				break;
			}
			else {											// &
				Token andToken = Token(BITWISE_AND, lineCount, columnCount);
				tokenList.push_back(andToken);
				break;
			}
		case '^':
		{
			Token bitNotToken = Token(BITWISE_NOT, lineCount, columnCount);
			tokenList.push_back(bitNotToken);
			break;
		}
		case '<':
		{
			if (checkNextChar(line, columnCount, '=')) {	// <=
				Token lessEqualToken = Token(LESSTHANEQUAL, lineCount, columnCount);
				tokenList.push_back(lessEqualToken);
				columnCount++;
				break;
			}

			if (checkNextChar(line, columnCount, '<')) {	// <<
				Token leftShiftToken = Token(LEFTSHIFT, lineCount, columnCount);
				tokenList.push_back(leftShiftToken);
				columnCount++;
				break;
			}

			// <
			Token lessThanToken = Token(LESSTHAN, lineCount, columnCount);
			tokenList.push_back(lessThanToken);
			break;
		}
		case '>':
		{
			// >=
			if (checkNextChar(line, columnCount, '=')) {
				Token greaterEqualToken = Token(GREATERTHANEQUAL, lineCount, columnCount);
				tokenList.push_back(greaterEqualToken);
				columnCount++;
				break;
			}

			// >>
			if (checkNextChar(line, columnCount, '>')) {
				Token rightShiftToken = Token(RIGHTSHIFT, lineCount, columnCount);
				tokenList.push_back(rightShiftToken);
				columnCount++;
				break;
			}

			// >
			Token greaterThanToken = Token(GREATERTHAN, lineCount, columnCount);
			tokenList.push_back(greaterThanToken);
			break;
		}
		case '"':	// double quotes - string literal
		{
			bool success = false;
			int size = 1;
			std::string strLit = getStringLiteral(line, columnCount, success, size);
			if (success) {
				Token strToken = Token(STRING_LIT, lineCount, columnCount, strLit);
				tokenList.push_back(strToken);
				columnCount += size;
				break;
			}
			else {
				return false;
			}

		}
		case '\'':	// single quote - char literal
		{
			bool success = false;
			int size = 1;
			std::string charLit = getCharLiteral(line, columnCount, success, size);
			if (success) {
				Token charToken = Token(CHAR_LIT, lineCount, columnCount, charLit);
				tokenList.push_back(charToken);
				columnCount += size;
				break;
			}
			else {
				return false;
			}
			break;
		}
		case '(':	// open paren
		{
			Token openParenToken = Token(OPEN_PARENTHESIS, lineCount, columnCount);
			tokenList.push_back(openParenToken);
			break;
		}
		case ')':	// closed paren
		{
			Token closedParenToken = Token(CLOSED_PARENTHESIS, lineCount, columnCount);
			tokenList.push_back(closedParenToken);
			break;
		}
		case '[':	// open bracket
		{
			Token openBracketToken = Token(OPEN_BRACKET, lineCount, columnCount);
			tokenList.push_back(openBracketToken);
			break;
		}
		case ']':	// closed bracket
		{
			Token closedBracketToken = Token(CLOSED_BRACKET, lineCount, columnCount);
			tokenList.push_back(closedBracketToken);
			break;
		}
		case ',':
		{
			Token commaToken = Token(COMMA, lineCount, columnCount);
			tokenList.push_back(commaToken);
			break;
		}
		case '.':
		{
			// .####
			if (columnCount + 1 < line.length()) {
				char nextChar = line.at(columnCount + 1);
				if (std::isdigit(nextChar)) {
					double val = 0.0;
					int size = 0;
					bool isAFloat = getNumber(line, columnCount, val, size);
					if (isAFloat) {
						Token floatToken = Token(FLOAT_LIT, lineCount, columnCount, val);
						tokenList.push_back(floatToken);
					}
					else {
						Token intToken = Token(INT_LIT, lineCount, columnCount, val);
						tokenList.push_back(intToken);
					}
					columnCount += size - 1;
					break;
				}
			}

			// .
			Token periodToken = Token(PERIOD, lineCount, columnCount);
			tokenList.push_back(periodToken);
			break;
		}
		case ' ':	// white space
		{	// do nothing/skip
			break;
		}
		case '_':	// _
		{
			Token underscoreToken = Token(UNDERSCORE, lineCount, columnCount);
			tokenList.push_back(underscoreToken);
			break;
		}
		case '{':	// {
		{
			Token curlyBracOpenToken = Token(CURLY_BRACKET_OPEN, lineCount, columnCount);
			tokenList.push_back(curlyBracOpenToken);
			break;
		}
		case '}':	// }
		{
			Token curlyBracClosedToken = Token(CURLY_BRACKET_CLOSED, lineCount, columnCount);
			tokenList.push_back(curlyBracClosedToken);
			break;
		}
		case ':':	// :
		{
			Token colonToken = Token(COLON, lineCount, columnCount);
			tokenList.push_back(colonToken);
			break;
		}
		case ';':	// ;
		{
			Token semicolonToken = Token(SEMICOLON, lineCount, columnCount);
			tokenList.push_back(semicolonToken);
			break;
		}
		default:
		{	// error - unrecognized token
			Token unknownToken = Token(UNKNOWN, lineCount, columnCount, std::string(1, currChar));
			tokenList.push_back(unknownToken);
			break;
		}
		}

		columnCount++;
	}

	return true;
}

// get a string literal from the input
std::string Tokenizer::getStringLiteral(std::string line, int columnCount, bool &success, int &size) {
	std::vector<char> charList = std::vector<char>();
	size = 1;

	while (columnCount + size < line.length()) {
		char currChar = line.at(columnCount + size);

		if (currChar != '"') {
			charList.push_back(currChar);
		}
		else {
			success = true;
			break;
		}

		size++;
	}

	return std::string(charList.begin(), charList.end());
}

// get a char literal from the input
std::string Tokenizer::getCharLiteral(std::string line, int columnCount, bool &success, int &size) {
	std::vector<char> charList = std::vector<char>();
	size = 1;

	while (columnCount + size < line.length()) {
		char currChar = line.at(columnCount + size);

		if (currChar != '\'') {
			charList.push_back(currChar);
		}
		else if (currChar == '\'') {
			success = true;
			break;
		}

		size++;
	}

	if (success) {
		if (size == 2) {
			if (std::isalnum(charList.at(0))) {
				return std::string(1, charList.at(0));
			}
		}
		else if (size == 3) {
			if (charList.at(0) == '\\') {
				char tempChar = charList.at(1);
				if (((tempChar == '0') || (tempChar == 'n') || (tempChar == '"') || (tempChar == '\'') || (tempChar == '\\') || (tempChar == 't'))) {
					return std::string(1, charList.at(0)) + std::string(1, charList.at(1));
				}
			}
		}
		else if (size == 5) {
			if (charList.at(0) == '\\') {
				if (charList.at(0) == '\\' && charList.at(1) == 'x' && charList.at(2) == 'd' && charList.at(3) == 'd') {
					return "\xdd";
				}
			}
		}
	}

	success = false;
	return "";
}

// get a number from the input
bool Tokenizer::getNumber(std::string line, int columnCount, double &value, int &size) {
	size = 0;

	bool period = false;
	std::string numVal = "";

	while (columnCount + size < line.length()) {
		char currChar = line.at(columnCount + size);
		if (std::isdigit(currChar)) {
			numVal += currChar;
		}
		else if (currChar == '.') {
			if (!period) {
				period = true;
				numVal += currChar;
			}
			else {
				break;
			}
		}
		else {
			break;
		}

		size++;
	}

	value = std::stof(numVal);
	return (period) ? true : false;
}

// get the next identifier from the input
void Tokenizer::getIdentifierToken(std::string line, int &columnCount, int lineCount) {
	std::vector<char> charList = std::vector<char>();
	int colCount = columnCount;

	while (colCount < line.length()) {
		char currChar = line.at(colCount);

		if (currChar == ' ' || ((!std::isalnum(currChar)) && currChar != '_')) {
			break;
		}

		charList.push_back(currChar);
		colCount++;
	}

	createIdentifierToken(std::string(charList.begin(), charList.end()), columnCount, lineCount);
	columnCount = colCount - 1;
	return;
}

// create a new identifier token
void Tokenizer::createIdentifierToken(std::string identifierName, int colCount, int lineCount) {
	Token newToken = Token(IDENTIFIER, lineCount, colCount, identifierName);
	tokenList.push_back(newToken);
}

// check if token is a reserved word
bool Tokenizer::isReservedWord(std::string line, int columnCount, std::string word) {
	if (columnCount + word.length() - 1 < line.length()) {
		for (int i = 0; i < word.length(); i++) {
			if (word.at(i) != line.at(columnCount + i)) {
				return false;
			}
		}

		return true;
	}
	else {
		return false;
	}
}

// check the next character
bool Tokenizer::checkNextChar(std::string line, int columnCount, char c) {
	if (columnCount + 1 < line.length()) {
		char nextChar = line.at(columnCount + 1);

		if (nextChar == c) {
			return true;
		}
	}

	return false;
}

