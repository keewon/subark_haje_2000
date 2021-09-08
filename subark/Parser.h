////////////////////////////////////////////////////////////////////////////////
//
// "Parser.h"
//		Parser 클래스 선언
//												작성자 : asura
//												Last Update : 2000. 7. 27.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _PARSER_H_ASURA_BECD_
#define _PARSER_H_ASURA_BECD_

#include <stdio.h>

#include "Types.h"
#include "DataType.h"
#include "Value.h"
#include "Part.h"
#include "Expr.h"
#include "Stmt.h"
#include "Func.h"
#include "Pgm.h"

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

		FILE *lpfSource;
		char cNext;
		char szToken[TOKEN_MAXLEN];

		ParsingError peLastError;
};

#endif // _PARSER_H_ASURA_BECD_
