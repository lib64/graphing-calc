#include "parser.h"

void Parser::expect(LexerToken::Type type)
{
    if(_current >= _tokens.size()) {
        throw std::invalid_argument("expect: out of tokens");
    }

    if(_tokens.at(_current).type() != type) {
        throw std::invalid_argument("expected token");
    }
}

bool Parser::accept(LexerToken::Type type)
{
    if(_current >= _tokens.size()) {
        return false;
    }
    if(_tokens.at(_current).type() == type) {
        ++_current;
        return true;
    }
    return false;
}

void Parser::unaccept()
{
    if(_current > 0) {
        --_current;
    }
}

void Parser::skip()
{
    if(_current >= _tokens.size()) {
        throw std::invalid_argument("skip: out of tokens.");
    }
    ++_current;
}

Parser::Parser(vector<LexerToken> &tokens)
{
    _tokens = tokens;
    _current = 0;
}

AstNode *Parser::parseMain()
{
    return parseExpr();
}

AstNode *Parser::parseExpr()
{
    return parseAdditive();
}

AstNode *Parser::parseAdditive()
{
    AstNode *left = parseMultiplicative();
    while(accept(LexerToken::Type::OP_ADD) ||
          accept(LexerToken::Type::OP_SUB)) {

        unaccept();
        LexerToken tok = _tokens.at(_current);
        skip();

        AstNode *right = parseMultiplicative();
        AstNode *parent = new AstNode(AstNode::Type::ADDITIVE, tok.value(), tok.col());
        parent->addChild(left);
        parent->addChild(right);
        left = parent;
    }
    return left;
}

AstNode *Parser::parseMultiplicative()
{
    AstNode *left = parseUnary();
    while(accept(LexerToken::Type::OP_MUL) ||
          accept(LexerToken::Type::OP_DIV)) {

        unaccept();
        LexerToken tok = _tokens.at(_current);
        skip();

        AstNode *right = parseUnary();
        AstNode *parent = new AstNode(AstNode::Type::MULTIPLICATIVE, tok.value(), tok.col());
        parent->addChild(left);
        parent->addChild(right);
        left = parent;
    }
    return left;
}

AstNode *Parser::parseUnary()
{
    if(accept(LexerToken::Type::OP_SUB)) {
       AstNode *right = parseUnary();

       unaccept();
       LexerToken tok = _tokens.at(_current);
       skip();

       AstNode *parent = new AstNode(AstNode::Type::UNARY, tok.value(), tok.col());
       parent->addChild(right);
       return parent;
    }
    return parsePrimary();
}

AstNode *Parser::parsePrimary()
{
    LexerToken tok = _tokens.at(_current++);
    AstNode *node = nullptr;
    switch(tok.type())
    {
    case LexerToken::Type::IDENTIFIER: node = new AstNode(AstNode::Type::IDENTIFIER, tok.value(), tok.col()); break;
    case LexerToken::Type::INT_LIT: node = new AstNode(AstNode::Type::INT_LITERAL, tok.value(), tok.col()); break;
    case LexerToken::Type::FLOAT_LIT: node = new AstNode(AstNode::Type::FLOAT_LITERAL, tok.value(), tok.col()); break;
    case LexerToken::Type::LPAREN:
    {
        AstNode *expr = parseExpr();
        expect(LexerToken::Type::RPAREN);
        return expr;
    }
    default:
        throw std::invalid_argument("Tok not primary:");
    }
    return node;
}
