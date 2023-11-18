#ifndef NODE_H_
#define NODE_H_
#include <iostream>
#include <string>
#include <fstream>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void codeGen(std::ofstream& output) const = 0;
};

class NumericNode : public ASTNode {
public:
    NumericNode(std::string value);
    void codeGen(std::ofstream& output) const override;
    int value() const;
private:
    int _value;
};

class BinaryOperatorNode : public ASTNode {
public:
    BinaryOperatorNode(char op, ASTNode &left, ASTNode &right);
    void codeGen(std::ofstream& output) const override;
private:
    char _op;
    ASTNode& _left;
    ASTNode& _right;
};

class ReturnNode : public ASTNode{
public:
   ReturnNode(ASTNode &returnValue);
   void codeGen(std::ofstream& output) const override;
private:
   ASTNode& _returnValue;   
};

class FunctionNode : public ASTNode{
public:
    FunctionNode(std::string id,ASTNode &statement);
    void codeGen(std::ofstream& output) const override;
    const ASTNode& statement() const;    
private:
    std::string _id;
    ASTNode& _statement;
};

#endif
