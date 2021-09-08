////////////////////////////////////////////////////////////////////////////////
//
// "Memory.cpp"
//		Memory Ŭ���� ����
//												�ۼ��� : asura
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
//		class Memory�� ������
//		IN:
//			pgmMain - ������ ���α׷�
//			nSize - �޸� ũ��
//												�ۼ��� : asura
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
	lpvsTop = NULL;							// ���� �ʱ�ȭ

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
	}										// ���� ���� ����
}

////////////////////////////////////////////////////////////////////////////////
//
// void Memory::Turn(void)
//		�ƹ��͵� ���Ѵ�
//												�ۼ��� : asura
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
//		�޸��� Attribute
//		IN:
//			lpszAttr - Attribute �̸�
//		RETURN:
//			�׻� NULL
//												�ۼ��� : asura
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
//		�޸��� Operation:
//			procedure initialize()
//		IN:
//			lpszOp - Operation �̸�
//			lpvlArgument - �Ķ���� ����Ʈ
//		RETURN:
//			lpszOp�� "initialize"�ϸ� VOID����, �ƴϸ� NULL
//												�ۼ��� : asura
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
//		���ÿ� ���� �������� �����Ѵ�.
//		IN:
//			lpslLocal - ���ο� ���� ���� ������
//												�ۼ��� : asura
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
//		���ÿ� ���� �������� �����Ѵ�.
//		OUT:
//			lpslLocal - ���� ���� ���� ������
//												�ۼ��� : asura
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
//		PC ���ÿ� ���� PC�� ����
//		IN:
//			rscNewCode, nNewState - ���� ���α׷� ���� ����
//			lpNewPC - ���� ���α׷� ���� ��ġ
//			lpTemporaryMem - �ӽ� ���� ����
//												�ۼ��� : asura
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
//		PC ���ÿ� PC�� �ϳ� ����
//		OUT:
//			rscNewCode, nNewState - ���������� ������ ���α׷� ���� ����
//			lpNewPC - ���������� ������ ���α׷� ���� ��ġ
//			lpTemporaryMem - �ӽ� ���� ����
//												�ۼ��� : asura
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
//		�޸� ���� ������ �뺸�Ѵ�.
//		IN:
//			nSize - ���� �ʿ��� �޸� ���� ��
//		RETURN:
//			���� �޸𸮰� ����ϸ� true, �ƴϸ� false
//												�ۼ��� : asura
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
//		�޸� ���� ���Ҹ� �뺸�Ѵ�.
//		OUT:
//			nSize - ����� ���� �޸� ��
//												�ۼ��� : asura
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
//		�Լ��� ���Ѵ�
//		IN:
//			lpszFunc - �Լ� �̸�
//		RETURN:
//			�Լ��� ������. �Լ� �̸��� �������� ������ NULL
//												�ۼ��� : asura
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
//		���� �����͸� ���Ѵ�. ���� ���� ������ ã��, �� �������� ���� ������
//		ã�´�.
//		IN:
//			lpszVar - ���� �̸�
//		RETURN:
//			���� ���� ������. ������ �������� ������ NULL
//												�ۼ��� : asura
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
//		���α׷� ���� ���¸� ���Ѵ�.
//		OUT:
//			mecStatus - ���� ���α׷��� ���� ����
//												�ۼ��� : asura
//												Last Update : 2000. 8. 16.
//
////////////////////////////////////////////////////////////////////////////////

void
Memory::MemoryRunStatus(MemErrCode &mecStatus)
{
	if (!lppcTop) {
		// ���α׷��� �ʱ�ȭ ���� �ʾҰų� ������ ������ ��
		mecStatus.bStopped = true;
		mecStatus.nPosition = 0;
		mecStatus.srReason = SR_EOPGM;
	} else if (lppcTop->rsState.rscCode != RSC_STOP) {
		// ���α׷��� ���� ���� ���� ��
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
