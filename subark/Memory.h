////////////////////////////////////////////////////////////////////////////////
//
// "Memory.h"
//		Memory Part�� ���� Ŭ���� ����
//												�ۼ��� : asura
//												Last Update : 2000. 10. 12.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MEMORY_H_ASURA_BECD_
#define _MEMORY_H_ASURA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////

#include "Part.h"
#include "Func.h"
#include "Pgm.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Class or functions /////////////////////////////////////////////////////////

typedef enum { 
	RSC_STMT, RSC_EXPR, RSC_STOP,
	RSC_IF, RSC_WHILE, RSC_PROC, RSC_ASSIGN, RSC_BEGIN, RSC_RETURN, RSC_WAIT,
	RSC_CONST, RSC_NOT, RSC_BOP, RSC_VAR, RSC_FUNC
} RunStateCode;
	// CPU run a statement or a expression.

#define STOP_BYSTMT			(10000)
#define STOP_BYWRONGPART	(0)
#define STOP_BYWRONGATTR	(1)

typedef enum {
	SR_Running, SR_EOPGM, SR_WRONGPART, SR_WRONGATTR
} StopReason;
	// Program stopped by some reason.

////////////////////////////////////////////////////////////////////////////////
//
// class RunState
//		���� Memory�� �ִ� ���α׷��� ����
//												�ۼ��� : asura
//												Last Update : 2000. 8. 15.
//
////////////////////////////////////////////////////////////////////////////////

class RunState {
	public:
		RunStateCode rscCode;
		int nSubState;
};

////////////////////////////////////////////////////////////////////////////////
//
// class ProgramCounter
//		���α׷����� �������� �κ��� ����
//												�ۼ��� : asura
//												Last Update : 2000. 8. 15.
//
////////////////////////////////////////////////////////////////////////////////

class ProgramCounter {
	public:
		RunState rsState;
		void *lpPC;
		void *lpTemporaryMem;
		ProgramCounter *lppcParent;
};

////////////////////////////////////////////////////////////////////////////////
//
// class VariableStack
//		�Լ� ȣ��ÿ� ���� ������ �����ϱ� ���� ����
//												�ۼ��� : asura
//												Last Update : 2000. 8. 15.
//
////////////////////////////////////////////////////////////////////////////////

class VariableStack {
	public:
		Scope *lpslLocal;
		VariableStack *lpvsLower;
};

////////////////////////////////////////////////////////////////////////////////
//
// class VariableStack
//		�Լ� ȣ��ÿ� ���� ������ �����ϱ� ���� ����
//												�ۼ��� : asura
//												Last Update : 2000. 10. 12.
//
////////////////////////////////////////////////////////////////////////////////

class MemErrCode {
	public:
		bool bStopped;
		int nPosition;
		StopReason srReason;
};

////////////////////////////////////////////////////////////////////////////////
//
// class Memory
//		�޸� ��Ʈ Ŭ����
//												�ۼ��� : asura
//												Last Update : 2000. 10. 12.
//
////////////////////////////////////////////////////////////////////////////////

class Memory : public Part {
	public:
		Memory(Program *pgmMain, int nSize);		// ������

		void Turn(void);
		void Draw(void);
		Value *Attribute(char *lpszAttr);	
		Value *Operation(char *lpszOp, VoidList *lpvlArgument);

		void PushVarScope(Scope *lpslLocal);
		void PopVarScope(Scope *&lpslLocal);		// ���� ���� Stack

		void PushCounter(RunStateCode rscNewCode, int nNewState,
			void *lpNewPC, void *lpTemporaryMem);
		void PopCounter(RunStateCode &rscOldCode, int &nOldState, 
			void *&lpOldPC, void *&lpTemporaryMem);	// PC�� �ٲٴ� �Լ�

		bool Malloc(int nSize);						// ������� �޸𸮰� ����
		void Free(int nSize);						// ������� �޸𸮰� ����

		Function *QueryFunction(char *lpszFunc);	// �Լ��� �����͸� ���Ѵ�
		Value *QueryVariable(char *lpszVar);		// ������ �����͸� ���Ѵ�

		void MemoryRunStatus(MemErrCode &mecStatus);	
													// ���α׷� ������¸� ���Ѵ�

	private:
		int nFreeMem;								// ���� ����
		Program *pgmProgram;						// ���α׷�

		ProgramCounter *lppcTop;					// PC
		VariableStack *lpvsTop;						// ������ Top
		Scope *lpslGlobal;							// Global Variable
};

#endif // _MEMORY_H_ASURA_BECD_