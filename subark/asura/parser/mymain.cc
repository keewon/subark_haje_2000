#include "parser.h"
#include "asura.h"

int main(int argc, char *argv[])
{
	Program pgm;

	  char* name = "GOAHEAD";
	pgm.lpszName = name;
	pgm.slDtGlobal = 0;
	pgm.slFunction = 0;
	pgm.stmtBody = 0;

	/*
	  Scope scGlobal;
	    ScopeElement seG1;

		char* name2 = "Var";
	      seG1.lpszId = name2;

		IntValue iv1;
		  iv1.i = 123;
		    DataType dataType1;
		    dataType1.type = 1;
		  iv1.dt = &dataType1;
	      seG1.element = &iv1;

	  scGlobal.Add(&seG1);
	pgm.slDtGlobal  = &scGlobal;
	pgm.slFunction = 0;

	  BeginStmt beginStmtPgm;
	  
	      AssignStmt ass1;

	        ConstantExpr constExpr1(0.9);
	      ass1.exprValue = &constExpr1;

	        char* name4 = "Function1";
	      ass1.lpszId = name4;
	        char* name5 = "ScopeAssign";
	      ass1.lpszScope = name5;

	        VoidList vl2;
		  VoidElement ve3;
		    IntValue iv2;
		      iv2.i = 456;
			DataType dataType2;
			dataType2.type = 1;
		      iv2.dt = &dataType2;
		  ve3.element = &iv2;
		  ve3.next = 0;
		vl2.veHead = vl2.veTail = &ve3;
	      ass1.vlExprIndexes = &vl2;

	    VoidList vl1;
	      VoidElement ve4;
	      ve4.element = &ass1;
	      ve4.next =  0;
	      vl1.veHead = vl1.veTail = &ve4;
	  beginStmtPgm.vlStmt = &vl1;

	pgm.stmtBody = &beginStmtPgm;
	*/

	printProgram(&pgm);
}
