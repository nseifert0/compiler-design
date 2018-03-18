#include "parser.hpp"

void Parser::parse() {
}

void Parser::pushToken() {
	tokenQueue.push_back(lexer.lex());
}