#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"


Expr* ast_int(int a) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = a;
  return node;
}

Expr* ast_bool(bool b) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_BOOL;
  node->attr.attbool.value = b;
  return node;
}


Expr* ast_expr_var(char* n){
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_VAR;
  node->attr.var = n;
  return node;
}

Expr* ast_oper(int oper, Expr* left, Expr* right) {
  Expr* node = (Expr*) malloc(sizeof(Expr));
  node->kind = E_OPER;
  node->attr.op.operate = oper;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

CmdList* cmdList(Cmd* cmd, CmdList* next){
  CmdList* list = (CmdList*) malloc(sizeof(CmdList));
  list->Cmd = cmd;
  list->next = next;
  return list;
}

Cmd* cmdwhile(While* whileexp){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_WHILE;
  node->type.While = whileexp;
  return node;
}

Cmd* cmdif(If* ifExp){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_IF;
  node->type.If = ifExp;
  return node;
}

Cmd* cmdprintstr(PrintStr* printExp){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_PRINTSTR;
  node->type.PrintStr = printExp;
  return node;
}

Cmd* cmdscanint(ScanInt* scanExp){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_SCANINT;
  node->type.ScanInt = scanExp;
  return node;
}

CharList* cmdcharlist(char* name, CharList* next){
  CharList* list = (CharList*) malloc(sizeof(CharList));
  list->value = name;
  list->next = next;
  return list;
}

PrintStr* cmdprint_str_expr(char* v,CharList* charList){
  PrintStr* node = (PrintStr*) malloc(sizeof(PrintStr));
  node->value = v;
  node->varList = charList;
  return node;
}

ScanInt* cmdscan_expr(char* v, CharList* charlist){
  ScanInt* node = (ScanInt*) malloc(sizeof(ScanInt));
  node->value = v;
  node->varList = charlist;
  return node;
}

While* cmdwhile_expr(Expr* expW, CmdList* cmdlist){
  While* node = (While*) malloc(sizeof(While));
  node->kind = W_EXPR;
  node->type.expr= expW;
  node->teste= cmdlist;
  return node;
}

While* cmdwhile_boolexprlist(BoolExprList* value , CmdList* cmdlist){
  While* node = (While*) malloc(sizeof(While));
  node->kind = W_BOOLEXPR;
  node->type.boolexprValue = value;
  node->teste = cmdlist ;
  return node;
}

If* cmdif_expr(Expr* expI, CmdList* cmdlist){
  If* node = (If*) malloc(sizeof(If));
  node->kind = IF_EXPR;
  node->type.exprValue = expI;
  node->teste= cmdlist;
  return node;
}

If* cmdif_boolexprlist(BoolExprList* value, CmdList* cmdlist){
    If* node = (If*) malloc(sizeof(If));
    node->kind = IF_BOOLEXPR;
    node->type.boolexprValue = value;
    node->teste = cmdlist;
    return node;
}

If* cmdif_expr_else(Expr* expI , CmdList* cmdlist, Else* expelse){
  If* node = (If*) malloc(sizeof(If));
  node->kind = IFELSE_EXPR;
  node->type.exprValue = expI;
  node->teste = cmdlist;
  node->ifElse.elseValue = expelse;
  return node;
}

If* cmdif_boolexpr_else (BoolExprList* value , CmdList* cmdlist , Else* boolelse){
  If* node = (If*) malloc(sizeof(If));
  node->kind = IFELSE_BOOLEXPR;
  node->type.boolexprValue= value;
  node->teste = cmdlist;
  node->ifElse.elseValue = boolelse;
  return node;
}

Else* cmdelse(CmdList* cmdlist){
  Else* node = (Else*) malloc(sizeof(Else));
  node->teste = cmdlist;
  return node;
}

Attrib* attribexpr_ct(char* var, Expr* expr){
  Attrib* node = (Attrib*) malloc(sizeof(Attrib));
  node->kind= A_ATTRIBCT;
  node->attr.attct.value = expr;
  node->attr.attct.name = var;
  return node;
}

Attrib* attribexpr(char* var, Expr* expr){
  Attrib* node=(Attrib*) malloc(sizeof(Attrib));
  node->kind = A_ATTRIBST;
  node->attr.att.value = expr;
  node->attr.att.name = var;
  return node;
}

Attrib* nattrib(char* var){
  Attrib* node = (Attrib*) malloc(sizeof(Attrib));
  node->kind= A_NATTRIB;
  node->attr.name= var;
  return node;
}

BoolExpr* boolexpr(Expr* left, Expr* right , int oper){
  BoolExpr* node = (BoolExpr*) malloc(sizeof(BoolExpr));
  node->kind = B_BOOLOP;
  node->attr.op.operate= oper;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

BoolExprList* bool_booleanexprlist(BoolExpr* value , BoolExprList* next){
  BoolExprList* list = (BoolExprList*) malloc(sizeof(BoolExprList));
  list->kind= B_BOOLEXPR;
  list->list.type.value = value;
  list->list.next = next;
  return list;
}

BoolExprList* expr_booleanexprlist(Expr* value , BoolExprList* next){
  BoolExprList* list = (BoolExprList*) malloc(sizeof(BoolExprList));
  list->kind= B_EXPR;
  list->list.type.expr = value;
  list->list.next = next;
  return list;
}

Attrib* nattribbool(char* var){
  Attrib* node = (Attrib*) malloc(sizeof(Attrib));
  node->kind= A_NATTRIBBOOL;
  node->attr.attrb.name= var;
  return node;
}

Attrib* attribexprbool(char* var, Expr* expr){
  Attrib* node = (Attrib*) malloc(sizeof(Attrib));
  node->kind = A_ATTRIBCTBOOL;
  node->attr.attctbool.value = expr;
  node->attr.attctbool.name = var;
  return node;
}

Cmd* cmdattrib(Attrib* attrib){
  Cmd* node = (Cmd*) malloc(sizeof(Cmd));
  node->kind = C_ATTRIB;
  node->type.Attrib = attrib;
  return node;
}


PrintStr* cmdprint_strname_expr(char* name){
    PrintStr* node = (PrintStr*) malloc(sizeof(PrintStr));
    node->name = name;
    return node;
}

ReturnExpr* return_exp(Expr* expr){
    ReturnExpr* node = (ReturnExpr*) malloc(sizeof(ReturnExpr));
    node->exprR = expr;
    return node;
}


While* cmdwhile_boolexprlist_return(BoolExprList* value , CmdList* cmdlist, ReturnExpr* retvalue){
  While* node = (While*) malloc(sizeof(While));
  node->kind = W_BOOLEXPR_RETURN;
  node->type.boolexprValue = value;
  node->wReturn.retvalue= retvalue;
  node->teste = cmdlist ;
  return node;
}


While* cmdwhile_expr_return(Expr* expW, CmdList* cmdlist , ReturnExpr* retvalue){
    While* node = (While*) malloc(sizeof(While));
    node->kind = W_EXPR_RETURN;
    node->type.expr = expW;
    node->wReturn.retvalue= retvalue;
    node->teste = cmdlist ;
    return node;
}

If* cmdif_expr_return(Expr* exprI, CmdList* cmdlist, ReturnExpr* retvalue){
    If* node = (If*) malloc(sizeof(If));
    node->kind = IF_EXPR_RETURN;
    node->type.exprValue = exprI;
    node->teste= cmdlist;
    node->wReturn.retvalue = retvalue;
    return node;
}

If* cmdif_boolexprlist_return(BoolExprList* exprI, CmdList* cmdlist, ReturnExpr* retvalue){
    If* node = (If*) malloc(sizeof(If));
    node->kind = IF_BOOLEXPR_RETURN;
    node->type.boolexprValue = exprI;
    node->teste= cmdlist;
    node->wReturn.retvalue = retvalue;
    return node;
}
