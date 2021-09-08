#include <iostream>
#include "asura.h"
using namespace std;

void printProgram(Program *p) {

  cerr << "Program : " << p->lpszName << endl;
  cerr << "Module : " << endl;
  printModule(p->slPgmModule);
  cerr << "Global : " << endl;
  printVariable(p->slDtGlobal);
  cerr << "Function : " << endl;
  printFunction(p->slFunction);
  cerr << "Body : " << endl;
  printStatement(p->stmtBody);
}

void printModule(Scope* s) {
}

void printVariable(Scope* s) {
  if (s == NULL) return;
  ScopeElement *i = s->seHead; //i = data type

  while (i != 0) {
    switch(*(int*)(i->element)) {
      case 0:
	cerr << "VOID " << i->lpszId << endl;
	break;
      case 1:
	cerr << "INT " << i->lpszId << endl;
	break;
      case 2:
	cerr << "REAL " << i->lpszId << endl;
	break;
      case 3:
	cerr << "BOOL " << i->lpszId << endl;
	break;
      case 4:
	cerr << "ARRAY " << i->lpszId << endl;
	break;
    }
    if (i == s->seTail) break;
    else i = i->next;
  }
}

void printFunction(Scope* s) {
  if (s == NULL) return;
  ScopeElement *i = s->seHead; //i = function
  while( i != 0 ) {
    Function* t = (Function*)(i->element); //could this work?
    //int t2 = (int)(t->dtReturn->type);

    switch(t->dtReturn->type) {
      case 0:
	cerr << "VOID " << i->lpszId << endl;
	break;
      case 1:
	cerr << "INT " << i->lpszId << endl;
	break;
      case 2:
	cerr << "REAL " << i->lpszId << endl;
	break;
      case 3:
	cerr << "BOOL " << i->lpszId << endl;
	break;
      case 4:
	cerr << "ARRAY " << i->lpszId << endl;
	break;
    }
    printVariable(t->slDtParam);
    printVariable(t->slDtLocal);
    printStatement(t->stmtBody);

    if (i == s->seTail) break;
    else i = i->next;
  }
}

void printStatement(Statement *s) {
  if (s == NULL) return;
  //int t = (int)(s->scCode);

  switch (s->scCode) {
    case 0:
      cerr << "IF " << endl;
      printExpression(((IfStmt*)s)->exprCond);
      printStatement(((IfStmt*)s)->stmtThen);
      printStatement(((IfStmt*)s)->stmtElse);
      break;
    case 1:
      cerr << "WHILE " << endl;
      printExpression(((WhileStmt*)s)->exprCond);
      printStatement(((WhileStmt*)s)->stmtBody);
      break;
    case 2:
      cerr << "PROC "<< (((ProcStmt*)s)->lpszScope) <<
	" " << (((ProcStmt*)s)->lpszId) << endl;
      for (VoidElement* i = ((ProcStmt*)s)->vlExprParam->veHead;
	  i; i = i->next) {
	printExpression((Expression*)(i->element));
      }
      break;
    case 3:
      cerr << "ASSIGN "; 
      printExpression(((AssignStmt*)s)->exprValue);
      cerr << "TO ";
      if (((AssignStmt*)s)->lpszScope != 0) 
	cerr << ((AssignStmt*)s)->lpszScope << "." << endl;
      cerr << ((AssignStmt*)s)->lpszId << endl;
      for (VoidElement* i = ((AssignStmt*)s)->vlExprIndexes->veHead;
	  i; i = i->next) {
	printExpression((Expression*)(i->element));
      }
      break;
    case 4:
      //cerr << "BEGIN " << endl;
      for (VoidElement* i = ((BeginStmt*)s)->vlStmt->veHead;
	  i; i = i->next) {
	printStatement((Statement*)(i->element));
      }
      break;
    case 5:
      cerr << "RETURN " ;
      printExpression(((ReturnStmt*)s)->exprReturn);
      break;
    case 6:
      cerr << "WAIT " ;
      printExpression(((WaitStmt*)s)->exprCond);
      break;
  }
}

void printExpression(Expression *e) {
  if (e == NULL) return;
  int t = (int)(e->ecCode);
  switch(t) {
    //Constant
    case 0:
      cerr << ((BoolValue*)(((ConstantExpr*)e)->vConst))->b << endl;
      break;
    case 1:
      cerr << ((IntValue*)(((ConstantExpr*)e)->vConst))->i << endl;
      break;
    case 2:
      //cerr << ((RealValue*)(((ConstantExpr*)e)->vConst))->r << endl;
      //cerr << ((ConstantExpr*)e)->vConst->r << endl;
      cerr << (double)(((RealValue*)(((ConstantExpr*)e)->vConst))->r) << endl;
      break;
      
    //NOT operation
    case 3:
      cerr << "NOT " << endl;
      printExpression(((NotExpr*)e)->exprBool);
      break;
    //Boolean
    case 4:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "AND " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 5:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "OR " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;

    //Numeric
    case 6:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "+ " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 7:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "- " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 8:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "* " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 9:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "/ " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 10:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "% " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;

    //Compare
    case 11:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "= " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 12:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "<> " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 13:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "> " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 14:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << ">= " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 15:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "< " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;
    case 16:
      printExpression(((BopExpr*)e)->exprLeft);
      cerr << "<= " << endl;
      printExpression(((BopExpr*)e)->exprRight);
      break;

    //Variable
    case 17:
      if (((VarExpr*)e)->lpszScope != 0)
	cerr << ((VarExpr*)e)->lpszScope << ".";
      cerr << ((VarExpr*)e)->lpszId << endl;
      for (VoidElement* i = ((VarExpr*)e)->vlExprIndexes->veHead;
	  i; i = i->next) {
	printExpression((Expression*)(i->element));
      }
      break;

    //Function Operation
    case 18:
      if (((FuncExpr*)e)->lpszScope != 0)
	cerr << ((FuncExpr*)e)->lpszScope << "."  ;
      cerr << ((FuncExpr*)e)->lpszId << endl;
      for (VoidElement* i = ((FuncExpr*)e)->vlExprParam->veHead;
	  i; i = i->next) {
	printExpression((Expression*)(i->element));
      }
      break;

  }
}
