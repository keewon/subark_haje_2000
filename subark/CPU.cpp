////////////////////////////////////////////////////////////////////////////////
//
// "CPU.cpp"
//		CPU 클래스 정의
//												작성자 : asura
//												Last Update : 2000. 11. 2.
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include <malloc.h>
#include <string.h>
#include "CPU.h"

/// Macros & Constants /////////////////////////////////////////////////////////

#define lpvLastReturn (((Value**)lpTemporaryMem)[0])
#define PauseCPU \
	lpmemPgm->PushCounter(rscCode, nSubState, lpPC, lpTemporaryMem); \
	return false
#define PopPCFromStmt \
	lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem); \
	if (rscCode == RSC_STOP) return false; \
	lpvLastReturn = new Value(); \
	lpvLastReturn->lpdt = new DataType(); \
	lpvLastReturn->lpdt->tcType = TC_VOID; \
	return true \

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// CPU::CPU(Explorer *lpexExp, int nPower, Memory *lpmemStart)
//		CPU의 생성자. nPower는 CPU가 한 턴에 계산하는 양을 결정한다.
//		IN:
//			lpexExp - CPU가 속한 탐사선
//			nPower - 한 턴에 사용할 CPU Power
//			lpmemStart - 처음 시작할 프로그램
//												작성자 : asura
//												Last Update : 2000. 8. 22.
//
////////////////////////////////////////////////////////////////////////////////

CPU::CPU(Explorer *lpexExp, int nPower, Memory *lpmemStart)
{
	lpexExplorer = lpexExp;
	nCPUPower = nPower;
	nLeftPower = 0;
	lpmemPgm = lpmemStart;
	lpmemNewPgm = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Value *CPU::Operation(char *lpszOp, VoidList *lpvlArgument)
//		CPU의 Operations:
//			procedure run(memory mem)
//		IN:
//			lpszOp - Operation 이름
//			lpvlArgument - 파라미터 리스트
//		RETURN:
//			lpszOp가 "run"이면 VOID값. 아니면 NULL
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

Value *
CPU::Operation(char *lpszOp, VoidList *lpvlArgument)
{
	if (!strcmp(lpszOp, "run")) {
		Value *lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		lpmemNewPgm = (Memory*)
			((ObjectValue*)lpvlArgument->lpveHead->lpElement)->partObject;
		return lpvReturn;
	} else return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Value *CPU::Attribute(char *lpszAttr)
//		CPU의 Attribute:
//			memory mem
//			int clock
//		IN:
//			lpszAttr - Attribute 이름
//		RETURN:
//			"mem"면 현재 실행중인 메모리. "clock"이면 CPU 스피드를. 아니면 NULL
//			
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

Value *
CPU::Attribute(char *lpszAttr)
{
	if (!strcmp(lpszAttr, "mem")) {
		return new ObjectValue("memory", lpmemPgm);
	} else if (!strcmp(lpszAttr, "clock")) {
		IntValue *lpivReturn = new IntValue();
		lpivReturn->n = nCPUPower;
		return lpivReturn;
	} else return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// void CPU::Draw(void)
//		아무일도 안한다.			
//												작성자 : asura
//												Last Update : 2000. 8. 22.
//
////////////////////////////////////////////////////////////////////////////////

void
CPU::Draw(void)
{
}

////////////////////////////////////////////////////////////////////////////////
//
// void CPU::Turn(void)
//		메모리의 현재 상태를 읽어와서 값을 계산하고 상태를 저장한다
//												작성자 : asura
//												Last Update : 2000. 10. 11.
//
////////////////////////////////////////////////////////////////////////////////

void 
CPU::Turn(void)
{
	if (lpmemNewPgm) {
		lpmemPgm = lpmemNewPgm;
		lpmemNewPgm = NULL;
	}

	nLeftPower += nCPUPower;
	lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
	if (rscCode == RSC_STOP) {
		nLeftPower = 0;
		if (lpPC) lpmemPgm->PushCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
		return;
	}

	do {
		switch (rscCode) {
		case RSC_STMT:		// Statement 분리
			switch (((Statement*)lpPC)->scCode) {
			case SC_IF:	rscCode = RSC_IF; break;
			case SC_WHILE: rscCode = RSC_WHILE; break;
			case SC_PROC: rscCode = RSC_PROC; break;
			case SC_ASSIGN: rscCode = RSC_ASSIGN; break;
			case SC_BEGIN: rscCode = RSC_BEGIN; break;
			case SC_RETURN: rscCode = RSC_RETURN; break;
			case SC_WAIT: rscCode = RSC_WAIT; break;
			}
			break;
		case RSC_EXPR:		// Expression 분리
			switch (((Expression*)lpPC)->ecCode) {
			case EC_BOOL: 
			case EC_INT: 
			case EC_REAL: rscCode = RSC_CONST; break;
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
			case EC_LE: rscCode = RSC_BOP; break;
			case EC_NOT: rscCode = RSC_NOT; break;
			case EC_VAR: rscCode = RSC_VAR; break;
			case EC_FUNC: rscCode = RSC_FUNC; break;
			}
			break;
		case RSC_IF:		// if then else
			if (!TurnIfStmt()) 
				return;
			break;
		case RSC_WHILE:		// while do
			if (!TurnWhileStmt())
				return;
			break;
		case RSC_PROC:		// call with
			if (!TurnProcStmt())
				return;
			break;
		case RSC_ASSIGN:	// assign to
			if (!TurnAssignStmt())
				return;
			break;
		case RSC_BEGIN:		// begin end
			if (!TurnBeginStmt())
				return;
			break;
		case RSC_RETURN:	// return
			if (!TurnReturnStmt())
				return;
			break;
		case RSC_WAIT:		// wait
			if (!TurnWaitStmt())
				return;
			break;
		case RSC_CONST:		// constant
			if (!TurnConstExpr())
				return;
			break;
		case RSC_BOP:		// binary operations
			if (!TurnBopExpr())
				return;
			break;
		case RSC_NOT:		// not operation
			if (!TurnNotExpr())
				return;
			break;
		case RSC_VAR:		// variable
			if (!TurnVarExpr())
				return;
			break;
		case RSC_FUNC:		// call with
			if (!TurnFuncExpr())
				return;
			break;
		}
	} while(true);
}

bool 
CPU::TurnIfStmt(void)
{
	if (nSubState==0) {
		// condition 계산
		lpmemPgm->PushCounter(RSC_IF, 1, lpPC, malloc(sizeof(Value*)));
		rscCode = RSC_EXPR;
		lpPC = ((IfStmt*)lpPC)->exprCond;
	} else if (nSubState==1) {
		// if문 실행
		if (nLeftPower<nIfCPUPower) { PauseCPU; }
		nLeftPower-=nIfCPUPower;

		if (((BoolValue*)lpvLastReturn)->b) {
			// condition이 참일 때
			lpmemPgm->PushCounter(RSC_IF, 2, lpPC, lpTemporaryMem);
			delete lpvLastReturn;
			rscCode = RSC_STMT;
			lpPC = ((IfStmt*)lpPC)->stmtThen;
			nSubState = 0;
			lpTemporaryMem = NULL;
		} else if (((IfStmt*)lpPC)->stmtElse) {
			// condition이 거짓이고 else 문이 사용되었을 때
			lpmemPgm->PushCounter(RSC_IF, 2, lpPC, lpTemporaryMem);
			delete lpvLastReturn;
			rscCode = RSC_STMT;
			lpPC = ((IfStmt*)lpPC)->stmtElse;
			nSubState = 0;
			lpTemporaryMem = NULL;
		} else {
			// condition이 거짓이고 else 문이 없을 때
			delete lpvLastReturn;
			nSubState = 2;
		}
	} else {
		// if then else 종료
		delete lpvLastReturn;
		free(lpTemporaryMem);
		PopPCFromStmt;
	}

	return true;
}

bool
CPU::TurnWhileStmt(void)
{
	if (nSubState==0) {
		nSubState = 1;
		lpTemporaryMem = malloc(sizeof(Value*));
	} else if (nSubState==1) {
		// condition 계산
		lpmemPgm->PushCounter(RSC_WHILE, 2, lpPC, lpTemporaryMem);
		rscCode = RSC_EXPR;
		lpPC = ((WhileStmt*)lpPC)->exprCond;
		nSubState = 0;
	} else if (nSubState==2) {
		if (nLeftPower<nWhileCPUPower) { PauseCPU; }
		nLeftPower -= nWhileCPUPower;
				
		if (((BoolValue*)lpvLastReturn)->b) {
			// condition이 참일 때
			lpmemPgm->PushCounter(RSC_WHILE, 1, lpPC, lpTemporaryMem);
			delete lpvLastReturn;
			rscCode = RSC_STMT;
			lpPC = ((WhileStmt*)lpPC)->stmtBody;
			nSubState = 0;
			lpTemporaryMem = NULL;
		} else {
			// condition이 거짓일 때, while문 끝내기
			delete lpvLastReturn;
			free(lpTemporaryMem);
			PopPCFromStmt;
		}
	}
	return true;
}

bool
CPU::TurnProcStmt(void)
{
	VoidElement *lpve;
	ScopeElement *lpse, *lpseTemp;
	Scope *lpslNewLocal;
	int i;

	if (nSubState==0) {
		lpTemporaryMem = malloc(sizeof(void*)*3);
		((VoidList**)lpTemporaryMem)[1] = new VoidList();
	} else if (nSubState==-2) {
		// call문 끝내기
		delete lpvLastReturn;
		delete ((VoidList**)lpTemporaryMem)[1];
		free(lpTemporaryMem);
		lpmemPgm->PopVarScope(lpslNewLocal);
		for (lpse = lpslNewLocal->lpseHead; lpse; lpse = lpse->lpseNext)
			delete (Value*)lpse->lpElement;
		delete lpslNewLocal;
		PopPCFromStmt;
		return true;
	} else if (nSubState == -1) {
		// 계산할 파라미터가 없을 때
		if (((ProcStmt*)lpPC)->lpszScope) {
			// Operation call
			if (nLeftPower<nOpCPUPower) { PauseCPU; }
			nLeftPower -= nOpCPUPower;

			Part *partObject;
			Value *lpvPart = lpmemPgm->QueryVariable(((ProcStmt*)lpPC)->lpszScope);
			if (lpvPart) {
				if (lpvPart->lpdt->tcType==TC_OBJECT)
					partObject = ((ObjectValue*)lpvPart)->partObject;
				else partObject = NULL;
			} else {
				partObject = lpexExplorer->QueryPart(((ProcStmt*)lpPC)->lpszScope);
			}
				
			if (!partObject) {
				lpmemPgm->PushCounter(RSC_STOP, STOP_BYSTMT+STOP_BYWRONGPART, 
					lpPC, lpTemporaryMem);
				return false;
			}
			lpvLastReturn = partObject->Operation(((ProcStmt*)lpPC)->lpszId,
				((VoidList**)lpTemporaryMem)[1]);
			if (lpvLastReturn) delete lpvLastReturn;
			lpve = ((VoidList**)lpTemporaryMem)[1]->lpveHead;
			while (lpve) {
				delete (Value*)lpve->lpElement;
				lpve = lpve->lpveNext;
			}
			delete ((VoidList**)lpTemporaryMem)[1];
			free(lpTemporaryMem);
			PopPCFromStmt;
		} else {
			// procedure call
			if (nLeftPower<nFuncCPUPower) { PauseCPU; }
			nLeftPower -= nFuncCPUPower;

			Function *func = lpmemPgm->QueryFunction(((ProcStmt*)lpPC)->lpszId);
			lpslNewLocal = new Scope();

			// 파라미터 복사
			nSubState = 0;
			lpve = ((VoidList**)lpTemporaryMem)[1]->lpveHead;
			while (lpve) {
				nSubState++;
				lpve = lpve->lpveNext;
			}
			lpve = ((VoidList**)lpTemporaryMem)[1]->lpveHead;
			while (nSubState>0) {
				i = --nSubState;
				lpse = func->lpslDtParam->lpseHead;
				while (i>0 && lpse) {
					lpse = lpse->lpseNext; i--;
				}
				lpseTemp = new ScopeElement();
				lpseTemp->lpszId = (char*)malloc(sizeof(char)*
					(strlen(lpse->lpszId)+1));
				memcpy(lpseTemp->lpszId, lpse->lpszId,
					sizeof(char)*(strlen(lpse->lpszId)+1));
				lpseTemp->lpElement = lpve->lpElement;
				lpslNewLocal->Add(lpseTemp);
				lpve = lpve->lpveNext;
			}

			// 지역 변수 생성
			lpse = func->lpslDtLocal->lpseHead;
			while (lpse) {
				lpseTemp = new ScopeElement();
				lpseTemp->lpszId = (char*)malloc(sizeof(char)*
					(strlen(lpse->lpszId)+1));
				memcpy(lpseTemp->lpszId, lpse->lpszId, 
					sizeof(char)*(strlen(lpse->lpszId)+1));
				switch (((DataType*)lpse->lpElement)->tcType) {
				case TC_INT:
					lpseTemp->lpElement = new IntValue();
					break;
				case TC_REAL:
					lpseTemp->lpElement = new RealValue();
					break;
				case TC_BOOL:
					lpseTemp->lpElement = new BoolValue();
					break;
				case TC_ARRAY:
					lpseTemp->lpElement = 
						new ArrayValue(
							((ArrayType*)lpse->lpElement)->CopyType());
					break;
				case TC_OBJECT:
					lpseTemp->lpElement = new ObjectValue(
						((ObjectType*)lpse->lpElement)->lpszObject, NULL);
					break;
				}
				lpslNewLocal->Add(lpseTemp);
				lpse = lpse->lpseNext;
			}

			// 리턴 변수 생성
			if (func->lpdtReturn->tcType != TC_VOID) {
				lpseTemp = new ScopeElement();
				lpseTemp->lpszId = (char *)malloc(sizeof(char));
				lpseTemp->lpszId[0] = '\0';
				switch (func->lpdtReturn->tcType) {
				case TC_INT:
					lpseTemp->lpElement = new IntValue();
					break;
				case TC_REAL:
					lpseTemp->lpElement = new RealValue();
					break;
				case TC_BOOL:
					lpseTemp->lpElement = new BoolValue();
					break;
				case TC_ARRAY:
					lpseTemp->lpElement = 
						new ArrayValue(
						((ArrayType*)lpse->lpElement)->CopyType());
					break;
				case TC_OBJECT:
					lpseTemp->lpElement = new ObjectValue(
						((ObjectType*)lpse->lpElement)->lpszObject, NULL);
					break;
				}
				lpslNewLocal->Add(lpseTemp);
			}

			// Push and call proc
			lpmemPgm->PushVarScope(lpslNewLocal);
			lpmemPgm->PushCounter(RSC_PROC, -2, lpPC, lpTemporaryMem);
			nSubState = 0;
			rscCode = RSC_STMT;
			lpPC = (void*)func->stmtBody;
			lpTemporaryMem = NULL;

			return true;
		}
	} else if (nSubState>0) {
		((VoidList**)lpTemporaryMem)[1]->Add(lpvLastReturn);
	}

	lpve = ((ProcStmt*)lpPC)->lpvlExprParam->lpveHead;
	for (i=nSubState; i>0 && lpve; i--)
		lpve = lpve->lpveNext;

	if (lpve) {
		// 계산할 파라미터가 남았을 때
		lpmemPgm->PushCounter(RSC_PROC, nSubState+1, lpPC, lpTemporaryMem);
		rscCode = RSC_EXPR;
		nSubState = 0;
		lpPC = lpve->lpElement;
		lpTemporaryMem = NULL;
	} else {
		nSubState = -1;
	}

	return true;
}

bool 
CPU::TurnAssignStmt(void)
{
	int nDimension(0), nSize;
	VoidElement *lpve;
	DataType *lpdt;
	Value *lpvTemp;
	byte *lpSave;

	if (nSubState==0) {
		// 임시 저장 공간 초기화
		lpve = ((AssignStmt*)lpPC)->lpvlExprIndexes->lpveHead;
		nDimension = 0;
		while (lpve) {
			nDimension++;
			lpve = lpve->lpveNext;
		}
		lpTemporaryMem = malloc(sizeof(Value*)+sizeof(int)*(nDimension+1));
		((int*)lpTemporaryMem+1)[0] = nDimension;
		if (nDimension) {
			// 첫번째 인덱스 계산
			lpmemPgm->PushCounter(RSC_ASSIGN, 1, lpPC, lpTemporaryMem);
			lpPC = ((AssignStmt*)lpPC)->lpvlExprIndexes->lpveHead->lpElement;
			rscCode = RSC_EXPR;
			lpTemporaryMem = NULL;
		} else {
			// 인덱스가 없는 경우
			lpmemPgm->PushCounter(RSC_ASSIGN, -1, lpPC, lpTemporaryMem);
			rscCode = RSC_EXPR;
			lpTemporaryMem = NULL;
			lpPC = ((AssignStmt*)lpPC)->exprValue;
			nSubState = 0;
		}
	} else if (nSubState!=-1 && ((int*)lpTemporaryMem+1)[0]>nSubState) {
		// 계산할 인덱스가 남았을 때
		((int*)lpTemporaryMem+1)[nSubState] = 
			((IntValue*)lpvLastReturn)->n;
		delete lpvLastReturn;
		nSubState++;
		lpve = ((AssignStmt*)lpPC)->lpvlExprIndexes->lpveHead;
		for (nDimension = 1; nDimension<nSubState; nDimension++)
			lpve = lpve->lpveNext;
		lpmemPgm->PushCounter(RSC_ASSIGN, nSubState+1, lpPC, lpTemporaryMem);
		lpPC = lpve->lpElement;
		nSubState = 0;
		rscCode = RSC_EXPR;
		lpTemporaryMem = NULL;
	} else if (nSubState==-1) {
		// 값을 저장
		if (nLeftPower<nAssignCPUPower) { PauseCPU; }
		nLeftPower -= nAssignCPUPower;

		lpvTemp = lpmemPgm->QueryVariable(((AssignStmt*)lpPC)->lpszId);
		switch (lpvTemp->lpdt->tcType) {
		case TC_INT:
			((IntValue*)lpvTemp)->n = ((IntValue*)lpvLastReturn)->n;
			break;
		case TC_REAL:
			((RealValue*)lpvTemp)->r = ((RealValue*)lpvLastReturn)->r;
			break;
		case TC_BOOL:
			((BoolValue*)lpvTemp)->b = ((BoolValue*)lpvLastReturn)->b;
			break;
		case TC_ARRAY:
			lpSave = ((ArrayValue*)lpvTemp)->value;
			lpdt = lpvTemp->lpdt;
			nSize = ((ArrayType*)lpdt)->GetElementSize() * 
				((ArrayType*)lpdt)->nLength;
			while (nDimension<((int*)lpTemporaryMem+1)[0]) {
				nSize = ((ArrayType*)lpdt)->GetElementSize();
				lpSave += nSize*
					((int*)lpTemporaryMem+1)[nDimension+1];
				nDimension++;
				lpdt = ((ArrayType*)lpdt)->lpdtElementType;
			}
			memcpy(lpSave, ((ArrayValue*)lpvLastReturn)->value, nSize);
			break;
		case TC_OBJECT:
			((ObjectValue*)lpvTemp)->partObject =
				((ObjectValue*)lpvLastReturn)->partObject;
			break;
		}

		delete lpvLastReturn;
		free(lpTemporaryMem);
		PopPCFromStmt;
	} else {
		// 인덱스를 모두 계산했을 때
		((int*)lpTemporaryMem+1)[nSubState] = 
			((IntValue*)lpvLastReturn)->n;
		delete lpvLastReturn;
		lpmemPgm->PushCounter(RSC_ASSIGN, -1, lpPC, lpTemporaryMem);
		rscCode = RSC_EXPR;
		lpTemporaryMem = NULL;
		lpPC = ((AssignStmt*)lpPC)->exprValue;
		nSubState = 0;
	}

	return true;
}

bool 
CPU::TurnBeginStmt(void)
{
	VoidElement *lpve;
	int i;

	if (nSubState==0)
		// 임시 저장 장소 초기화
		lpTemporaryMem = malloc(sizeof(Value*));
	else
		delete lpvLastReturn;

	lpve = ((BeginStmt*)lpPC)->lpvlStmt->lpveHead;
	for (i=0; i<nSubState && lpve; i++)
		lpve = lpve->lpveNext;
	if (lpve) {
		// 실행할 statement가 남았을 때
		lpmemPgm->PushCounter(RSC_BEGIN, nSubState+1, lpPC, lpTemporaryMem);
		rscCode = RSC_STMT;
		lpTemporaryMem = NULL;
		lpPC = lpve->lpElement;
		nSubState = 0;
	} else {
		// begin end 끝
		free(lpTemporaryMem);
		PopPCFromStmt;
	}

	return true;
}

bool 
CPU::TurnReturnStmt(void)
{
	Value *lpvTemp;

	if (nSubState==0) {
		// 리턴값 계산
		lpmemPgm->PushCounter(RSC_RETURN, 1, lpPC, malloc(sizeof(Value*)));
		rscCode = RSC_EXPR;
		lpTemporaryMem = NULL;
		lpPC = ((ReturnStmt*)lpPC)->exprReturn;
	} else {
		// 리턴 변수에 값을 저장
		if (nLeftPower<nReturnCPUPower) { PauseCPU; }
		nLeftPower -= nReturnCPUPower;

		lpvTemp = lpmemPgm->QueryVariable("");
		switch (lpvTemp->lpdt->tcType) {
		case TC_INT:
			((IntValue*)lpvTemp)->n = ((IntValue*)lpvLastReturn)->n;
			break;
		case TC_REAL:
			((RealValue*)lpvTemp)->r = ((RealValue*)lpvLastReturn)->r;
			break;
		case TC_BOOL:
			((BoolValue*)lpvTemp)->b = ((BoolValue*)lpvLastReturn)->b;
			break;
		case TC_ARRAY:
			memcpy(((ArrayValue*)lpvTemp)->value,
				((ArrayValue*)lpvLastReturn)->value,
				((ArrayType*)lpvTemp->lpdt)->GetElementSize()*
				((ArrayType*)lpvTemp->lpdt)->nLength);
			break;
		case TC_OBJECT:
			((ObjectValue*)lpvTemp)->partObject =
				((ObjectValue*)lpvLastReturn)->partObject;
			break;
		}
		// return문 끝냄
		delete lpvLastReturn;
		PopPCFromStmt;
	}

	return true;
}

bool 
CPU::TurnWaitStmt(void)
{
	if (nSubState==0) {
		// 임시 저장 장소 초기화와 condition 계산
		lpmemPgm->PushCounter(RSC_WAIT, 2, lpPC, malloc(sizeof(Value*)));
		lpTemporaryMem = NULL;
		lpPC = ((WaitStmt*)lpPC)->exprCond;
		rscCode = RSC_EXPR;
	} else if (nSubState==1) {
		// condition 재계산
		lpmemPgm->PushCounter(RSC_WAIT, 2, lpPC, lpTemporaryMem);
		lpTemporaryMem = NULL;
		lpPC = ((WaitStmt*)lpPC)->exprCond;
		rscCode = RSC_EXPR;
		nSubState = 0;
	} else if (((BoolValue*)lpvLastReturn)->b) {
		// condition이 참일 때
		delete lpvLastReturn;
		free(lpTemporaryMem);
		PopPCFromStmt;
	} else {
		// condition이 거짓일 때, 다음 턴에 다시 계산
		delete lpvLastReturn;
		nSubState = 1;
		nLeftPower = 0;
		PauseCPU;
	}

	return true;
}

bool 
CPU::TurnConstExpr(void)
{
	void *lpOldPC;

	if (nLeftPower<nConstCPUPower) { PauseCPU; }
	nLeftPower -= nConstCPUPower;

	lpmemPgm->PopCounter(rscCode, nSubState, lpOldPC, lpTemporaryMem);
	switch (((Expression*)lpPC)->ecCode) {
	case EC_BOOL:
		lpvLastReturn = new BoolValue();
		((BoolValue*)lpvLastReturn)->b =
			((BoolValue*)((ConstantExpr*)lpPC)->lpvConst)->b;
		break;
	case EC_INT:
		lpvLastReturn = new IntValue();
		((IntValue*)lpvLastReturn)->n =
			((IntValue*)((ConstantExpr*)lpPC)->lpvConst)->n;
		break;
	case EC_REAL:
		lpvLastReturn = new RealValue();
		((RealValue*)lpvLastReturn)->r =
			((RealValue*)((ConstantExpr*)lpPC)->lpvConst)->r;
		break;
	}
	lpPC = lpOldPC;

	return true;
}

bool 
CPU::TurnBopExpr(void)
{
	Value *lpvLeft, *lpvRight;
	void *lpOldPC;

	if (nSubState==0) {
		lpmemPgm->PushCounter(RSC_BOP, 1, lpPC, malloc(sizeof(Value*)*2));
		lpPC = ((BopExpr*)lpPC)->exprLeft;
		rscCode = RSC_EXPR;
		lpTemporaryMem = NULL;
	} else if (nSubState==1) {
		((Value**)lpTemporaryMem)[1] = lpvLastReturn;
		lpmemPgm->PushCounter(RSC_BOP, 2, lpPC, lpTemporaryMem);
		lpPC = ((BopExpr*)lpPC)->exprRight;
		rscCode = RSC_EXPR;
		lpTemporaryMem = NULL;
		nSubState = 0;
	} else {
		if (nLeftPower<nBopCPUPower) { PauseCPU; }
		nLeftPower -= nBopCPUPower;

		lpvRight = lpvLastReturn;
		lpvLeft = ((Value**)lpTemporaryMem)[1];
		free(lpTemporaryMem);
		lpmemPgm->PopCounter(rscCode, nSubState, lpOldPC, lpTemporaryMem);
		switch (((Expression*)lpPC)->ecCode) {
		case EC_ADD:
			lpvLastReturn = Add(lpvLeft, lpvRight);
			break;
		case EC_SUB:
			lpvLastReturn = Sub(lpvLeft, lpvRight);
			break;
		case EC_MUL:
			lpvLastReturn = Mul(lpvLeft, lpvRight);
			break;
		case EC_DIV:
			lpvLastReturn = Div(lpvLeft, lpvRight);
			break;
		case EC_MOD:
			lpvLastReturn = Mod(lpvLeft, lpvRight);
			break;
		case EC_EQ:
			lpvLastReturn = EQ(lpvLeft, lpvRight);
			break;
		case EC_NE:
			lpvLastReturn = NE(lpvLeft, lpvRight);
			break;
		case EC_GT:
			lpvLastReturn = GT(lpvLeft, lpvRight);
			break;
		case EC_GE:
			lpvLastReturn = GE(lpvLeft, lpvRight);
			break;
		case EC_LT:
			lpvLastReturn = LT(lpvLeft, lpvRight);
			break;
		case EC_LE:
			lpvLastReturn = LE(lpvLeft, lpvRight);
			break;
		case EC_AND:
			lpvLastReturn = And(lpvLeft, lpvRight);
			break;
		case EC_OR:
			lpvLastReturn = Or(lpvLeft, lpvRight);
			break;
		}

		delete lpvLeft;
		delete lpvRight;
		lpPC = lpOldPC;
	}

	return true;
}

bool
CPU::TurnNotExpr(void)
{
	Value *lpvReturn;

	if (nSubState==0) {
		lpmemPgm->PushCounter(RSC_NOT, 1, lpPC, malloc(sizeof(Value*)));
		lpPC = ((NotExpr*)lpPC)->exprBool;
		rscCode = RSC_EXPR;
		lpTemporaryMem = NULL;
	} else {
		if (nLeftPower<nNotCPUPower) { PauseCPU; }
		nLeftPower -= nNotCPUPower;

		lpvReturn = new BoolValue();
		((BoolValue*)lpvReturn)->b = !(((BoolValue*)lpvLastReturn)->b);
		delete lpvLastReturn;
		free(lpTemporaryMem);
		lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
		lpvLastReturn = lpvReturn;
	}

	return true;
}

bool
CPU::TurnVarExpr(void)
{
	int nDimension(0), nSize;
	VoidElement *lpve;
	DataType *lpdt;
	Value *lpvTemp;
	byte *lpSave;

	if (nSubState==0) {
		// 임시 저장 공간 초기화
		lpve = ((VarExpr*)lpPC)->lpvlExprIndexes->lpveHead;
		nDimension = 0;
		while (lpve) {
			nDimension++;
			lpve = lpve->lpveNext;
		}
		lpTemporaryMem = malloc(sizeof(Value*)+sizeof(int)*(nDimension+1));
		((int*)lpTemporaryMem+1)[0] = nDimension;
		if (nDimension) {
			// 첫번째 인덱스 계산
			lpmemPgm->PushCounter(RSC_ASSIGN, 1, lpPC, lpTemporaryMem);
			lpPC = ((VarExpr*)lpPC)->lpvlExprIndexes->lpveHead->lpElement;
			rscCode = RSC_EXPR;
			lpTemporaryMem = NULL;
		} else {
			// 인덱스가 없는 경우
			nSubState = -1;
		}
	} else if (nSubState!=-1 && ((int*)lpTemporaryMem+1)[0]>nSubState) {
		// 계산할 인덱스가 남았을 때
		((int*)lpTemporaryMem+1)[nSubState] = 
			((IntValue*)lpvLastReturn)->n;
		delete lpvLastReturn;
		nSubState++;
		lpve = ((VarExpr*)lpPC)->lpvlExprIndexes->lpveHead;
		for (nDimension = 1; nDimension<nSubState; nDimension++)
			lpve = lpve->lpveNext;
		lpmemPgm->PushCounter(RSC_VAR, nSubState+1, lpPC, lpTemporaryMem);
		lpPC = lpve->lpElement;
		nSubState = 0;
		rscCode = RSC_EXPR;
		lpTemporaryMem = NULL;
	} else if (nSubState!=-1) {
		// 인덱스를 모두 계산했을 때
		((int*)lpTemporaryMem+1)[nSubState] = 
			((IntValue*)lpvLastReturn)->n;
		delete lpvLastReturn;
		nSubState = -1;
	} else if (((VarExpr*)lpPC)->lpszScope) {
		Part *partObject;

		if (nLeftPower<nAttrCPUPower) { PauseCPU; }
		nLeftPower -= nAttrCPUPower;

		partObject = lpexExplorer->QueryPart(((VarExpr*)lpPC)->lpszScope);
		if (!partObject) {
			lpmemPgm->PushCounter(RSC_STOP, STOP_BYWRONGPART, lpPC, 
				lpTemporaryMem);
			return false;
		}
		lpvTemp = partObject->Attribute(((VarExpr*)lpPC)->lpszId);
		if (!lpvTemp) {
			lpmemPgm->PushCounter(RSC_STOP, STOP_BYWRONGATTR, lpPC, 
				lpTemporaryMem);
		}
		switch (lpvTemp->lpdt->tcType) {
		case TC_INT:
		case TC_REAL:
		case TC_BOOL:
		case TC_OBJECT:
			free(lpTemporaryMem);
			lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
			lpvLastReturn = lpvTemp;
			break;
		case TC_ARRAY:
			lpSave = ((ArrayValue*)lpvTemp)->value;
			lpdt = lpvTemp->lpdt;
			nSize = ((ArrayType*)lpdt)->GetElementSize() * 
				((ArrayType*)lpdt)->nLength;
			while (nDimension<((int*)lpTemporaryMem+1)[0]) {
				nSize = ((ArrayType*)lpdt)->GetElementSize();
				lpSave += nSize*
					((int*)lpTemporaryMem+1)[nDimension+1];
				nDimension++;
				lpdt = ((ArrayType*)lpdt)->lpdtElementType;
			}
			free(lpTemporaryMem);
			lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
			switch (lpdt->tcType) {
			case TC_INT:
				lpvLastReturn = new IntValue();
				((IntValue*)lpvLastReturn)->n = *((int*)lpSave);
				break;
			case TC_REAL:
				lpvLastReturn = new RealValue();
				((RealValue*)lpvLastReturn)->r = *((double*)lpSave);
				break;
			case TC_BOOL:
				lpvLastReturn = new BoolValue();
				((BoolValue*)lpvLastReturn)->b = *((bool*)lpSave);
				break;
			case TC_OBJECT:
				lpvLastReturn = new ObjectValue(
						((ObjectType*)lpdt)->lpszObject,
						*((Part**)lpSave)
					);
				break;
			case TC_ARRAY:
				lpvLastReturn = new ArrayValue(((ArrayType*)lpdt)->CopyType());
				memcpy(((ArrayValue*)lpvLastReturn)->value, lpSave, nSize);
				break;
			}
			delete lpvTemp;
		}
	} else {
		if (nLeftPower<nVarCPUPower) { PauseCPU; }
		nLeftPower -= nVarCPUPower;

		lpvTemp = lpmemPgm->QueryVariable(((VarExpr*)lpPC)->lpszId);
		if (!lpvTemp) {
			Part *partObject = lpexExplorer->QueryPart(((VarExpr*)lpPC)->lpszId);
			if (partObject) {
				free(lpTemporaryMem);
				lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
				lpvLastReturn = new ObjectValue("Object", partObject);
				return true;
			} else {
				lpmemPgm->PushCounter(RSC_STOP, STOP_BYWRONGATTR, lpPC, 
					lpTemporaryMem);
			}
		}

		switch (lpvTemp->lpdt->tcType) {
		case TC_INT:
			free(lpTemporaryMem);
			lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
			lpvLastReturn = new IntValue();
			((IntValue*)lpvLastReturn)->n = ((IntValue*)lpvTemp)->n;
			break;
		case TC_REAL:
			free(lpTemporaryMem);
			lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
			lpvLastReturn = new RealValue();
			((RealValue*)lpvLastReturn)->r = ((RealValue*)lpvTemp)->r;
			break;
		case TC_BOOL:
			free(lpTemporaryMem);
			lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
			lpvLastReturn = new BoolValue();
			((BoolValue*)lpvLastReturn)->b = ((BoolValue*)lpvTemp)->b;
			break;
		case TC_OBJECT:
			free(lpTemporaryMem);
			lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
			lpvLastReturn = new ObjectValue(
					((ObjectType*)lpvTemp->lpdt)->lpszObject,
					((ObjectValue*)lpvTemp)->partObject
				);
			break;
		case TC_ARRAY:
			lpSave = ((ArrayValue*)lpvTemp)->value;
			lpdt = lpvTemp->lpdt;
			nSize = ((ArrayType*)lpdt)->GetElementSize() * 
				((ArrayType*)lpdt)->nLength;
			while (nDimension<((int*)lpTemporaryMem+1)[0]) {
				nSize = ((ArrayType*)lpdt)->GetElementSize();
				lpSave += nSize*
					((int*)lpTemporaryMem+1)[nDimension+1];
				nDimension++;
				lpdt = ((ArrayType*)lpdt)->lpdtElementType;
			}
			free(lpTemporaryMem);
			lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
			switch (lpdt->tcType) {
			case TC_INT:
				lpvLastReturn = new IntValue();
				((IntValue*)lpvLastReturn)->n = *((int*)lpSave);
				break;
			case TC_REAL:
				lpvLastReturn = new RealValue();
				((RealValue*)lpvLastReturn)->r = *((double*)lpSave);
				break;
			case TC_BOOL:
				lpvLastReturn = new BoolValue();
				((BoolValue*)lpvLastReturn)->b = *((bool*)lpSave);
				break;
			case TC_OBJECT:
				lpvLastReturn = new ObjectValue(
						((ObjectType*)lpdt)->lpszObject,
						*((Part**)lpSave)
					);
				break;
			case TC_ARRAY:
				lpvLastReturn = new ArrayValue(((ArrayType*)lpdt)->CopyType());
				memcpy(((ArrayValue*)lpvLastReturn)->value, lpSave, nSize);
				break;
			}
		}
	}

	return true;
}

bool
CPU::TurnFuncExpr(void)
{
	VoidElement *lpve;
	ScopeElement *lpse, *lpseTemp;
	Scope *lpslNewLocal;
	Value *lpvReturn;
	int i;

	if (nSubState==0) {
		lpTemporaryMem = malloc(sizeof(void*)*3);
		((VoidList**)lpTemporaryMem)[1] = new VoidList();
	} else if (nSubState==-2) {
		// call문 끝내기
		delete lpvLastReturn;
		delete ((VoidList**)lpTemporaryMem)[1];
		free(lpTemporaryMem);
		lpmemPgm->PopVarScope(lpslNewLocal);
		lpvReturn = (Value*)lpslNewLocal->lpseHead->lpElement;
		for (lpse = lpslNewLocal->lpseHead->lpseNext; lpse; lpse = lpse->lpseNext)
			delete (Value*)lpse->lpElement;
		delete lpslNewLocal;
		lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
		if (rscCode == RSC_STOP) return false;
		lpvLastReturn = lpvReturn;
		return true;
	} else if (nSubState == -1) {
		// 계산할 파라미터가 없을 때
		if (((FuncExpr*)lpPC)->lpszScope) {
			// Operation call
			if (nLeftPower<nOpCPUPower) { PauseCPU; }
			nLeftPower -= nOpCPUPower;

			Part *partObject;
			Value *lpvPart = lpmemPgm->QueryVariable(((FuncExpr*)lpPC)->lpszScope);
			if (lpvPart) {
				if (lpvPart->lpdt->tcType==TC_OBJECT)
					partObject = ((ObjectValue*)lpvPart)->partObject;
				else partObject = NULL;
			} else {
				partObject = lpexExplorer->QueryPart(
					((FuncExpr*)lpPC)->lpszScope);
			}

			if (!partObject) {
				lpmemPgm->PushCounter(RSC_STOP, STOP_BYWRONGPART, 
					lpPC, lpTemporaryMem);
				return false;
			}
			lpvReturn = partObject->Operation(((FuncExpr*)lpPC)->lpszId,
				((VoidList**)lpTemporaryMem)[1]);
			if (lpvLastReturn) delete lpvLastReturn;
			lpve = ((VoidList**)lpTemporaryMem)[1]->lpveHead;
			while (lpve) {
				delete (Value*)lpve->lpElement;
				lpve = lpve->lpveNext;
			}
			delete ((VoidList**)lpTemporaryMem)[1];
			free(lpTemporaryMem);
			lpmemPgm->PopCounter(rscCode, nSubState, lpPC, lpTemporaryMem);
			if (rscCode == RSC_STOP) return false;
			lpvLastReturn = lpvReturn;
			return true;
		} else {
			// function call
			if (nLeftPower<nFuncCPUPower) { PauseCPU; }
			nLeftPower -= nFuncCPUPower;

			Function *func = lpmemPgm->QueryFunction(((FuncExpr*)lpPC)->lpszId);
			lpslNewLocal = new Scope();

			// 파라미터 복사
			nSubState = 0;
			lpve = ((VoidList**)lpTemporaryMem)[1]->lpveHead;
			while (lpve) {
				nSubState++;
				lpve = lpve->lpveNext;
			}
			lpve = ((VoidList**)lpTemporaryMem)[1]->lpveHead;
			while (nSubState>0) {
				i = --nSubState;
				lpse = func->lpslDtParam->lpseHead;
				while (i>0 && lpse) {
					lpse = lpse->lpseNext; i--;
				}
				lpseTemp = new ScopeElement();
				lpseTemp->lpszId = (char*)malloc(sizeof(char)*
					(strlen(lpse->lpszId)+1));
				memcpy(lpseTemp->lpszId, lpse->lpszId,
					sizeof(char)*(strlen(lpse->lpszId)+1));
				lpseTemp->lpElement = lpve->lpElement;
				lpslNewLocal->Add(lpseTemp);
				lpve = lpve->lpveNext;
			}

			// 지역 변수 생성
			lpse = func->lpslDtLocal->lpseHead;
			while (lpse) {
				lpseTemp = new ScopeElement();
				lpseTemp->lpszId = (char*)malloc(sizeof(char)*
					(strlen(lpse->lpszId)+1));
				memcpy(lpseTemp->lpszId, lpse->lpszId, 
					sizeof(char)*(strlen(lpse->lpszId)+1));
				switch (((DataType*)lpse->lpElement)->tcType) {
				case TC_INT:
					lpseTemp->lpElement = new IntValue();
					break;
				case TC_REAL:
					lpseTemp->lpElement = new RealValue();
					break;
				case TC_BOOL:
					lpseTemp->lpElement = new BoolValue();
					break;
				case TC_ARRAY:
					lpseTemp->lpElement = 
						new ArrayValue(
							((ArrayType*)lpse->lpElement)->CopyType());
					break;
				case TC_OBJECT:
					lpseTemp->lpElement = new ObjectValue(
						((ObjectType*)lpse->lpElement)->lpszObject, NULL);
					break;
				}
				lpslNewLocal->Add(lpseTemp);
				lpse = lpse->lpseNext;
			}

			// 리턴 변수 생성
			if (func->lpdtReturn->tcType != TC_VOID) {
				lpseTemp = new ScopeElement();
				lpseTemp->lpszId = (char *)malloc(sizeof(char));
				lpseTemp->lpszId[0] = '\0';
				switch (func->lpdtReturn->tcType) {
				case TC_INT:
					lpseTemp->lpElement = new IntValue();
					break;
				case TC_REAL:
					lpseTemp->lpElement = new RealValue();
					break;
				case TC_BOOL:
					lpseTemp->lpElement = new BoolValue();
					break;
				case TC_ARRAY:
					lpseTemp->lpElement = 
						new ArrayValue(
						((ArrayType*)lpse->lpElement)->CopyType());
					break;
				case TC_OBJECT:
					lpseTemp->lpElement = new ObjectValue(
						((ObjectType*)lpse->lpElement)->lpszObject, NULL);
					break;
				}
				lpslNewLocal->Add(lpseTemp);
			}

			// Push and call func
			lpmemPgm->PushVarScope(lpslNewLocal);
			lpmemPgm->PushCounter(RSC_FUNC, -2, lpPC, lpTemporaryMem);
			nSubState = 0;
			rscCode = RSC_STMT;
			lpPC = (void*)func->stmtBody;
			lpTemporaryMem = NULL;

			return true;
		}
	} else if (nSubState>0) {
		((VoidList**)lpTemporaryMem)[1]->Add(lpvLastReturn);
	}

	lpve = ((FuncExpr*)lpPC)->lpvlExprParam->lpveHead;
	for (i=nSubState; i>0 && lpve; i--)
		lpve = lpve->lpveNext;

	if (lpve) {
		// 계산할 파라미터가 남았을 때
		lpmemPgm->PushCounter(RSC_FUNC, nSubState+1, lpPC, lpTemporaryMem);
		rscCode = RSC_EXPR;
		nSubState = 0;
		lpPC = lpve->lpElement;
		lpTemporaryMem = NULL;
	} else {
		nSubState = -1;
	}

	return true;
}

Value *
CPU::Add(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new IntValue();
			((IntValue*)lpvReturn)->n = 
				((IntValue*)lpvLeft)->n + ((IntValue*)lpvRight)->n;
		} else {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((IntValue*)lpvLeft)->n + ((RealValue*)lpvRight)->r;
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((RealValue*)lpvLeft)->r + ((IntValue*)lpvRight)->n;
		} else {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((RealValue*)lpvLeft)->r + ((RealValue*)lpvRight)->r;
		}
	}

	return lpvReturn;
}

Value *
CPU::Sub(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new IntValue();
			((IntValue*)lpvReturn)->n = 
				((IntValue*)lpvLeft)->n - ((IntValue*)lpvRight)->n;
		} else {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((IntValue*)lpvLeft)->n - ((RealValue*)lpvRight)->r;
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((RealValue*)lpvLeft)->r - ((IntValue*)lpvRight)->n;
		} else {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((RealValue*)lpvLeft)->r - ((RealValue*)lpvRight)->r;
		}
	}

	return lpvReturn;
}

Value *
CPU::Mul(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new IntValue();
			((IntValue*)lpvReturn)->n = 
				((IntValue*)lpvLeft)->n * ((IntValue*)lpvRight)->n;
		} else {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((IntValue*)lpvLeft)->n * ((RealValue*)lpvRight)->r;
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((RealValue*)lpvLeft)->r * ((IntValue*)lpvRight)->n;
		} else {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((RealValue*)lpvLeft)->r * ((RealValue*)lpvRight)->r;
		}
	}

	return lpvReturn;
}

Value *
CPU::Div(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new IntValue();
			((IntValue*)lpvReturn)->n = 
				((IntValue*)lpvLeft)->n / ((IntValue*)lpvRight)->n;
		} else {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((IntValue*)lpvLeft)->n / ((RealValue*)lpvRight)->r;
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((RealValue*)lpvLeft)->r / ((IntValue*)lpvRight)->n;
		} else {
			lpvReturn = new RealValue();
			((RealValue*)lpvReturn)->r = 
				((RealValue*)lpvLeft)->r / ((RealValue*)lpvRight)->r;
		}
	}

	return lpvReturn;
}

Value *
CPU::Mod(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	lpvReturn = new IntValue();
	((IntValue*)lpvReturn)->n = 
		((IntValue*)lpvLeft)->n % ((IntValue*)lpvRight)->n;

	return lpvReturn;
}

Value *
CPU::EQ(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n == ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n == ((RealValue*)lpvRight)->r);
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r == ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r == ((RealValue*)lpvRight)->r);
		}
	}

	return lpvReturn;
}

Value *
CPU::NE(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n != ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n != ((RealValue*)lpvRight)->r);
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r != ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r != ((RealValue*)lpvRight)->r);
		}
	}

	return lpvReturn;
}

Value *
CPU::GT(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n > ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n > ((RealValue*)lpvRight)->r);
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r > ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r > ((RealValue*)lpvRight)->r);
		}
	}

	return lpvReturn;
}

Value *
CPU::GE(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n >= ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n >= ((RealValue*)lpvRight)->r);
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r >= ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r >= ((RealValue*)lpvRight)->r);
		}
	}

	return lpvReturn;
}

Value *
CPU::LT(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n < ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n < ((RealValue*)lpvRight)->r);
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r < ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r < ((RealValue*)lpvRight)->r);
		}
	}

	return lpvReturn;
}

Value *
CPU::LE(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	if (lpvLeft->lpdt->tcType == TC_INT) {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n <= ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((IntValue*)lpvLeft)->n <= ((RealValue*)lpvRight)->r);
		}
	} else {
		if (lpvRight->lpdt->tcType == TC_INT) {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r <= ((IntValue*)lpvRight)->n);
		} else {
			lpvReturn = new BoolValue();
			((BoolValue*)lpvReturn)->b = 
				(((RealValue*)lpvLeft)->r <= ((RealValue*)lpvRight)->r);
		}
	}

	return lpvReturn;
}

Value *
CPU::And(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	lpvReturn = new BoolValue();
	((BoolValue*)lpvReturn)->b =
		((BoolValue*)lpvLeft)->b && ((BoolValue*)lpvRight)->b;
	return lpvReturn;
}

Value *
CPU::Or(Value *lpvLeft, Value *lpvRight)
{
	Value *lpvReturn;

	lpvReturn = new BoolValue();
	((BoolValue*)lpvReturn)->b =
		((BoolValue*)lpvLeft)->b || ((BoolValue*)lpvRight)->b;
	return lpvReturn;
}
