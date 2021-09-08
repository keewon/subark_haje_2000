#ifndef ASURA_PARSER_H
#define ASURA_PARSER_H

#include <stdio.h>

/*
 * List
 */

class VoidElement {
	public:
		VoidElement();

		void *element;
		VoidElement *next;
};

class VoidList {
	public:
		VoidList();
		~VoidList();

		void Add(void *newElement);

		VoidElement *veHead, *veTail;
};

class ScopeElement {
	public:
		ScopeElement();
		~ScopeElement();

		char *lpszId;
		void *element;
		ScopeElement *next;
};

class Scope {
	public:  
		Scope();
		~Scope();

		void Add(ScopeElement *seNew);
		
		ScopeElement *seHead, *seTail;
};

/*
 * byte
 */

#ifndef byte
typedef unsigned char byte;
#endif

/*
 * Class pre-declaration
 */

class Part;

class DataType;
class Expression;
class Function;
class Program;

/*
 * Variable data structures
 */

typedef enum { VOID, INTEGER, REALNUM, BOOLEAN, ARRAY } TypeCode;

class DataType {
	public:
		~DataType();

		TypeCode type;
		bool operator==(const DataType &dt);
};

class ArrayType : public DataType {
	public:
		int GetElementSize(void);

		int length;
		DataType *dtElementType;
};

class Value {
	public:
		~Value();

		DataType *dt;
};

class IntValue : public Value {
	public:
		IntValue();

		int i;
};

class RealValue : public Value {
	public:
		RealValue();

		double r;
};

class BoolValue : public Value {
	public:
		BoolValue();

		bool b;
};

class ArrayValue : public Value {
	public:
		ArrayValue(ArrayType *dtArray);

		byte *value;
};

/*
 * Expression data structures
 */

typedef enum { 
	BOOL, INT, REAL, 			// Constant
	NOT, AND, OR, 							// Boolean
	ADD, SUB, MUL, DIV, MOD,			// Numeric
	EQ, NE, GT, GE, LT, LE,				// Compare
	VAR, 										// Variable read
	FUNC										// Function or operation
} ExprCode;

class Expression {
	public:
		~Expression();
		
		ExprCode ecCode;
		int position;
};

class ConstantExpr : public Expression {
	public:
		ConstantExpr(int i);
		ConstantExpr(double r);
		ConstantExpr(bool b);

		Value *vConst;
};

class NotExpr : public Expression {
	public:
		NotExpr();

		Expression *exprBool;
};

class BopExpr : public Expression {
	public:
		BopExpr(ExprCode ecOp);

		Expression *exprLeft, *exprRight;
};

class VarExpr : public Expression {
	public:
		VarExpr();

		char *lpszScope;
		char *lpszId;
		VoidList *vlExprIndexes;
};

class FuncExpr : public Expression {
	public:
		FuncExpr();

		char *lpszScope;
		char *lpszId;
		VoidList *vlExprParam;
};

/*
 * Statements data structures
 */

typedef enum { IF, WHILE, PROC, ASSIGN, BEGIN, RETURN, WAIT } StmtCode;

class Statement {
	public:
		~Statement();

		StmtCode scCode;
		int position;
};

class IfStmt : public Statement {
	public:
		IfStmt();

		Expression *exprCond;
		Statement *stmtThen;
		Statement *stmtElse;
};

class WhileStmt : public Statement {
	public:
		WhileStmt();

		Expression *exprCond;
		Statement *stmtBody;
};

class ProcStmt : public Statement {
	public:
		ProcStmt();

		char *lpszScope;
		char *lpszId;
		VoidList *vlExprParam;
};

class AssignStmt : public Statement {
	public:
		AssignStmt();

		Expression *exprValue;
		char *lpszScope;
		char *lpszId;
		VoidList *vlExprIndexes;
};

class BeginStmt : public Statement {
	public:
		BeginStmt();

		VoidList *vlStmt;
};

class ReturnStmt : public Statement {
	public:
		ReturnStmt();

		Expression *exprReturn;
};

class WaitStmt : public Statement {
	public:
		WaitStmt();

		Expression *exprCond;
};

/*
 * Function or procedure data structure
 */

class Function {
	public:
		Function();
		~Function();

		DataType *dtReturn;
		Scope *slDtParam;
		Scope *slDtLocal;
		Statement *stmtBody;
};

/*
 * Program or module data structure
 */

class Program {
	public:
		Program();
		~Program();

		char *lpszName;
		Scope *slPgmModule;
		Scope *slDtGlobal;
		Scope *slFunction;
		Statement *stmtBody;
};

/*
 * Parser class
 */

#define TOKEN_MAXLEN 128

typedef enum { 
			NoError,
			TokenTooLong,
			CannotOpenFile,
			ProgramOrModuleRequired,
			IdentifierRequired,
			SemicolonRequired,
			ColonRequired,
			UnexpectedToken,
			UnexpectedEOF,
			EOFExpected,
			TypeRequired,
			InvalidArraySize,
			IndexCloseRequired,
			CloseParenRequired,
			NotBeginOfStatement,
			ThenRequired,
			ParametersRequired,
			ToRequired,
			EndOfBlockRequired,
			WrongExpr,
			SourceNotOpened,
			NotAToken
		} ParsingErrorCode;

class ParsingError {
	public:
		ParsingErrorCode peCode;
		int position;
};

class Parser {
	public:
		Parser();
		~Parser();

		bool Open(char *lpszFileName);
		void Close();

		Program *ParseProgram(void);
		ParsingError &GetLastError(void);

	private:
		ScopeElement *ParseFunc(void);
		Scope *ParseVarDecl(void);
		DataType *ParseType(void);
		Statement *ParseStmt(void);
		Expression *ParseExpr(void);

		char *ParseProgramId(void);
	
		Expression *ParseOr(void);
		Expression *ParseAnd(void);
		Expression *ParseNot(void);
		Expression *ParseComparison(void);
		Expression *ParseAddSub(void);
		Expression *ParseMulDivMod(void);
		Expression *ParseLowestExpr(void);
		
		char *ParseId(void);
		bool FetchNextToken(void);
		bool FetchNumber(void);
		bool FetchSymbol(void);

		FILE *fpSource;
		char cNext;
		char szToken[TOKEN_MAXLEN];

		ParsingError peLastError;
};

#endif // ASURA_PARSER_H
