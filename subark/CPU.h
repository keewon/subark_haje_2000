////////////////////////////////////////////////////////////////////////////////
//
// "CPU.h"
//		CPU Part에 대한 클래스 선언
//												작성자 : asura
//												Last Update : 2000. 8. 23.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _CPU_H_ASURA_BECD_
#define _CPU_H_ASURA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////

#include "Part.h"
#include "Memory.h"
#include "Explorer.h"
#include "Value.h"

/// Public macros & Constants //////////////////////////////////////////////////

#define nDefaultCPUPower 100
#define nIfCPUPower 5
#define nWhileCPUPower 5
#define nOpCPUPower 30
#define nFuncCPUPower 10
#define nAssignCPUPower 5
#define nReturnCPUPower 5
#define nConstCPUPower 1
#define nBopCPUPower 2
#define nNotCPUPower 2
#define nAttrCPUPower 5
#define nVarCPUPower 1

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// class CPU
//		MEM에서 프로그램을 읽어서 실행시킨다.
//												작성자 : asura
//												Last Update : 2000. 8. 15.
//
////////////////////////////////////////////////////////////////////////////////

class CPU : public Part {
	public:
		CPU(Explorer *lpexExp, int nPower = nDefaultCPUPower,
			Memory *lpmemStart = NULL);	
											// 생성자, nPower는 CPU Clock을 지정
		~CPU();

		void Turn(void);					
		Value *Attribute(char *lpszAttr);	
		Value *Operation(char *lpszOp, VoidList *lpvlArgument);
		void Draw(void);

	private:
		Memory *lpmemPgm;
		Memory *lpmemNewPgm;
		Explorer *lpexExplorer;
		int nCPUPower;
		int nLeftPower;

		RunStateCode rscCode;
		int nSubState;
		void *lpPC;
		void *lpTemporaryMem;	// 현재 PC와 임시 저장 장소

		bool TurnIfStmt(void);
		bool TurnWhileStmt(void);
		bool TurnProcStmt(void);
		bool TurnAssignStmt(void);
		bool TurnBeginStmt(void);
		bool TurnReturnStmt(void);
		bool TurnWaitStmt(void);
		// 현재 PC가 Statement를 가리키고 있을 때 turn 실행 함수들

		bool TurnConstExpr(void);
		bool TurnBopExpr(void);
		bool TurnNotExpr(void);
		bool TurnVarExpr(void);
		bool TurnFuncExpr(void);
		// 현재 PC가 Expression을 가리키고 있을 때 turn 실행 함수들

		Value *Add(Value *lpvLeft, Value *lpvRight);
		Value *Sub(Value *lpvLeft, Value *lpvRight);
		Value *Mul(Value *lpvLeft, Value *lpvRight);
		Value *Div(Value *lpvLeft, Value *lpvRight);
		Value *Mod(Value *lpvLeft, Value *lpvRight);
		Value *EQ(Value *lpvLeft, Value *lpvRight);
		Value *NE(Value *lpvLeft, Value *lpvRight);
		Value *GT(Value *lpvLeft, Value *lpvRight);
		Value *GE(Value *lpvLeft, Value *lpvRight);
		Value *LT(Value *lpvLeft, Value *lpvRight);
		Value *LE(Value *lpvLeft, Value *lpvRight);
		Value *And(Value *lpvLeft, Value *lpvRight);
		Value *Or(Value *lpvLeft, Value *lpvRight);
		// Binary operation 결과 값 계산 함수들
};

#endif // _CPU_H_ASURA_BECD_