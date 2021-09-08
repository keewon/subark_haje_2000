////////////////////////////////////////////////////////////////////////////////
//
// "Stmt.h"
//		Statement 클래스
//												작성자 : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _STMT_H_ASURA_BECD_
#define _STMT_H_ASURA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////

#include "Types.h"
#include "Value.h"
#include "Expr.h"

// Public macros & Constants //////////////////////////////////////////////////

/// Class or functions /////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// enum StmtCode
//		Statement의 종류를 나타내는 코드
//												작성자 : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

typedef enum { 
	SC_IF, SC_WHILE, SC_PROC, SC_ASSIGN, SC_BEGIN, SC_RETURN, SC_WAIT 
} StmtCode;

////////////////////////////////////////////////////////////////////////////////
//
// class Statement
//		Statement의 슈퍼클래스
//												작성자 : asura
//												Last Update : 2000. 7. 28.
// <참고> Statement *형 변수의 prefix는 stmt을 쓴다
//
////////////////////////////////////////////////////////////////////////////////

class Statement {
	public:
		~Statement();

		StmtCode scCode;		// Statement의 종류
		int nPosition;			// Debug info
};

////////////////////////////////////////////////////////////////////////////////
//
// class IfStmt
//		if ... then ... else ...
//												작성자 : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

class IfStmt : public Statement {
	public:
		IfStmt();

		Expression *exprCond;		// Condition
		Statement *stmtThen;		// Condition이 참일 때 실행할 Statement
		Statement *stmtElse;		// Condition이 거짓일 때 실행할 Statement
									// 만약 NULL이면 if ... then ... 구문
};

////////////////////////////////////////////////////////////////////////////////
//
// class WhileStmt
//		while ... do ...
//												작성자 : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

class WhileStmt : public Statement {
	public:
		WhileStmt();

		Expression *exprCond;		// Condition
		Statement *stmtBody;		// Body
};

////////////////////////////////////////////////////////////////////////////////
//
// class WhileStmt
//		while ... do ...
//												작성자 : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

class ProcStmt : public Statement {
	public:
		ProcStmt();

		char *lpszScope;
		char *lpszId;
		VoidList *lpvlExprParam;
};

////////////////////////////////////////////////////////////////////////////////
//
// class AssignStmt
//		assign ... to ...
//												작성자 : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

class AssignStmt : public Statement {
	public:
		AssignStmt();

		Expression *exprValue;		// 저장할 값
		char *lpszId;				// 저장할 변수의 ID
		VoidList *lpvlExprIndexes;	// 변수가 배열일 때 Index
};

////////////////////////////////////////////////////////////////////////////////
//
// class BeginStmt
//		Statement의 리스트
//												작성자 : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

class BeginStmt : public Statement {
	public:
		BeginStmt();

		VoidList *lpvlStmt;
};

////////////////////////////////////////////////////////////////////////////////
//
// class WhileStmt
//		while ... do ...
//												작성자 : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

class ReturnStmt : public Statement {
	public:
		ReturnStmt();

		Expression *exprReturn;		// Return할 값
};

////////////////////////////////////////////////////////////////////////////////
//
// class WaitStmt
//		wait ...
//												작성자 : asura
//												Last Update : 2000. 7. 28.
//
////////////////////////////////////////////////////////////////////////////////

class WaitStmt : public Statement {
	public:
		WaitStmt();

		Expression *exprCond;		// Condition
};

#endif // _STMT_H_ASURA_BECD_