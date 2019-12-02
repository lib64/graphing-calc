#include "astnode.h"

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
