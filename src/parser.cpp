#include "parser.h"

void Parser::expect(LexerToken::Type type)
{
    if(_current >= _tokens.size()) {
        throw std::invalid_argument("expect: out of tokens");
    }

    if(_tokens.at(_current).type() != type) {
        throw std::invalid_argument("expected token.");
    }
    ++_current;
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
    AstNode *left = parseExponent();
    while(accept(LexerToken::Type::OP_MUL) ||
          accept(LexerToken::Type::OP_DIV)) {

        unaccept();
        LexerToken tok = _tokens.at(_current);
        skip();

        AstNode *right = parseExponent();
        AstNode *parent = new AstNode(AstNode::Type::MULTIPLICATIVE, tok.value(), tok.col());
        parent->addChild(left);
        parent->addChild(right);
        left = parent;
    }
    return left;
}

AstNode *Parser::parseExponent()
{
    AstNode *left = parseUnary();
    while(accept(LexerToken::Type::OP_POW)) {

        unaccept();
        LexerToken tok = _tokens.at(_current);
        skip();

        AstNode *right = parseUnary();
        AstNode *parent = new AstNode(AstNode::Type::EXPONENT, tok.value(), tok.col());
        parent->addChild(left);
        parent->addChild(right);
        left = parent;
    }
    return left;
}

AstNode *Parser::parseUnary()
{
    LexerToken tok = _tokens.at(_current);

    if(accept(LexerToken::Type::OP_SUB)) {
       AstNode *right = parseUnary();

       AstNode *parent = new AstNode(AstNode::Type::UNARY, tok.value(), tok.col());
       parent->addChild(right);
       return parent;
    }
    return parsePrimary();
}

AstNode *Parser::parsePrimary()
{
    LexerToken tok = _tokens.at(_current++);
    switch(tok.type())
    {
    case LexerToken::Type::IDENTIFIER: return new AstNode(AstNode::Type::IDENTIFIER, tok.value(), tok.col());
    case LexerToken::Type::INT_LIT: return new AstNode(AstNode::Type::INT_LITERAL, tok.value(), tok.col());
    case LexerToken::Type::FLOAT_LIT: return new AstNode(AstNode::Type::FLOAT_LITERAL, tok.value(), tok.col());
    case LexerToken::Type::ABS:
    case LexerToken::Type::SQRT:
    case LexerToken::Type::SIN:
    case LexerToken::Type::COS:
    case LexerToken::Type::TAN:
    case LexerToken::Type::ASIN:
    case LexerToken::Type::ACOS:
    case LexerToken::Type::ATAN:
    case LexerToken::Type::SINH:
    case LexerToken::Type::COSH:
    case LexerToken::Type::TANH:
    case LexerToken::Type::ASINH:
    case LexerToken::Type::ACOSH:
    case LexerToken::Type::ATANH:

    {
        AstNode *parent = new AstNode(AstNode::Type::FUNCTION, tok.value(), tok.col());
        expect(LexerToken::Type::LPAREN);
        AstNode *child = parseExpr();
        expect(LexerToken::Type::RPAREN);
        parent->addChild(child);
        return parent;
    }
    case LexerToken::Type::LPAREN:
    {
        AstNode *expr = parseExpr();
        expect(LexerToken::Type::RPAREN);
        return expr;
    }
    default:
        throw std::invalid_argument("invalid primary token.");
    }
}
