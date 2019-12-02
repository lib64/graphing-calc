#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "astnode.h"

class Interpreter
{
    AstNode *_expr;
    double _x;
public:
    Interpreter(AstNode *expr);

    double interpret(double x);
    void interpretMain(AstNode *node);
    void interpretRoot(AstNode *node);
    void interpretAdditive(AstNode *node);
    void interpretMultiplicative(AstNode *node);
    void interpretUnary(AstNode *node);
    void interpretInt(AstNode *node);
    void interpretFloat(AstNode *node);
    void interpretIdentifier(AstNode *node);
};

#endif // INTERPRETER_H
