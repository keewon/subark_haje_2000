////////////////////////////////////////////////////////////////////////////////
//
// "Memory.cpp"
//		Memory 클래스 정의
//												작성자 : asura
//												Last Update : 2000. 10. 12.
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include <string.h>
#include <malloc.h>
#include "Memory.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Memory::Memroy(Program *pgmMain, int nSize)
//		class Memory의 생성자
//		IN:
//			pgmMain - 실행할 프로그램
//			nSize - 메모리 크기
//												작성자 : asura
//												Last Update : 2000. 8. 15.
//
////////////////////////////////////////////////////////////////////////////////

Memory::Memory(Program *pgmMain, int nSize)
{
	ScopeElement *lpse, *lpseTemp;

	pgmProgram = pgmMain;

	lppcTop = new ProgramCounter();
	lppcTop->rsState.rscCode = RSC_STMT;
	lppcTop->rsState.nSubState = 0;
	lppcTop->lpPC = pgmMain->stmtBody;
	lppcTop->lppcParent = NULL;
	lpvsTop = NULL;							// 스택 초기화

	lpslGlobal = new Scope;
	lpse = pgmMain->lpslDtGlobal->lpseHead;
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
				new ArrayValue((ArrayType*)lpse->lpElement);
			break;
		case TC_OBJECT:
			lpseTemp->lpElement = new ObjectValue(
				((ObjectType*)lpse->lpElement)->lpszObject, NULL);
			break;
		}
		lpslGlobal->Add(lpseTemp);
		lpse = lpse->lpseNext;
	}										// 전역 변수 생성
}

////////////////////////////////////////////////////////////////////////////////
//
// void Memory::Turn(void)
//		아무것도 안한다
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

void 
Memory::Turn(void)
{
}

void
Memory::Draw(void)
{

}

////////////////////////////////////////////////////////////////////////////////
//
// Value *Memory::Attribute(char *lpszAttr)
//		메모리의 Attribute
//		IN:
//			lpszAttr - Attribute 이름
//		RETURN:
//			항상 NULL
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

Value *
Memory::Attribute(char *lpszAttr)
{
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// Value *Memory::Operation(char *lpszOp, VoidList *lpvlArgument)
//		메모리의 Operation:
//			procedure initialize()
//		IN:
//			lpszOp - Operation 이름
//			lpvlArgument - 파라미터 리스트
//		RETURN:
//			lpszOp가 "initialize"일면 VOID값을, 아니면 NULL
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

Value *
Memory::Operation(char *lpszOp, VoidList *lpvlArgument)
{
	if (!strcmp(lpszOp, "initialize")) {
		ProgramCounter *lppcTemp;
		Value *lpvReturn;

		while (lppcTop) {
			lppcTemp = lppcTop;
			lppcTop = lppcTop->lppcParent;
			delete lppcTemp;
		}
		lppcTop = new ProgramCounter();
		lppcTop->rsState.rscCode = RSC_STMT;
		lppcTop->rsState.nSubState = 0;
		lppcTop->lpPC = pgmProgram->stmtBody;
		lppcTop->lppcParent = NULL;
		lpvsTop = NULL;

		lpvReturn = new Value();
		lpvReturn->lpdt = new DataType();
		lpvReturn->lpdt->tcType = TC_VOID;
		return lpvReturn;
	} else return NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
// void Memory::PushVarScope(Scope *lpslLocal)
//		스택에 로컬 변수들을 저장한다.
//		IN:
//			lpslLocal - 새로운 로컬 변수 스코프
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

void
Memory::PushVarScope(Scope *lpslLocal)
{
	VariableStack *lpvsTemp;

	lpvsTemp = new VariableStack();
	lpvsTemp->lpslLocal = lpslLocal;
	lpvsTemp->lpvsLower = lpvsTop;
	lpvsTop = lpvsTemp;
}

////////////////////////////////////////////////////////////////////////////////
//
// void Memory::PushVarScope(Scope *&lpslLocal)
//		스택에 로컬 변수들을 저장한다.
//		OUT:
//			lpslLocal - 현재 로컬 변수 스코프
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

void
Memory::PopVarScope(Scope *&lpslLocal)
{
	if (lpvsTop) {
		VariableStack *lpvsTemp;

		lpslLocal = lpvsTop->lpslLocal;
		lpvsTemp = lpvsTop;
		lpvsTop = lpvsTop->lpvsLower;
		delete lpvsTemp;
	} else lpslLocal = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//
//	void Memory::PushCounter(RunStateCode rscNewCode, int nNewState,
//		void *lpNewPC, void *lpTemporaryMem)
//		PC 스택에 현재 PC를 저장
//		IN:
//			rscNewCode, nNewState - 현재 프로그램 실행 상태
//			lpNewPC - 현재 프로그램 실행 위치
//			lpTemporaryMem - 임시 저장 공간
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

void 
Memory::PushCounter(RunStateCode rscNewCode, int nNewState,
	void *lpNewPC, void *lpTemporaryMem)
{
	ProgramCounter *lppcTemp;

	lppcTemp = new ProgramCounter();
	lppcTemp->rsState.rscCode = rscNewCode;
	lppcTemp->rsState.nSubState = nNewState;
	lppcTemp->lpPC = lpNewPC;
	lppcTemp->lpTemporaryMem = lpTemporaryMem;

	lppcTemp->lppcParent = lppcTop;
	lppcTop = lppcTemp;
}

////////////////////////////////////////////////////////////////////////////////
//
//	void Memory::PopCounter(RunStateCode &rscOldCode, int &nOldState,
//		void *&lpOldPC, void *&lpTemporaryMem)
//		PC 스택에 PC를 하나 뺀다
//		OUT:
//			rscNewCode, nNewState - 마지막으로 저장한 프로그램 실행 상태
//			lpNewPC - 마지막으로 저장한 프로그램 실행 위치
//			lpTemporaryMem - 임시 저장 공간
//												작성자 : asura
//												Last Update : 2000. 10. 11.
//
////////////////////////////////////////////////////////////////////////////////

void
Memory::PopCounter(RunStateCode &rscOldCode, int &nOldState,
	void *&lpOldPC, void *&lpTemporaryMem)
{
	ProgramCounter *lppcTemp;

	if (lppcTop) {
		rscOldCode = lppcTop->rsState.rscCode;
		nOldState = lppcTop->rsState.nSubState;
		lpOldPC = lppcTop->lpPC;
		lpTemporaryMem = lppcTop->lpTemporaryMem;

		lppcTemp = lppcTop;
		lppcTop = lppcTop->lppcParent;
		delete lppcTemp;
	} else {
		rscOldCode = RSC_STOP;
		lpOldPC = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//	bool Memory::Malloc(int nSize)
//		메모리 사용양 증가를 통보한다.
//		IN:
//			nSize - 새로 필요한 메모리 공간 양
//		RETURN:
//			남은 메모리가 충분하면 true, 아니면 false
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

bool
Memory::Malloc(int nSize)
{
	if (nFreeMem<nSize) return false;
	else {
		nSize -= nFreeMem;
		return true;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
//	void Memory::Free(int nSize)
//		메모리 사용양 감소를 통보한다.
//		OUT:
//			nSize - 사용을 끝낸 메모리 양
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

void
Memory::Free(int nSize)
{
	nFreeMem += nSize;
	return;
}

////////////////////////////////////////////////////////////////////////////////
//
//	Function *Memory::QueryFunction(char *lpszFunc)
//		함수를 구한다
//		IN:
//			lpszFunc - 함수 이름
//		RETURN:
//			함수의 포인터. 함수 이름이 존재하지 않으면 NULL
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

Function *
Memory::QueryFunction(char *lpszFunc)
{
	return (Function *)pgmProgram->lpslFunction->Search(lpszFunc);
}

////////////////////////////////////////////////////////////////////////////////
//
//	Value *Memory::QueryVariable(char *lpszVar)
//		변수 포인터를 구한다. 먼저 지역 변수를 찾고, 그 다음에는 전역 변수를
//		찾는다.
//		IN:
//			lpszVar - 변수 이름
//		RETURN:
//			변수 값의 포인터. 변수가 존재하지 않으면 NULL
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

Value *
Memory::QueryVariable(char *lpszVar)
{
	void *lpTemp;

	if (lpvsTop && (lpTemp = lpvsTop->lpslLocal->Search(lpszVar)))
		return (Value *)lpTemp;
	else return (Value *)lpslGlobal->Search(lpszVar);
}

////////////////////////////////////////////////////////////////////////////////
//
//	void Memory::MemoryRunStatus(MemErrCode &mecStatus)
//		프로그램 실행 상태를 구한다.
//		OUT:
//			mecStatus - 현재 프로그램의 실행 상태
//												작성자 : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

void
Memory::MemoryRunStatus(MemErrCode &mecStatus)
{
	if (!lppcTop) {
		// 프로그램이 초기화 되지 않았거나 실행이 끝났을 때
		mecStatus.bStopped = true;
		mecStatus.nPosition = 0;
		mecStatus.srReason = SR_EOPGM;
	} else if (lppcTop->rsState.rscCode != RSC_STOP) {
		// 프로그램이 정상 실행 중일 때
		mecStatus.bStopped = false;
	} else {
		mecStatus.bStopped = true;
		if (lppcTop->rsState.nSubState>=STOP_BYSTMT) 
			mecStatus.nPosition = ((Statement*)lppcTop->lpPC)->nPosition;
		else 
			mecStatus.nPosition = ((Statement*)lppcTop->lpPC)->nPosition;
		switch (lppcTop->rsState.nSubState%STOP_BYSTMT) {
		case STOP_BYWRONGPART:
			mecStatus.srReason = SR_WRONGPART;
			break;
		case STOP_BYWRONGATTR:
			mecStatus.srReason = SR_WRONGATTR;
			break;
		}
	}
}
