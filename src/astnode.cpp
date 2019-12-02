#include "astnode.h"

#include <iostream>

AstNode::AstNode(AstNode::Type type, const std::string &value, size_t col)
{
    _type = type;
    _value = value;
    _col = col;
}

void AstNode::addChild(AstNode *child)
{
    _children.push_back(child);
}

AstNode *AstNode::getChild(size_t index)
{
    return _children.at(index);
}

size_t AstNode::childCount() const
{
    return _children.size();
}

std::string AstNode::to_string()
{
    return _value;
}

AstNode::Type AstNode::getType() const
{
    return _type;
}

string AstNode::getValue() const
{
    return _value;
}

double AstNode::getResult() const
{
    return _result;
}

void AstNode::setResult(double result)
{
    _result = result;
}

void printAst(AstNode *node, int depth)
{
    for(int i = 0; i < depth; i++) {
        std::cout << "  ";
    }

    std::cout << node->to_string() << std::endl;

    for(int i = 0; i < node->childCount();i++) {
        printAst(node->getChild(i), depth + 1);
    }
}
