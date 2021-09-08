////////////////////////////////////////////////////////////////////////////////
//
// "Memory.h"
//		Memory Part에 대한 클래스 선언
//												작성자 : asura
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
//		현재 Memory에 있는 프로그램의 상태
//												작성자 : asura
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
//		프로그램에서 실행중인 부분을 지정
//												작성자 : asura
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
//		함수 호출시에 지역 변수를 저장하기 위한 스택
//												작성자 : asura
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
//		함수 호출시에 지역 변수를 저장하기 위한 스택
//												작성자 : asura
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
//		메모리 파트 클래스
//												작성자 : asura
//												Last Update : 2000. 10. 12.
//
////////////////////////////////////////////////////////////////////////////////

class Memory : public Part {
	public:
		Memory(Program *pgmMain, int nSize);		// 생성자

		void Turn(void);
		void Draw(void);
		Value *Attribute(char *lpszAttr);	
		Value *Operation(char *lpszOp, VoidList *lpvlArgument);

		void PushVarScope(Scope *lpslLocal);
		void PopVarScope(Scope *&lpslLocal);		// 변수 저장 Stack

		void PushCounter(RunStateCode rscNewCode, int nNewState,
			void *lpNewPC, void *lpTemporaryMem);
		void PopCounter(RunStateCode &rscOldCode, int &nOldState, 
			void *&lpOldPC, void *&lpTemporaryMem);	// PC를 바꾸는 함수

		bool Malloc(int nSize);						// 사용중인 메모리가 증가
		void Free(int nSize);						// 사용중인 메모리가 감소

		Function *QueryFunction(char *lpszFunc);	// 함수의 포인터를 구한다
		Value *QueryVariable(char *lpszVar);		// 변수의 포인터를 구한다

		void MemoryRunStatus(MemErrCode &mecStatus);	
													// 프로그램 실행상태를 구한다

	private:
		int nFreeMem;								// 여유 공간
		Program *pgmProgram;						// 프로그램

		ProgramCounter *lppcTop;					// PC
		VariableStack *lpvsTop;						// 스택의 Top
		Scope *lpslGlobal;							// Global Variable
};

#endif // _MEMORY_H_ASURA_BECD_