#ifndef ASTNODE_H
#define ASTNODE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class AstNode
{
public:
    enum class Type {
        ROOT,
        ADDITIVE,
        MULTIPLICATIVE,
        UNARY,
        INT_LITERAL,
        FLOAT_LITERAL,
        IDENTIFIER,
        FUNCTION,
    };
private:
    AstNode::Type _type;
    string _value;
    size_t _col;
    vector<AstNode *> _children;

    double _result;
public:
    AstNode(AstNode::Type type, const string &value, size_t col);

    void addChild(AstNode *child);
    AstNode *getChild(size_t index);
    size_t childCount() const;

    void print();
    AstNode::Type getType() const;
    string getValue() const;
    double getResult() const;
    void setResult(double result);
};

void printAst(AstNode *node, int depth);

#endif // ASTNODE_H
