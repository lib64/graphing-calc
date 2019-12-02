#ifndef LEXER_H
#define LEXER_H

#include "lexertoken.h"

#include <vector>
#include <regex>

using std::vector;
using std::regex;

class Lexer
{
    string _expr;
    size_t _index;

    regex *_intRegex;
    regex *_floatRegex;
    regex *_identifierRegex;

public:

    static const vector<string> OPERATORS;
    static const vector<string> FUNCTIONS;

    const static std::string REGEX_INT_LITERAL;
    const static std::string REGEX_FLOAT_LITERAL;
    const static std::string REGEX_IDENTIFIER;

    Lexer(const string &expr);
    ~Lexer();

    vector<LexerToken> lex();
};

#endif // LEXER_H
