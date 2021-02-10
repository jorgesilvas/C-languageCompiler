%token INT BOOL PLUS
%token MINUS DIV MULT MOD
%token LBRACE RBRACE LPAREN RPAREN
%token SEMICOLON COMMA
%token GREATER LESS GREATERTHAN LESSTHAN EQUALS EQUAL RETURN
%token MAIN WHILE IF ELSE
%token SCAN_INT PRINT_INT PRINT_STR
%token D_INT D_BOOL
%token NAME NAMESCAN STRING

// precedencias
%left MAIN D_INT D_BOOL EQUAL RETURN
%left SEMICOLON
%left GREATER LESS GREATERTHAN LESSTHAN EQUALS
%left PLUS MINUS
%left DIV MULT MOD



// Root-level grammar symbol
%start program;

// correspondem ás structs do ast.h
%union{
	int intv;
	bool boolv;
	char* stringvalue;
	Expr* exp;
	BoolExpr* boolExpVal;
	BoolExprList* boolexprlistV;
	CmdList* cmdListV;
	Cmd* cmdV;
	If* ifV;
	Else* elseV;
	While* whileV;
	PrintStr* printStrV;
	ScanInt* scanIntV;
	CharList* varlistValue;
	CharList* varlistValue2;
	char* nameValue;
	char* nameValueScan;
	Attrib* attribV;
	ReturnExpr* returnV;
}

%type <intv> INT;
%type <boolv> BOOL;
%type <stringvalue> STRING;
%type <exp> exp;
%type <boolExpVal> boolexp;
%type <cmdListV> cmdList;
%type <cmdV> cmd;
%type <ifV> if;
%type <elseV> else;
%type <whileV> while;
%type <printStrV> print;
%type <scanIntV> scan;
%type <varlistValue> varlist;
%type <varlistValue2> varlist2;
%type <nameValue> NAME;
%type <nameValueScan> NAMESCAN;
%type <attribV> attrib;
%type <boolexprlistV> boolexprlist;
%type <returnV> return;

%code requires {
	#include <stdio.h>
	#include <stdlib.h>
	#include "ast.h"

	extern int yylex();
	extern int yyline;
	extern char* yytext;
	extern FILE* yyin;
	extern void yyerror(const char* msg);

	CmdList* root;

}

%%

program:	D_INT MAIN LPAREN RPAREN LBRACE cmdList RBRACE		{root = $6;};

cmdList:	cmd cmdList		{$$ = cmdList($1, $2);}
  	|	cmd		{$$ = cmdList($1, NULL);};

cmd:	attrib 	{$$ = cmdattrib($1);}
	|	if		{$$ = cmdif($1);}
	|	while	{$$ = cmdwhile($1);}
	|	print	{$$ = cmdprintstr($1);}
	|	scan	{$$ = cmdscanint($1);};

print:	PRINT_STR LPAREN STRING varlist RPAREN SEMICOLON	{$$ = cmdprint_str_expr($3,$4);}
	|	PRINT_STR LPAREN STRING RPAREN SEMICOLON	{$$ = cmdprint_str_expr($3,NULL);}
	|	PRINT_STR LPAREN NAME RPAREN SEMICOLON {$$ = cmdprint_strname_expr($3);}
	|	PRINT_INT LPAREN NAME RPAREN SEMICOLON {$$ = cmdprint_strname_expr($3);};

scan:	SCAN_INT LPAREN STRING varlist2 RPAREN SEMICOLON	{$$ = cmdscan_expr($3,$4);}
	|	SCAN_INT LPAREN STRING RPAREN SEMICOLON		{$$ = cmdscan_expr($3,NULL);};


varlist: COMMA NAME varlist 	{ $$ = cmdcharlist($2, $3);}
	|	COMMA NAME 	{$$ = cmdcharlist($2, NULL);};

varlist2:	COMMA NAMESCAN varlist		{$$ = cmdcharlist($2, $3);}
	|	COMMA NAMESCAN		{$$ = cmdcharlist($2, NULL);};


while:	WHILE LPAREN boolexprlist RPAREN LBRACE cmdList RBRACE		{$$ = cmdwhile_boolexprlist($3,$6);}
	|	WHILE LPAREN boolexprlist RPAREN LBRACE cmdList return RBRACE		{$$ = cmdwhile_boolexprlist_return($3,$6,$7);}
	|	WHILE LPAREN exp LPAREN LBRACE cmdList RBRACE		{$$ = cmdwhile_expr($3,$6);}
	|	WHILE LPAREN exp LPAREN LBRACE cmdList return RBRACE		{$$ = cmdwhile_expr_return($3,$6,$7);};

if:		IF LPAREN exp RPAREN LBRACE cmdList RBRACE		{$$ = cmdif_expr($3,$6);}
	|	IF LPAREN exp RPAREN LBRACE cmdList return RBRACE		{$$ = cmdif_expr_return($3,$6,$7);}
	|	IF LPAREN boolexprlist RPAREN LBRACE cmdList RBRACE		{$$ = cmdif_boolexprlist($3,$6);}
	|	IF LPAREN boolexprlist RPAREN LBRACE cmdList return RBRACE		{$$ = cmdif_boolexprlist_return($3,$6,$7);}
	|	IF LPAREN exp RPAREN LBRACE cmdList RBRACE else		{$$ = cmdif_expr_else($3,$6,$8);}
	|	IF LPAREN boolexprlist RPAREN LBRACE cmdList RBRACE else		{$$ = cmdif_boolexpr_else($3,$6,$8);};

else:	ELSE LBRACE cmdList RBRACE		{$$ = cmdelse($3);};

attrib:		D_INT NAME EQUAL exp SEMICOLON		{$$ = attribexpr_ct($2, $4);}
  	|	NAME EQUAL exp SEMICOLON		{$$ = attribexpr($1, $3);}
  	|	D_INT NAME SEMICOLON	{$$ = nattrib($2);}
  	|	D_BOOL NAME EQUAL exp SEMICOLON		{$$ = attribexprbool($2, $4);}
  	|	D_BOOL NAME SEMICOLON		{$$ = nattribbool($2);};

return:		RETURN exp SEMICOLON 	{$$ = return_exp($2);};

boolexprlist:	boolexp	{$$ = bool_booleanexprlist($1,NULL);}
	|	exp		{$$ = expr_booleanexprlist($1,NULL);};

boolexp:	exp GREATER exp		{$$ = boolexpr($1,$3,GREATER);}
	|	exp LESS exp		{$$ = boolexpr($1,$3,LESS);}
	|	exp GREATERTHAN exp		{$$ = boolexpr($1,$3,GREATERTHAN);}
	|	exp LESSTHAN exp	{$$ = boolexpr($1,$3,LESSTHAN);}
	|	exp EQUALS exp	{$$ = boolexpr($1,$3,EQUALS);};

exp:	INT 	{$$ = ast_int($1);}
  	|	BOOL 	{$$ = ast_bool($1);}
	|	NAME 	{$$ = ast_expr_var($1);}
	|	exp PLUS exp 	{$$ = ast_oper(PLUS, $1, $3);}
  	|	exp MINUS exp 	{$$ = ast_oper(MINUS, $1, $3);}
  	|	exp DIV exp 	{$$ = ast_oper(DIV, $1, $3);}
  	|	exp MULT exp 	{$$ = ast_oper(MULT, $1, $3);}
  	|	exp MOD exp		{$$ = ast_oper(MOD, $1, $3);};

%%

void yyerror(const char* err){
    printf("Line %d: %s - '%s'\n",yyline,err,yytext);
}
