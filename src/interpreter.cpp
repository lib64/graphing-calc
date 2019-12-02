#include "interpreter.h"

#include <stdexcept>

Interpreter::Interpreter(AstNode *expr)
{
    _expr = expr;
}

double Interpreter::interpret(double x)
{
    _x = x;
    AstNode *root = _expr;
    interpretMain(root);
    return root->getResult();
}

void Interpreter::interpretMain(AstNode *node)
{
    for(size_t i = 0; i < node->childCount(); i++) {
        interpretMain(node->getChild(i));
    }

    switch(node->getType()) {
    case AstNode::Type::ROOT: interpretRoot(node); break;
    case AstNode::Type::ADDITIVE: interpretAdditive(node); break;
    case AstNode::Type::MULTIPLICATIVE: interpretMultiplicative(node); break;
    case AstNode::Type::UNARY: interpretUnary(node); break;
    case AstNode::Type::INT_LITERAL: interpretInt(node); break;
    case AstNode::Type::FLOAT_LITERAL: interpretFloat(node); break;
    case AstNode::Type::IDENTIFIER: interpretIdentifier(node); break;
    }
}

void Interpreter::interpretRoot(AstNode *node)
{
    node->setResult(node->getChild(0)->getResult());
}

void Interpreter::interpretAdditive(AstNode *node)
{
    AstNode *left = node->getChild(0);
    AstNode *right = node->getChild(1);

    double res;
    if(node->getValue() == "+") {
        res = left->getResult() + right->getResult();
    } else if(node->getValue() == "-") {
        res = left->getResult() - right->getResult();
    } else {
        throw std::invalid_argument("evaluateAdditive: bad value" + node->getValue());
    }
    node->setResult(res);
}

void Interpreter::interpretMultiplicative(AstNode *node)
{
    AstNode *left = node->getChild(0);
    AstNode *right = node->getChild(1);

    double res;
    if(node->getValue() == "*") {
        res = left->getResult() * right->getResult();
    } else if(node->getValue() == "/") {
        res = left->getResult() / right->getResult();
    } else {
        throw std::invalid_argument("evaluateMultiplicative: bad value");
    }
    node->setResult(res);
}

void Interpreter::interpretUnary(AstNode *node)
{
    AstNode *left = node->getChild(0);
    node->setResult(-left->getResult());
}

void Interpreter::interpretInt(AstNode *node)
{
    long val = std::stol(node->getValue());
    node->setResult(val);
}

void Interpreter::interpretFloat(AstNode *node)
{
    double val = std::stod(node->getValue());
    node->setResult(val);
}

void Interpreter::interpretIdentifier(AstNode *node)
{
    node->setResult(_x);
}
