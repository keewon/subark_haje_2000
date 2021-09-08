#include <malloc.h>
#include "parser.h"

/*
 * Statement classes
 */

Statement::~Statement() {
	VoidElement *ve;

	switch (scCode) {
	case IF:
#define temp ((IfStmt*)this)
		if (temp->exprCond) delete temp->exprCond;
		if (temp->stmtThen) delete temp->stmtThen;
		if (temp->stmtElse) delete temp->stmtElse;
		break;
#undef temp
	case WHILE:
#define temp ((WhileStmt*)this)
		if (temp->exprCond) delete temp->exprCond;
		if (temp->stmtBody) delete temp->stmtBody;
		break;
#undef temp
	case PROC:
#define temp ((ProcStmt*)this)
		if (temp->lpszScope) free(temp->lpszScope);
		if (temp->lpszId) free(temp->lpszId);
		if (temp->vlExprParam) {
			for (ve = temp->vlExprParam->veHead; ve; ve = ve->next)
				delete ((Expression*)ve);
			delete temp->vlExprParam;
		}
		break;
#undef temp
	case ASSIGN:
#define temp ((AssignStmt*)this)
		if (temp->exprValue) delete temp->exprValue;
		if (temp->lpszScope) free(temp->lpszScope);
		if (temp->lpszId) free(temp->lpszId);
		if (temp->vlExprIndexes) {
			for (ve = temp->vlExprIndexes->veHead; ve; ve = ve->next)
				delete ((Expression*)ve);
			delete temp->vlExprIndexes;
		}
		break;
#undef temp
	case BEGIN:
#define temp ((BeginStmt*)this)
		if (temp->vlStmt) {
			for (ve = temp->vlStmt->veHead; ve; ve = ve->next)
				delete ((Statement*)ve);
			delete temp->vlStmt;
		}
#undef temp
		break;
	case RETURN:
#define temp ((ReturnStmt*)this)
		if (temp->exprReturn) delete temp->exprReturn;
#undef temp
		break;
	case WAIT:
#define temp ((WaitStmt*)this)
		if (temp->exprCond) delete temp->exprCond;
#undef temp
	}
}

IfStmt::IfStmt() {
	scCode = IF;
	exprCond = NULL;
	stmtThen = stmtElse = NULL;
}

WhileStmt::WhileStmt() {
	scCode = WHILE;
	exprCond = NULL;
	stmtBody = NULL;
}

ProcStmt::ProcStmt() {
	scCode = PROC;
	lpszScope = lpszId = NULL;
	vlExprParam = new VoidList();
}

AssignStmt::AssignStmt() {
	scCode = ASSIGN;
	lpszScope = lpszId = NULL;
	vlExprIndexes = new VoidList();
}

BeginStmt::BeginStmt() {
	scCode = BEGIN;
	vlStmt = new VoidList();
}

ReturnStmt::ReturnStmt() {
	scCode = RETURN;
	exprReturn = NULL;
}

WaitStmt::WaitStmt() {
	scCode = WAIT;
	exprCond = NULL;
}
