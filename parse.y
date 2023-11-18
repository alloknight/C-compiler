%{
#include "node.h"
ASTNode *root = nullptr;
 
extern int yylex();
void yyerror(const char*);

%}

%union {
    int token;
    std::string *string;
    ASTNode *node;
}

%token <string> IDENTIFIER INTEGER RETURN_KEYWORD INT_KEYWORD

%token <token> LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE 
%token <token> PLUS MINUS MULT DIV

%type <node> expression program statement function factor term 

%left PLUS MINUS
%left MUL DIV

%start program

%%

program: function {root = $1;} 
       ;
function: INT_KEYWORD IDENTIFIER LEFT_BRACE RIGHT_BRACE LEFT_PAREN statement RIGHT_PAREN {$$ = new FunctionNode(*$2,*$6);} //$2 = identifier, $6 = statment.
	;
expression: factor
    | expression PLUS expression {$$ = new BinaryOperatorNode('+', *$1, *$3); }
    | expression MINUS expression {$$ = new BinaryOperatorNode('-', *$1, *$3); }
    | term
    ;
term: factor MULT factor {$$ = new BinaryOperatorNode('*', *$1, *$3); }
    | factor DIV factor {$$ = new BinaryOperatorNode('/', *$1, *$3); }
    ;
factor: INTEGER {$$ = new NumericNode(*$1); }
    ;
statement: RETURN_KEYWORD expression {$$ = new ReturnNode(*$2);}
    ;
%%

void yyerror(const char *s) {
    std::cerr << "Error: " << s << std::endl;
}
