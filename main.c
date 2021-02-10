#include <stdio.h>
#include "parser.h"


void printcharlist(CharList* , int );
void printvariaveis(Expr*  , char*  , int );
void printprintstr(PrintStr*  , int );
void printscanint(ScanInt* , int );
void printAttrib(Attrib* , int );
void printwhile(While* , int );
void printelse(Else* , int );
void printCmd(Cmd* , int );
void printcmdlist(CmdList* , int );
void printIf(If* , int );
void printspaces(int );
void printExpr(Expr*  , int );
void printboolexpr(BoolExpr* , int );
void printBoolExprList(BoolExprList*  , int );
void printreturn(ReturnExpr*  , int );



void printcharlist(CharList* varlist, int spaces){
  printspaces(spaces);
  printf(" %s\n", varlist->value);

  if(varlist->next != NULL){
    printcharlist(varlist->next, spaces);
  }
}

void printvariaveis(Expr* expr , char* name , int spaces){
	printspaces(spaces);
	printf("%s\n" , name);
	printspaces(spaces + 3);
	printf("=\n");
	printExpr(expr, spaces + 3);
}

void printprintstr(PrintStr* cmdP , int spaces){
    if(cmdP->value==NULL){
        printspaces(spaces);
        printf("print_int\n");
        printspaces(spaces + 3);
	    printf("%s\n" , cmdP->name);
    }
    else{
        printspaces(spaces);
        printf("print_str\n");
        printspaces(spaces + 3);
        printf("%s\n" , cmdP->value);
    }
	if(cmdP->varList != NULL){
    	printcharlist(cmdP->varList, spaces + 3);
  }
}

void printscanint(ScanInt* cmdS, int spaces){
	printspaces(spaces);
	printf("scan_int\n");
	printspaces(spaces + 3);
	printf("%s" , cmdS->value);
	if(cmdS->varList != NULL){
    	printcharlist(cmdS->varList, spaces + 3);
  }
}

void printAttrib(Attrib* cmdA, int spaces){
	if(cmdA->kind == A_ATTRIBST){
		printvariaveis(cmdA->attr.att.value, cmdA->attr.att.name , spaces + 3);
	}
	else if(cmdA->kind == A_ATTRIBCT){
		printspaces(spaces);
		printf("int\n");
		printvariaveis(cmdA->attr.attct.value, cmdA->attr.attct.name , spaces + 3);
	}
	else if(cmdA->kind == A_ATTRIBCTBOOL){
		printspaces(spaces);
		printf("bool\n");
		printvariaveis(cmdA->attr.attctbool.value, cmdA->attr.attctbool.name , spaces + 3);
	}
	else if(cmdA->kind == A_NATTRIBBOOL){
		printspaces(spaces);
		printf("bool\n");
		printspaces(spaces+3);
		printf("%s\n", cmdA->attr.attrb.name);
	}
	else if(cmdA->kind == A_NATTRIB){
		printspaces(spaces);
		printf("int\n");
		printspaces(spaces+3);
		printf("%s\n", cmdA->attr.name);
	}
}

void printwhile(While* cmdW, int spaces){
	if(cmdW->kind == W_EXPR){
		printspaces(spaces);
		printf("while\n");
		printExpr(cmdW->type.expr, spaces + 3);
		printcmdlist(cmdW->teste,spaces + 3);
	}
	else if(cmdW->kind == W_BOOLEXPR){
		printspaces(spaces);
		printf("while\n");
		printBoolExprList(cmdW->type.boolexprValue, spaces + 3);
		printcmdlist(cmdW->teste,spaces + 3);
	}
    else if(cmdW->kind == W_BOOLEXPR_RETURN){
		printspaces(spaces);
		printf("while\n");
		printBoolExprList(cmdW->type.boolexprValue, spaces + 3);
		printcmdlist(cmdW->teste,spaces + 3);
        printspaces(spaces +6);
        printf("return\n");
        printreturn(cmdW->wReturn.retvalue,spaces + 6);
	}
    else if(cmdW->kind == W_EXPR_RETURN){
		printspaces(spaces);
		printf("while\n");
		printBoolExprList(cmdW->type.boolexprValue, spaces + 3);
		printcmdlist(cmdW->teste,spaces + 3);
        printspaces(spaces +6);
        printf("return\n");
        printreturn(cmdW->wReturn.retvalue,spaces + 6);
	}
}
void printreturn(ReturnExpr* returnv , int spaces){
    printExpr(returnv->exprR,spaces + 3);
}

void printelse(Else* cmdE, int spaces){
	printspaces(spaces);
	printf("else\n");
	printcmdlist(cmdE->teste ,spaces+3);
}

void printCmd(Cmd* cmd, int spaces){
	if(cmd->kind == C_WHILE)
		printwhile(cmd->type.While , spaces + 3);
	else if(cmd->kind == C_IF)
		printIf(cmd->type.If , spaces + 3);
	else if(cmd->kind == C_PRINTSTR)
		printprintstr(cmd->type.PrintStr , spaces + 3);
	else if(cmd->kind == C_SCANINT)
		printscanint(cmd->type.ScanInt , spaces + 3);
	else if(cmd->kind == C_ATTRIB)
		printAttrib(cmd->type.Attrib, spaces + 3);
}

void printcmdlist(CmdList* root, int spaces){
    printCmd(root->Cmd, spaces);

    while(root->next != NULL){
      root = root->next;
      printCmd(root->Cmd, spaces);
    }
}

void printIf(If* cmdI, int spaces){
	if(cmdI->kind == IF_EXPR){
		printspaces(spaces);
		printf("if\n");
		printExpr(cmdI->type.exprValue, spaces + 3);
		printcmdlist(cmdI->teste, spaces + 6);
	}

    if(cmdI->kind == IF_EXPR_RETURN){
		printspaces(spaces);
		printf("if\n");
		printExpr(cmdI->type.exprValue, spaces + 3);
		printcmdlist(cmdI->teste, spaces + 6);
        printspaces(spaces +6);
        printf("return\n");
        printreturn(cmdI->wReturn.retvalue,spaces + 6);
	}

    else if(cmdI->kind == IF_BOOLEXPR){
    	printspaces(spaces);
    	printf("if\n");
    	printBoolExprList(cmdI->type.boolexprValue, spaces + 3);
    	printcmdlist(cmdI->teste , spaces + 6);
    }

    if(cmdI->kind == IF_BOOLEXPR_RETURN){
		printspaces(spaces);
		printf("if\n");
		printBoolExprList(cmdI->type.boolexprValue, spaces + 3);
		printcmdlist(cmdI->teste, spaces + 6);
        printspaces(spaces +6);
        printf("return\n");
        printreturn(cmdI->wReturn.retvalue,spaces + 6);
	}

    else if(cmdI->kind == IFELSE_EXPR){
    	printspaces(spaces);
		printf("if\n");
		printExpr(cmdI->type.exprValue, spaces + 3);
		printcmdlist(cmdI->teste, spaces + 6);
		printelse(cmdI->ifElse.elseValue, spaces);
    }
    else if(cmdI->kind == IFELSE_BOOLEXPR){
    	printspaces(spaces);
    	printf("if\n");
    	printBoolExprList(cmdI->type.boolexprValue, spaces + 3);
    	printcmdlist(cmdI->teste, spaces + 6);
    	printelse(cmdI->ifElse.elseValue,spaces);
    }
}

void printspaces(int spaces){
	int i = 0;
	while(spaces != i){
		printf(" ");
		i++;
	}
}

void printExpr(Expr* expr , int spaces){
	if(expr->kind == E_INTEGER){
		printspaces(spaces);
		printf("%d\n", expr->attr.value);
	}
	else if(expr->kind == E_BOOL){
		printspaces(spaces);
		printf("%d\n", expr->attr.attbool.value);
	}
	else if(expr->kind == E_VAR){
		printspaces(spaces);
		printf("%s\n", expr->attr.var);
	}
	else if(expr->kind == E_OPER){
        printspaces(spaces);
		if(expr->attr.op.operate == PLUS){
			printf("+\n");
		}
		else if(expr->attr.op.operate == MINUS){
			printf("-\n");
		}
		else if(expr->attr.op.operate == DIV){
			printf("/\n");
		}
		else if(expr->attr.op.operate == MULT){
			printf("*\n");
		}
		else if(expr->attr.op.operate == MOD){
			printf("%c\n", '%');
		}

		printExpr(expr->attr.op.left, spaces+3);
    	printExpr(expr->attr.op.right, spaces+3);
	}
}

void printboolexpr(BoolExpr* bexpr, int spaces){
	if(bexpr->kind == B_BOOLOP){
		printspaces(spaces);
    	if(bexpr->attr.op.operate == GREATER){
	        printf(">\n");
	    }
	    else if(bexpr->attr.op.operate == LESS){
	        printf("<\n");
	    }
	    else if(bexpr->attr.op.operate == GREATERTHAN){
	        printf(">=\n");
	    }
	    else if(bexpr->attr.op.operate == LESSTHAN){
	        printf("<=\n");
	    }
	    else if(bexpr->attr.op.operate == EQUALS){
	        printf("==\n");
	    }
    printExpr(bexpr->attr.op.left, spaces+3);
    printExpr(bexpr->attr.op.right, spaces+3);
    }
}

void printBoolExprList(BoolExprList* bexprlist , int spaces){
	if(bexprlist->kind == B_EXPR){
    	printExpr(bexprlist->list.type.expr, spaces);
  	}
  	else if(bexprlist->kind == B_BOOLEXPR){
   		printboolexpr(bexprlist->list.type.value, spaces);
  	}
  	if(bexprlist->list.next != NULL){
    	bexprlist = bexprlist->list.next;
    	printBoolExprList(bexprlist, spaces);
  }
}

int main(int argc, char** argv){
    if(argc != 1){
        yyin = fopen(argv[1],"r");
        if(!yyin){
            printf("'%s': Could Not Opening file\n",argv[1]);
            return 1;
        }
        if(yyparse() == 0){
            printf("int main()\n");
    		printCmd(root->Cmd, 0);

		    while(root->next != NULL){
		      root = root->next;
		      printCmd(root->Cmd, 0);
		    }
            return 0;
        }
        printf("ERROR\n");
        return 1;
    }
}
