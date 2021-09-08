#include <malloc.h>
#include "parser.h"

/*
 * Expression class
 */

Expression::~Expression()
{
	VoidElement *ve;

	switch (ecCode) {
	case BOOL:
	case INT:
	case REAL:
#define temp ((ConstantExpr*)this)
		if (temp->vConst) delete temp->vConst;
		break;
#undef temp
	case NOT:
#define temp ((NotExpr*)this)
		if (temp->exprBool) delete temp->exprBool;
		break;
#undef temp
	case AND:
	case OR:
	case ADD:
	case SUB:
	case MUL:
	case DIV:
	case MOD:
	case EQ:
	case NE:
	case GT:
	case GE:
	case LT:
	case LE:
#define temp ((BopExpr*)this)
		if (temp->exprLeft) delete temp->exprLeft;
		if (temp->exprRight) delete temp->exprRight;
		break;
#undef temp
	case VAR:
#define temp ((VarExpr*)this)
		if (temp->lpszScope) free(temp->lpszScope);
		if (temp->lpszId) free(temp->lpszId);
		if (temp->vlExprIndexes) {
			for (ve = temp->vlExprIndexes->veHead; ve; ve = ve->next)
				delete ((Expression*)ve->element);
			delete temp->vlExprIndexes;
		}
		break;
#undef temp
	case FUNC:
#define temp ((FuncExpr*)this)
		if (temp->lpszScope) free(temp->lpszScope);
		if (temp->lpszId) free(temp->lpszId);
		if (temp->vlExprParam) {
			for (ve = temp->vlExprParam->veHead; ve; ve = ve->next)
				delete ((Expression*)ve->element);
			delete temp->vlExprParam;
		}
#undef temp
	}
}

ConstantExpr::ConstantExpr(int i)
{
	ecCode = INT;
	vConst = new IntValue();
	((IntValue*)vConst)->i = i;
}

ConstantExpr::ConstantExpr(double r)
{
	ecCode = REAL;
	vConst = new RealValue();
	((RealValue*)vConst)->r = r;
}

ConstantExpr::ConstantExpr(bool b)
{
	ecCode = BOOL;
	vConst = new BoolValue();
	((BoolValue*)vConst)->b = b;
}

NotExpr::NotExpr()
{
	ecCode = NOT;
	exprBool = NULL;
}

BopExpr::BopExpr(ExprCode ecOp)
{
	ecCode = ecOp;
	exprLeft = exprRight = NULL;
}

VarExpr::VarExpr()
{
	ecCode = VAR;
	lpszScope = lpszId = NULL;
	vlExprIndexes = new VoidList();
}

FuncExpr::FuncExpr()
{
	ecCode = FUNC;
	lpszScope = lpszId = NULL;
	vlExprParam = new VoidList();
}
