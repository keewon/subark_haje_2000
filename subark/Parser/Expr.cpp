////////////////////////////////////////////////////////////////////////////////
//
// "Expr.cpp"
//		Expression 클래스 정의
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include <malloc.h>
#include "Expr.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Expression::~Expression()
//		Expression 클래스 소멸자. ecCode를 통하여 스스로 어느 클래스인지 확인
//		필요한 일을 한다.
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

Expression::~Expression()
{
	VoidElement *lpve;

	switch (ecCode) {
	case EC_BOOL:
	case EC_INT:
	case EC_REAL:					// 상수
#define temp ((ConstantExpr*)this)
		if (temp->lpvConst) delete temp->lpvConst;
		break;
#undef temp
	case EC_NOT:					// not <Expr>
#define temp ((NotExpr*)this)
		if (temp->exprBool) delete temp->exprBool;
		break;
#undef temp
	case EC_AND:
	case EC_OR:
	case EC_ADD:
	case EC_SUB:
	case EC_MUL:
	case EC_DIV:
	case EC_MOD:
	case EC_EQ:
	case EC_NE:
	case EC_GT:
	case EC_GE:
	case EC_LT:
	case EC_LE:						// Binary Operations
#define temp ((BopExpr*)this)
		if (temp->exprLeft) delete temp->exprLeft;
		if (temp->exprRight) delete temp->exprRight;
		break;
#undef temp
	case EC_VAR:					// 변수, Attribute 읽기
#define temp ((VarExpr*)this)
		if (temp->lpszScope) free(temp->lpszScope);
		if (temp->lpszId) free(temp->lpszId);
		if (temp->lpvlExprIndexes) {
			for (lpve = temp->lpvlExprIndexes->lpveHead; lpve; lpve = lpve->lpveNext)
				delete ((Expression*)lpve->lpElement);
			delete temp->lpvlExprIndexes;
		}
		break;
#undef temp
	case EC_FUNC:					// Function or operations
#define temp ((FuncExpr*)this)
		if (temp->lpszScope) free(temp->lpszScope);
		if (temp->lpszId) free(temp->lpszId);
		if (temp->lpvlExprParam) {
			for (lpve = temp->lpvlExprParam->lpveHead; lpve; lpve = lpve->lpveNext)
				delete ((Expression*)lpve->lpElement);
			delete temp->lpvlExprParam;
		}
#undef temp
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// ConstantExpr::ConstantExpr(int n)
//		정수형 상수 Expression 생성자
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

ConstantExpr::ConstantExpr(int n)
{
	ecCode = EC_INT;
	lpvConst = new IntValue();
	((IntValue*)lpvConst)->n = n;
}

////////////////////////////////////////////////////////////////////////////////
//
// ConstantExpr::ConstantExpr(double r)
//		실수형 상수 Expression 생성자
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

ConstantExpr::ConstantExpr(double r)
{
	ecCode = EC_REAL;
	lpvConst = new RealValue();
	((RealValue*)lpvConst)->r = r;
}

////////////////////////////////////////////////////////////////////////////////
//
// ConstantExpr::ConstantExpr(bool b)
//		Boolean형 상수 Expression 생성자
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

ConstantExpr::ConstantExpr(bool b)
{
	ecCode = EC_BOOL;
	lpvConst = new BoolValue();
	((BoolValue*)lpvConst)->b = b;
}

////////////////////////////////////////////////////////////////////////////////
//
// NotExpr::NotExpr()
//		not <expr> 생성자
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

NotExpr::NotExpr()
{
	ecCode = EC_NOT;
	exprBool = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// BopExpr::BopExpr(ExprCode ecOp)
//		Binary Operation 생성자
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

BopExpr::BopExpr(ExprCode ecOp)
{
	ecCode = ecOp;
	exprLeft = exprRight = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// VarExpr::VarExpr()
//		변수, Attribute 읽기
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

VarExpr::VarExpr()
{
	ecCode = EC_VAR;
	lpszScope = lpszId = NULL;
	lpvlExprIndexes = new VoidList();
}

////////////////////////////////////////////////////////////////////////////////
//
// FuncExpr::FuncExpr()
//		Function or operation 부르기
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

FuncExpr::FuncExpr()
{
	ecCode = EC_FUNC;
	lpszScope = lpszId = NULL;
	lpvlExprParam = new VoidList();
}