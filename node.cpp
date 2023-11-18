#include "node.h"

// NumericNode implementation
NumericNode::NumericNode(std::string value) : _value(std::stoi(value)) {}

void NumericNode::codeGen(std::ofstream& output) const {    
    if(output.is_open()){
        output << "mov\teax," <<_value << std::endl;
    }
}

int NumericNode::value() const{
    return _value;
}
// BinaryOperatorNode implementation
BinaryOperatorNode::BinaryOperatorNode(char op, ASTNode& left, ASTNode& right)
    : _op(op), _left(left), _right(right) {}

void BinaryOperatorNode::codeGen(std::ofstream& output) const {
    // First, evaluate the left operand and push the result onto the stack
    _left.codeGen(output);
    output << "\tpush eax" << std::endl;

    // Then, evaluate the right operand
    _right.codeGen(output);

    // Now, pop the left operand back into another register (e.g., EBX)
    output << "\tpop ebx" << std::endl;

    // Perform the operation based on the operator
    switch (_op) {
        case '+':
            output << "\tadd eax, ebx" << std::endl;
            break;
        case '-':
            output << "\tsub ebx, eax" << std::endl;
            output << "\tmov eax, ebx" << std::endl;
            break;
        case '*':
            output << "\timul eax, ebx" << std::endl;
            break;
        case '/':
            output << "\txchg eax, ebx" << std::endl; // Swap EAX and EBX
            output << "\tcdq" << std::endl; // Sign-extend EAX into EDX
            output << "\tidiv ebx" << std::endl;
            break;
        default:
            // Handle error: unknown operator
            break;
    }
}

// ReturnNode implementation
ReturnNode::ReturnNode(ASTNode& returnValue) : _returnValue(returnValue) {}

void ReturnNode::codeGen(std::ofstream& output) const {
    NumericNode* numericNode = dynamic_cast<NumericNode*>(&_returnValue);
    
   _returnValue.codeGen(output); 
    if(output.is_open()){
        output << "\tret" << std::endl;
    }
    
}

// FunctionNode implementation
FunctionNode::FunctionNode(std::string id,ASTNode& statement) : _id(id),_statement(statement) {}

void FunctionNode::codeGen(std::ofstream& output) const {
    std::string code = ".globl "+ _id+ "\n"+ _id+ ":";   	   
    if(output.is_open()){ 
        output << code << std::endl;
    }
}
const ASTNode& FunctionNode::statement() const{
    return _statement;
}
