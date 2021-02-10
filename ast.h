#ifndef _ast_h_
#define _ast_h_
#include <stdbool.h>

typedef struct attrib{
  enum{
    A_ATTRIBST,
    A_ATTRIBCT,
    A_ATTRIBCTBOOL, //
    A_NATTRIBBOOL, //
    A_NATTRIB
  }kind;
  union{
    struct{
      struct expr* value;
      char* name;
    }att;
    struct{
      struct expr* value;
      char* name;
    }attct;
    struct{
      struct expr* value;
      char* name;
    }attctbool;
    struct{          //
      char* name;    //
    }attrb;          //
    char* name;
  }attr;
}Attrib;

typedef struct expr {
  enum {
    E_INTEGER,
    E_BOOL, //
    E_VAR,
    E_OPER
  } kind;
  union {
    int value;  //para inteiros
    char* var;
    struct{
      bool value; //
    }attbool;
    struct {
      int operate;
      struct expr* left;
      struct expr* right;
    } op;
  }attr;
}Expr;

typedef struct boolexpr{
  enum{
    B_BOOLOP
  }kind;
  union{
    struct{
        int operate;
        struct expr* left;
        struct expr* right;
    }op;
  }attr;
}BoolExpr;

typedef struct boolExprList {
  enum{
    B_BOOLEXPR,
    B_EXPR,
  }kind;
  struct{
    union{
      struct boolexpr* value;
      struct expr* expr;
    }type;
    struct boolExprList* next;
  }list;
}BoolExprList;

typedef struct while_str {
  enum{
    W_EXPR,
    W_BOOLEXPR,
    W_BOOLEXPR_RETURN,
    W_EXPR_RETURN
  } kind;
  union {
    struct expr* expr;
    struct boolExprList* boolexprValue;
  }type;
  union{
      struct returnExpr* retvalue;
  }wReturn;
  struct cmdList* teste;
}While;

typedef struct if_str {
  enum {
    IF_EXPR,
    IF_EXPR_RETURN,
    IF_BOOLEXPR,
    IF_BOOLEXPR_RETURN,
    IFELSE_EXPR,
    IFELSE_BOOLEXPR
  }kind;
  union {
    struct expr* exprValue;
    struct boolExprList* boolexprValue;
  }type;
  union{
    struct returnExpr* retvalue;
  }wReturn;
  union {
    struct else_str* elseValue;
  }ifElse;
  struct cmdList* teste;
}If;

typedef struct else_str{
  struct cmdList* teste;
}Else;

typedef struct charList {
  char* value;
  struct charList* next;
}CharList;

typedef struct printStr {
  char* value;
  char* name;
  struct charList* varList;;
}PrintStr;

typedef struct scanInt {
  char* value;
  struct charList* varList;
}ScanInt;

typedef struct cmd{
  enum{
    C_ATTRIB,
    C_WHILE,
    C_PRINTSTR,
    C_SCANINT,
    C_IF
  }kind;
  union{
    struct attrib* Attrib;
    struct while_str* While;
    struct printStr* PrintStr;
    struct scanInt* ScanInt;
    struct if_str* If;
  }type;
}Cmd;

typedef struct cmdList{
  struct cmd* Cmd;
  struct cmdList* next;
}CmdList;

typedef struct returnExpr{
    struct expr* exprR;
}ReturnExpr;

Expr* ast_int(int a);
Expr* ast_bool(bool b);
Expr* ast_expr_var(char* n);
Expr* ast_oper(int oper, Expr* left, Expr* right);
CmdList* cmdList(Cmd* cmd, CmdList* next);
Cmd* cmdwhile(While* whileExp);
Cmd* cmdif(If* ifExp);
Cmd* cmdprintstr(PrintStr* printExp);
Cmd* cmdscanint(ScanInt* scanExp);
Cmd* cmdattrib(Attrib* attrib);
Else* cmdelse(CmdList* cmdlist);
CharList* cmdcharlist(char* name, CharList* next);
PrintStr* cmdprint_str_expr(char* v, CharList* charList);
ScanInt* cmdscan_expr(char* v, CharList* charlist);
While* cmdwhile_expr(Expr* expW, CmdList* cmdlist);
While* cmdwhile_boolexprlist(BoolExprList* value , CmdList* cmdlist);
If* cmdif_expr(Expr* expI, CmdList* cmdlist);
If* cmdif_boolexprlist(BoolExprList* value, CmdList* cmdlist);
If* cmdif_expr_else(Expr* expI , CmdList* cmdlist, Else* expelse);
If* cmdif_boolexpr_else (BoolExprList* value , CmdList* cmdlist , Else* boolelse);
Attrib* attribexpr_ct(char* var, Expr* expr);
Attrib* attribexpr(char* var, Expr* expr);
Attrib* nattrib(char* var);
BoolExpr*  boolexpr(Expr* left, Expr* right , int oper);
BoolExprList* bool_booleanexprlist(BoolExpr* value , BoolExprList* next);
BoolExprList* expr_booleanexprlist(Expr* value , BoolExprList* next);
Attrib* nattribbool(char* var);
Attrib* attribexprbool(char* var, Expr* expr);


PrintStr* cmdprint_strname_expr(char* name);
ReturnExpr* return_exp(Expr* expr);
While* cmdwhile_boolexprlist_return(BoolExprList* value , CmdList* cmdlist, ReturnExpr* retvalue);
While* cmdwhile_expr_return(Expr* expW, CmdList* cmdlist , ReturnExpr* retvalue);
If* cmdif_expr_return(Expr* exprI, CmdList* cmdlist, ReturnExpr* retvalue);
If* cmdif_boolexprlist_return(BoolExprList* exprI, CmdList* cmdlist, ReturnExpr* retvalue);

#endif
