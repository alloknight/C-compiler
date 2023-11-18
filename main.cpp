#include "node.h"
extern ASTNode *root;
extern int yyparse();

int main(int argc, char** argv) {
    yyparse();
    FunctionNode* functionRoot = dynamic_cast<FunctionNode*>(root);// root in type functionNode

    if (root != nullptr)  {
	std::ofstream output("code.s");
	if (output.is_open()) {
            functionRoot->codeGen(output);
            functionRoot->statement().codeGen(output);
            output.close();
        }
        else{
            std::cerr << "cant open file" << std::endl;
        }
    }
    return 0;
}
