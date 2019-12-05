#ifndef LEXERTOKEN_H
#define LEXERTOKEN_H

#include <string>
using std::string;

class LexerToken
{
public:
    enum class Type {
        INT_LIT,
        FLOAT_LIT,
        IDENTIFIER,
        LPAREN,
        RPAREN,
        SQRT,
        ABS,
        SIN,
        COS,
        TAN,
        ASIN,
        ACOS,
        ATAN,
        SINH,
        COSH,
        TANH,
        ASINH,
        ACOSH,
        ATANH,
        OP_ADD,
        OP_SUB,
        OP_MUL,
        OP_DIV,
        OP_POW
    };
private:
    LexerToken::Type _type;
    string _value;
    size_t _col;
public:
    LexerToken(LexerToken::Type type, const std::string &value, size_t col);
    LexerToken::Type type() const;
    string value() const;
    size_t col() const;

};

#endif // LEXERTOKEN_H
