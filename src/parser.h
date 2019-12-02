#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "lexertoken.h"
#include "astnode.h"

class Parser
{
    vector<LexerToken> _tokens;
    size_t _current;

    void expect(LexerToken::Type type);
    bool accept(LexerToken::Type type);
    void unaccept();
    void skip();

public:
    Parser(vector<LexerToken> &tokens);

    AstNode *parseMain();
    AstNode *parseExpr();
    AstNode *parseFunction();
    AstNode *parseAdditive();
    AstNode *parseMultiplicative();
    AstNode *parseUnary();
    AstNode *parsePrimary();

};

#endif // PARSER_H
