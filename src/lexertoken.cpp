#include "lexertoken.h"

LexerToken::LexerToken(Type type, const std::string &value, size_t col)
{
    _type = type;
    _value = value;
    _col = col;
}

LexerToken::Type LexerToken::type() const
{
    return _type;
}

string LexerToken::value() const
{
    return _value;
}

size_t LexerToken::col() const
{
    return _col;
}

