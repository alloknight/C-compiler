%{
#include "node.h"
#include "parse.tab.h"
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
#define TOKEN(type) (yylval.token = type)

extern void yyerror(const char* s);
%}

%%

[ \t\n]             ; // Ignore whitespace
[0-9]+                { SAVE_TOKEN; return INTEGER; }
"return"              { SAVE_TOKEN; return RETURN_KEYWORD;}
"int"                 { SAVE_TOKEN; return INT_KEYWORD;}
[a-zA-Z]+             { SAVE_TOKEN; return IDENTIFIER; }
"("                   { return TOKEN(LEFT_BRACE);}
")"                   { return TOKEN(RIGHT_BRACE);}
"{"                   { return TOKEN(LEFT_PAREN);}
"}"                   { return TOKEN(RIGHT_PAREN);}
"+"                   { return TOKEN(PLUS);}
"-"                   { return TOKEN(MINUS);}
"*"                   { return TOKEN(MULT);}
"/"                   { return TOKEN(DIV);}

.                 { yyerror("Invalid character"); }

%%

int yywrap() {
    return 1;
}
