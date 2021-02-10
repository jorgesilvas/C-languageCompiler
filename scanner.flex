%{
#include "parser.h"
#include <stdlib.h>
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
\n { yyline++;}

\-?[0-9]+ {
   yylval.intv = atoi(yytext);
   return INT;
}

true {
    yylval.boolv = true;
    return BOOL;
}


"+" { return PLUS; }
"-" { return MINUS; }
"/" { return DIV;}
"*" { return MULT; }
"%" { return MOD; }
"{" { return LBRACE; }
"}" { return RBRACE; }
"(" { return LPAREN; }
")" { return RPAREN; }
";" { return SEMICOLON; }
"," { return COMMA; }
">" { return GREATER; }
"<" { return LESS; }
">=" { return GREATERTHAN; }
"<=" { return LESSTHAN; }
"==" { return EQUALS; }
"=" { return EQUAL; }
"main" { return MAIN; }
"while" { return WHILE; }
"scan_int" { return SCAN_INT; }
"print_int" { return PRINT_INT; }
"print_str" {return PRINT_STR;  }
"if" { return IF; }
"else" { return ELSE; }
"int" { return D_INT; }
"bool" { return D_BOOL; }
"return" {return RETURN; }

[a-z][a-zA-Z0-9]* {
    yylval.nameValue = strdup(yytext);
    return NAME;
}

\&[a-z][a-zA-Z0-9]* {
    yylval.nameValue = strdup(yytext);
    return NAMESCAN;
}

\"[^\"]*\" {
    yylval.stringvalue = strdup(yytext);
    return STRING;
}
.  { yyerror("unexpected character"); }
%%
