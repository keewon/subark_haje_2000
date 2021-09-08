////////////////////////////////////////////////////////////////////////////////
//
// "Stmt.cpp"
//		Statement Ŭ���� ����
//												�ۼ��� : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include <malloc.h>
#include "Parser.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Statement::~Statement()
//		Statement Ŭ���� �Ҹ���. scCode�� �̿��Ͽ� �ڵ����� �ڽ��� ���
//		Ŭ�������� Ȯ���Ͽ� �ʿ��� �۾��� �Ѵ�.
//												�ۼ��� : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

Statement::~Statement() {
	VoidElement *lpve;

	switch (scCode) {
	case SC_IF:									// IfStmt �Ҹ���
#define temp ((IfStmt*)this)
		if (temp->exprCond) delete temp->exprCond;
		if (temp->stmtThen) delete temp->stmtThen;
		if (temp->stmtElse) delete temp->stmtElse;
		break;
#undef temp
	case SC_WHILE:								// WhileStmt �Ҹ���
#define temp ((WhileStmt*)this)
		if (temp->exprCond) delete temp->exprCond;
		if (temp->stmtBody) delete temp->stmtBody;
		break;
#undef temp
	case SC_PROC:								// ProcStmt �Ҹ���
#define temp ((ProcStmt*)this)
		if (temp->lpszScope) free(temp->lpszScope);
		if (temp->lpszId) free(temp->lpszId);
		if (temp->lpvlExprParam) {
			for (lpve = temp->lpvlExprParam->lpveHead; lpve; lpve = lpve->lpveNext)
				delete ((Expression*)lpve);
			delete temp->lpvlExprParam;
		}
		break;
#undef temp
	case SC_ASSIGN:								// AssignStmt �Ҹ���
#define temp ((AssignStmt*)this)
		if (temp->exprValue) delete temp->exprValue;
		if (temp->lpszId) free(temp->lpszId);
		if (temp->lpvlExprIndexes) {
			for (lpve = temp->lpvlExprIndexes->lpveHead; lpve; lpve = lpve->lpveNext)
				delete ((Expression*)lpve);
			delete temp->lpvlExprIndexes;
		}
		break;
#undef temp
	case SC_BEGIN:								// BeginStmt �Ҹ���
#define temp ((BeginStmt*)this)
		if (temp->lpvlStmt) {
			for (lpve = temp->lpvlStmt->lpveHead; lpve; lpve = lpve->lpveNext)
				delete ((Statement*)lpve);
			delete temp->lpvlStmt;
		}
#undef temp
		break;
	case SC_RETURN:								// ReturnStmt �Ҹ���
#define temp ((ReturnStmt*)this)
		if (temp->exprReturn) delete temp->exprReturn;
#undef temp
		break;
	case SC_WAIT:								// WaitStmt �Ҹ���
#define temp ((WaitStmt*)this)
		if (temp->exprCond) delete temp->exprCond;
#undef temp
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// IfStmt::IfStmt()
//		IfStmt ������
//												�ۼ��� : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

IfStmt::IfStmt() {
	scCode = SC_IF;
	exprCond = NULL;
	stmtThen = stmtElse = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// WhileStmt::WhileStmt()
//		WhileStmt ������
//												�ۼ��� : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

WhileStmt::WhileStmt() {
	scCode = SC_WHILE;
	exprCond = NULL;
	stmtBody = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// ProcStmt::ProcStmt()
//		ProcStmt ������
//												�ۼ��� : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

ProcStmt::ProcStmt() {
	scCode = SC_PROC;
	lpszScope = lpszId = NULL;
	lpvlExprParam = new VoidList();
}

////////////////////////////////////////////////////////////////////////////////
//
// AssignStmt::AssignStmt()
//		AssignStmt ������
//												�ۼ��� : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

AssignStmt::AssignStmt() {
	scCode = SC_ASSIGN;
	lpszId = NULL;
	lpvlExprIndexes = new VoidList();
}

////////////////////////////////////////////////////////////////////////////////
//
// BeginStmt::BeginStmt()
//		BeginStmt ������
//												�ۼ��� : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

BeginStmt::BeginStmt() {
	scCode = SC_BEGIN;
	lpvlStmt = new VoidList();
}

////////////////////////////////////////////////////////////////////////////////
//
// ReturnStmt::ReturnStmt
//		ReturnStmt ������
//												�ۼ��� : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

ReturnStmt::ReturnStmt() {
	scCode = SC_RETURN;
	exprReturn = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// WaitStmt::WaitStmt()
//		WaitStmt ������
//												�ۼ��� : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

WaitStmt::WaitStmt() {
	scCode = SC_WAIT;
	exprCond = NULL;
}
