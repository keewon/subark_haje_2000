#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "Parser.h"

/*
 * Some helpful functions
 */

bool isName(char *lpszToken);
bool isReal(char *lpszToken);
bool isNumber(char *lpszToken);
double ator(char *lpszReal);

/*
 * Parser class
 */

Parser::Parser()
{
	lpfSource = NULL;
}

Parser::~Parser()
{
	Close();
}

bool
Parser::Open(char *lpszFileName)
{
	if (!(lpfSource = fopen(lpszFileName, "r"))) {
		peLastError.peCode = CannotOpenFile;
		return false;
	}
	cNext = '\0';
	szToken[0] = '\0';

	return true;
}

void
Parser::Close()
{
	if (lpfSource) {
		fclose(lpfSource);
		lpfSource = NULL;
	}
}

Program *
Parser::ParseProgram(void)
{
	bool isProgram;
	Program *pgm;

	peLastError.peCode = NoError;
	peLastError.position = 0;
	if (!lpfSource || fseek(lpfSource, 0, SEEK_SET)==-1) {
		peLastError.peCode = CannotOpenFile;
		return NULL;
	}

	/* program <name>;
		module <name>; */
	if (!FetchNextToken()) return NULL;
	if (!strcmp(szToken, "program")) isProgram = true;
	else if (!strcmp(szToken, "module")) isProgram = false;
	else {
		peLastError.peCode = ProgramOrModuleRequired;
		return NULL;
	}
	pgm = new Program();
	if (!(pgm->lpszName = ParseProgramId())) {
		delete pgm;
		return NULL;
	}
	if (!FetchNextToken()) { delete pgm; return NULL; }

	/* uses <name>{, <name>}; */
	if (!strcmp(szToken, "uses")) {
		do {
			ScopeElement *t = new ScopeElement();
			if (!(t->lpszId = ParseId())) {
				delete t; delete pgm;
				return NULL;
			}
			pgm->lpslPgmModule->Add(t);
			if (!FetchNextToken()) { delete pgm; return NULL; }
		} while (szToken[0]==',');
		if (szToken[0]!=';') {
			peLastError.peCode = SemicolonRequired;
			delete pgm;
			return NULL;
		}
		if (!FetchNextToken()) { delete pgm; return NULL; }
	}

	/* var {<name>:<type>;} */
	if (!strcmp(szToken, "var")) {
		if (!(pgm->lpslDtGlobal = ParseVarDecl())) {
			delete pgm; return NULL;
		}
	}
	else pgm->lpslDtGlobal = new Scope();

	/* { (<func-decl>|<proc-decl>) } */
	while (!strcmp(szToken, "function") || !strcmp(szToken, "procedure")) {
		ScopeElement *t = ParseFunc();
		if (!t) {
			delete pgm; return NULL;
		}
		pgm->lpslFunction->Add(t);
		if (!isProgram && szToken[0]=='!') break;
		if (szToken[0]!=';' && (isProgram || szToken[0]!='!')) {
			peLastError.peCode = SemicolonRequired;
			delete pgm; return NULL;
		}
		if (!FetchNextToken()) { delete pgm; return NULL; }
	}

	if (!isProgram && szToken[0]=='!') return pgm;
	
	/* <stmt>. */
	if (!(pgm->stmtBody = ParseStmt())) {
		delete pgm; return NULL;
	}
	if (szToken[0]!='!') {
		peLastError.peCode = EOFExpected;
		delete pgm; return NULL;
	}

	return pgm;
}

ParsingError &
Parser::GetLastError(void)
{
	return peLastError;
}

ScopeElement *
Parser::ParseFunc(void)
{
	bool isProc;
	Function *funcF;
	ScopeElement *lpseFunc;

	/* (function | procedure) <name> */
	isProc = strcmp(szToken, "function");
	lpseFunc = new ScopeElement();
	if (!(lpseFunc->lpszId = ParseId())) { delete lpseFunc; return NULL; }
	if (!FetchNextToken() || szToken[0]!='(') {
		delete lpseFunc; return NULL; 
	}
	else lpseFunc->lpElement = funcF = new Function();

	/* '(' { <name>:<type> } ')' */
	if (!(funcF->lpslDtParam = ParseVarDecl())) {
		delete lpseFunc; delete funcF; return NULL;
	}
	if (szToken[0]!=')') {
		peLastError.peCode = CloseParenRequired;
		delete lpseFunc; delete funcF; return NULL;
	}

	/* : <type> ; */
	if (!FetchNextToken()) { delete lpseFunc; delete funcF; return NULL; }
	if (!isProc) { 
		if (szToken[0]!=':') {
			peLastError.peCode = ColonRequired;
			delete lpseFunc; delete funcF; return NULL;
		}
		if (!(funcF->lpdtReturn = ParseType())) {
			delete lpseFunc; delete funcF; return NULL;
		}
	} else {
		funcF->lpdtReturn = new DataType();
		funcF->lpdtReturn->tcType = TC_VOID;
	}
	if (szToken[0]!=';') {
		peLastError.peCode = SemicolonRequired;
		delete lpseFunc; delete funcF; return NULL;
	}

	/* <var-decl> */
	if (!FetchNextToken()) { delete lpseFunc; delete funcF; return NULL; }
	if (!strcmp(szToken, "var"))
		if (!(funcF->lpslDtLocal = ParseVarDecl())) {
			delete lpseFunc; delete funcF; return NULL;
		}
	
	/* <stmt>; */
	if (!(funcF->stmtBody = ParseStmt())) {
		delete lpseFunc; delete funcF; return NULL;
	}

	return lpseFunc;
}

Scope *
Parser::ParseVarDecl(void)
{
	Scope *lpsTemp;
	ScopeElement *i;

#define DeleteTemp \
	for (i = lpsTemp->lpseHead; i; i = i->lpseNext) \
		delete ((DataType*)i->lpElement); \
	delete lpsTemp

	if (!FetchNextToken()) { return NULL; }
	lpsTemp = new Scope();

	while (isName(szToken)) {
		ScopeElement *lpseTemp = new ScopeElement();
		lpseTemp->lpszId = (char *)malloc(sizeof(char)*(strlen(szToken)+1));
		memcpy(lpseTemp->lpszId, szToken, sizeof(char)*(strlen(szToken)+1));

		if (!FetchNextToken()) { 
			delete lpseTemp; DeleteTemp; return NULL; 
		}
		
		if (szToken[0]!=':') {
			peLastError.peCode = ColonRequired;
			delete lpseTemp; DeleteTemp;
			return NULL;
		}
		if (!(lpseTemp->lpElement = (void *)ParseType())) {
			delete lpseTemp; DeleteTemp; return NULL;
		}
		lpsTemp->Add(lpseTemp);
		if (szToken[0]!=';')	break;
		if (!FetchNextToken()) { DeleteTemp; return NULL; }
	}
#undef DeleteTemp

	return lpsTemp;
}

DataType *
Parser::ParseType(void)
{
	DataType *t1;
	ArrayType *t2;

	if (!FetchNextToken()) return NULL;
	/* <type> = int | real | bool | */
	if (!strcmp(szToken, "int")) { 
		t1 = new DataType();
		t1->tcType = TC_INT;
	}
	else if (!strcmp(szToken, "real")) { 
		t1 = new DataType();
		t1->tcType = TC_REAL;
	}
	else if (!strcmp(szToken, "bool")) { 
		t1 = new DataType();
		t1->tcType = TC_BOOL;
	}
	else { 
		t1 = new ObjectType(szToken);
		t1->tcType = TC_OBJECT;
	}

	/* <type> = ...| <type>'['<digit>{<digit>}']' */
	if (!FetchNextToken()) { delete t1; return NULL; }
	while (szToken[0]=='[') {
		if (!FetchNextToken()) { delete t1; return NULL; }
		if (!isNumber(szToken) || isReal(szToken)) {
			peLastError.peCode = InvalidArraySize;
			return NULL;
		}
		t2 = new ArrayType();
		t2->nLength = atoi(szToken);
		t2->lpdtElementType = t1;
		t1 = t2;
		if (!FetchNextToken()) { delete t1; return NULL; }
		if (szToken[0]!=']') {
			peLastError.peCode = IndexCloseRequired;
			delete t1; return NULL;
		}
		if (!FetchNextToken()) { delete t1; return NULL; }
	}

	return t1;
}

Statement *
Parser::ParseStmt()
{
	if (!strcmp(szToken, "if")) {
		/* if <expr> then <stmt> [else <stmt>] */
		IfStmt *stmtS = new IfStmt();
		stmtS->nPosition = peLastError.position;
		if (!(stmtS->exprCond = ParseExpr())) { delete stmtS; return NULL; }
		if (strcmp(szToken, "then")) {
			peLastError.peCode = ThenRequired;
			delete stmtS; return NULL;
		}
		if (!FetchNextToken()) { delete stmtS; return NULL; }
		if (!(stmtS->stmtThen = ParseStmt())) { delete stmtS; return NULL; }
		if (!strcmp(szToken, "else"))
			if (!FetchNextToken() || !(stmtS->stmtElse = ParseStmt())) {
				delete stmtS; return NULL;
			}
		return stmtS;
	} else if (!strcmp(szToken, "while")) {
		/* while <expr> do <stmt> */
		WhileStmt *stmtS = new WhileStmt();
		stmtS->nPosition = peLastError.position;
		if (!(stmtS->exprCond = ParseExpr())) { delete stmtS; return NULL; }
		if (strcmp(szToken, "do")) {
			peLastError.peCode = ThenRequired;
			delete stmtS; return NULL;
		}
		if (!FetchNextToken()) { delete stmtS; return NULL; }
		if (!(stmtS->stmtBody = ParseStmt())) { delete stmtS; return NULL; }
		return stmtS;
	} else if (!strcmp(szToken, "call")) {
		/* call [<name>.]name with '(' <param-list> ')' */
		ProcStmt *stmtS = new ProcStmt();
		Expression *exprParam;
		stmtS->nPosition = peLastError.position;
		if (!(stmtS->lpszId = ParseId())) { delete stmtS; return NULL; }
		if (!FetchNextToken()) { delete stmtS; return NULL; }
		if (szToken[0]=='.') {
			stmtS->lpszScope = stmtS->lpszId;
			if (!(stmtS->lpszId = ParseId())) { delete stmtS; return NULL; }
			if (!FetchNextToken()) { delete stmtS; return NULL; }
		}
		if (!strcmp(szToken, "with")) { delete stmtS; return NULL; }
		if (!FetchNextToken()) { delete stmtS; return NULL; }
		if (szToken[0]!='(') {
			peLastError.peCode = ParametersRequired;
			delete stmtS; return NULL;
		}
		if ((exprParam = ParseExpr())) {
			stmtS->lpvlExprParam->Add(exprParam);
			while (szToken[0]==',') {
				if (!(exprParam = ParseExpr())) { delete stmtS; return NULL; }
				stmtS->lpvlExprParam->Add((void *)exprParam);
			}
		}
		if (szToken[0]!=')') {
			peLastError.peCode = CloseParenRequired;
			delete stmtS; return NULL;
		}
		if (!FetchNextToken()) { delete stmtS; return NULL; }
		return stmtS;
	} else if (!strcmp(szToken, "assign")) {
		/* assign <expr> to name{[<expr>]} */
		AssignStmt *stmtS = new AssignStmt();
		Expression *exprIndex;
		stmtS->nPosition = peLastError.position;
		if (!(stmtS->exprValue = ParseExpr())) { delete stmtS; return NULL; }
		if (strcmp(szToken, "to")) {
			peLastError.peCode = ToRequired;
			delete stmtS; return NULL;
		}
		if (!(stmtS->lpszId = ParseId())) { delete stmtS; return NULL; }
		if (!FetchNextToken()) { delete stmtS; return NULL; }
		while (szToken[0]=='[') {
			if (!(exprIndex = ParseExpr())) { delete stmtS; return NULL; }
			if (szToken[0]!=']') {
				peLastError.peCode = IndexCloseRequired;
				delete stmtS; return NULL;
			}
			stmtS->lpvlExprIndexes->Add((void *)exprIndex);
			if (!FetchNextToken()) { delete stmtS; return NULL; }
		}
		return stmtS;
	} else if (!strcmp(szToken, "begin")) {
		/* begin <stmt-list> end */
		BeginStmt *stmtS = new BeginStmt();
		Statement *stmt;
		stmtS->nPosition = peLastError.position;
		do {
			if (!FetchNextToken()) { delete stmtS; return NULL; }
			if (!(stmt = ParseStmt())) { delete stmtS; return NULL; }
			stmtS->lpvlStmt->Add((void *)stmt);
		} while (szToken[0]==';');
		if (strcmp(szToken, "end")) {
			peLastError.peCode = EndOfBlockRequired;
			delete stmtS; return NULL;
		}
		if (!FetchNextToken()) { delete stmtS; return NULL; }
		return stmtS;
	} else if (!strcmp(szToken, "return")) {
		ReturnStmt *stmtS = new ReturnStmt();
		/* return <expr> */
		stmtS->nPosition = peLastError.position;
		if (!(stmtS->exprReturn = ParseExpr())) { delete stmtS; return NULL; }
		return stmtS;
	} else if (!strcmp(szToken, "wait")) {
		/* wait <expr> */
		WaitStmt *stmtS = new WaitStmt();
		stmtS->nPosition = peLastError.position;
		if (!(stmtS->exprCond = ParseExpr())) { delete stmtS; return NULL; }
		return stmtS;
	} else {
		peLastError.peCode = NotBeginOfStatement;
		return NULL;
	}
}

Expression *
Parser::ParseExpr(void)
{
	return ParseOr();
}

Expression *
Parser::ParseOr(void)
{
	/* <expr> { or <expr> } */
	Expression *exprLeft;
	BopExpr *exprRet;

	if (!(exprLeft = ParseAnd())) return NULL;
	while (!strcmp(szToken, "or")) {
		exprRet = new BopExpr(EC_OR);
		exprRet->exprLeft = exprLeft;
		exprRet->nPosition = exprLeft->nPosition;
		if (!(exprRet->exprRight = ParseAnd())) { delete exprRet; return NULL; }
		exprLeft = exprRet;
	}

	return exprLeft;
}

Expression *
Parser::ParseAnd(void)
{
	/* <expr> { and <expr> } */
	Expression *exprLeft;
	BopExpr *exprRet;

	if (!(exprLeft = ParseNot())) return NULL;
	while (!strcmp(szToken, "and")) {
		exprRet = new BopExpr(EC_AND);
		exprRet->exprLeft = exprLeft;
		exprRet->nPosition = exprLeft->nPosition;
		if (!(exprRet->exprRight = ParseNot())) { delete exprRet; return NULL; }
		exprLeft = exprRet;
	}

	return exprLeft;
}

Expression *
Parser::ParseNot(void)
{
	/* not <expr> | <expr> */
	NotExpr *expr;

	if (!FetchNextToken()) return NULL;
	if (!strcmp(szToken, "not")) {
		expr = new NotExpr();
		expr->nPosition = peLastError.position;
		if (!(expr->exprBool = ParseNot())) { delete expr; return NULL; }
	} else return ParseComparison();

	return expr;
}

Expression *
Parser::ParseComparison(void)
{
	/* <expr> ( = | <> | > | >= | < | <= ) <expr> */
	Expression *exprLeft;
	BopExpr *exprRet;

	if (!(exprLeft = ParseAddSub())) return NULL;

	if (!strcmp(szToken, "=")) {
		exprRet = new BopExpr(EC_EQ);
		exprRet->nPosition = exprLeft->nPosition;
		exprRet->exprLeft = exprLeft;
		if (!FetchNextToken()) { delete exprRet; return NULL; }
		if (!(exprRet->exprRight = ParseAddSub())) {
			delete exprRet; return NULL;
		}
	} else if (!strcmp(szToken, "<>")) {
		exprRet = new BopExpr(EC_OR);
		exprRet->nPosition = exprLeft->nPosition;
		exprRet->exprLeft = exprLeft;
		if (!FetchNextToken()) { delete exprRet; return NULL; }
		if (!(exprRet->exprRight = ParseAddSub())) {
			delete exprRet; return NULL;
		}
	} else if (!strcmp(szToken, ">")) {
		exprRet = new BopExpr(EC_GT);
		exprRet->nPosition = exprLeft->nPosition;
		exprRet->exprLeft = exprLeft;
		if (!FetchNextToken()) { delete exprRet; return NULL; }
		if (!(exprRet->exprRight = ParseAddSub())) {
			delete exprRet; return NULL;
		exprRet->nPosition = exprLeft->nPosition;
		}
	} else if (!strcmp(szToken, ">=")) {
		exprRet = new BopExpr(EC_GE);
		exprRet->nPosition = exprLeft->nPosition;
		exprRet->exprLeft = exprLeft;
		if (!FetchNextToken()) { delete exprRet; return NULL; }
		if (!(exprRet->exprRight = ParseAddSub())) {
			delete exprRet; return NULL;
		}
	} else if (!strcmp(szToken, "<")) {
		exprRet = new BopExpr(EC_LT);
		exprRet->nPosition = exprLeft->nPosition;
		exprRet->exprLeft = exprLeft;
		if (!FetchNextToken()) { delete exprRet; return NULL; }
		if (!(exprRet->exprRight = ParseAddSub())) {
			delete exprRet; return NULL;
		}
	} else if (!strcmp(szToken, "<=")) {
		exprRet = new BopExpr(EC_LE);
		exprRet->nPosition = exprLeft->nPosition;
		exprRet->exprLeft = exprLeft;
		if (!FetchNextToken()) { delete exprRet; return NULL; }
		if (!(exprRet->exprRight = ParseAddSub())) {
			delete exprRet; return NULL;
		}
	} else return exprLeft;

	return exprRet;
}

Expression *
Parser::ParseAddSub(void)
{
	/* <expr> { ( - | + ) <expr> } */
	Expression *exprLeft;
	BopExpr *exprRet;

	if (!(exprLeft = ParseMulDivMod())) return NULL;
	while (szToken[0]=='-' || szToken[0]=='+') {
		if (szToken[0]=='-') exprRet = new BopExpr(EC_SUB);
		else exprRet = new BopExpr(EC_ADD);
		exprRet->nPosition = exprLeft->nPosition;
		exprRet->exprLeft = exprLeft;
		if (!FetchNextToken()) { delete exprRet; return NULL; }
		if (!(exprRet->exprRight = ParseMulDivMod())) {
			delete exprRet; return NULL;
		}
		exprLeft = exprRet;
	}

	return exprLeft;
}

Expression *
Parser::ParseMulDivMod(void)
{
	/* <expr> { ( * | / | % ) <expr> } */
	Expression *exprLeft;
	BopExpr *exprRet;

	if (!(exprLeft = ParseLowestExpr())) return NULL;
	while (szToken[0]=='*' || szToken[0]=='/' || szToken[0]=='%') {
		if (szToken[0]=='*') exprRet = new BopExpr(EC_MUL);
		else if (szToken[0]=='/') exprRet = new BopExpr(EC_DIV);
		else exprRet = new BopExpr(EC_MOD);
		exprRet->nPosition = exprLeft->nPosition;
		exprRet->exprLeft = exprLeft;
		if (!FetchNextToken()) { delete exprRet; return NULL; }
		exprRet->nPosition = exprLeft->nPosition;
		if (!(exprRet->exprRight = ParseLowestExpr())) {
			delete exprRet; return NULL;
		}
		exprLeft = exprRet;
	}

	return exprLeft;
}

Expression *
Parser::ParseLowestExpr(void)
{
	if (szToken[0]=='(') {
		/* '(' <expr> ')' */
		Expression *expr;
		if (!(expr = ParseOr())) return NULL;
		if (szToken[0]!=')') {
			peLastError.peCode = CloseParenRequired;
			return NULL;
		}
		if (!FetchNextToken()) { delete expr; return NULL; }
		return expr;
	} else if (szToken[0]=='-') {
		/* -<number> */
		ConstantExpr *expr;
		int nPosition;
		nPosition = peLastError.position;
		if (!FetchNextToken() || !isNumber(szToken)) return NULL;
		if (isReal(szToken)) expr = new ConstantExpr(ator(szToken));
		else expr = new ConstantExpr(-atoi(szToken));
		expr->nPosition = nPosition;
		if (!FetchNextToken()) { delete expr; return NULL; }
		else return expr;
	} else if (!strcmp(szToken, "call")) {
		/* call [<name>.]<name> with '(' <param-list> ')' */
		FuncExpr *exprF = new FuncExpr();
		Expression *exprParam;
		exprF->nPosition = peLastError.position;
		if (!(exprF->lpszId = ParseId())) { delete exprF; return NULL; }
		if (!FetchNextToken()) { delete exprF; return NULL; }
		if (szToken[0]=='.') {
			exprF->lpszScope = exprF->lpszId;
			if (!(exprF->lpszId = ParseId())) { delete exprF; return NULL; }
			if (!FetchNextToken()) { delete exprF; return NULL; }
		}
		if (strcmp(szToken, "with")) { delete exprF; return NULL; }
		if (!FetchNextToken()) { delete exprF; return NULL; }
		if (szToken[0]!='(') {
			peLastError.peCode = ParametersRequired;
			delete exprF; return NULL;
		}
		if ((exprParam = ParseExpr())) {
			exprF->lpvlExprParam->Add(exprParam);
			while (szToken[0]==',') {
				if (!(exprParam = ParseExpr())) { delete exprF; return NULL; }
				exprF->lpvlExprParam->Add((void *)exprParam);
			}
		}
		if (szToken[0]!=')') {
			peLastError.peCode = CloseParenRequired;
			delete exprF; return NULL;
		}
		if (!FetchNextToken()) { delete exprF; return NULL; }
		return exprF;
	} else if (isName(szToken)) {
		/* <name> */
		VarExpr *exprV = new VarExpr();
		Expression *exprIndex;
		exprV->nPosition = peLastError.position;
		exprV->lpszId = (char *)malloc(sizeof(char)*(strlen(szToken)+1));
		memcpy(exprV->lpszId, szToken, sizeof(char)*(strlen(szToken)+1));
		if (!FetchNextToken()) { delete exprV; return NULL; }
		if (szToken[0]=='.') {
			exprV->lpszScope = exprV->lpszId;
			if (!(exprV->lpszId = ParseId())) { delete exprV; return NULL; }
			if (!FetchNextToken()) { delete exprV; return NULL; }
		}
		while (szToken[0]=='[') {
			if (!(exprIndex = ParseExpr())) { delete exprV; return NULL; }
			if (szToken[0]!=']') {
				peLastError.peCode = IndexCloseRequired;
				delete exprV; return NULL;
			}
			exprV->lpvlExprIndexes->Add((void *)exprIndex);
			if (!FetchNextToken()) { delete exprV; return NULL; }
		}
	  	return exprV;
	} else if (isNumber(szToken)) {
		/* <int> | <real> */
		ConstantExpr *expr;
		if (isReal(szToken)) expr = new ConstantExpr(ator(szToken));
		else expr = new ConstantExpr(atoi(szToken));
		expr->nPosition = peLastError.position;
		if (!FetchNextToken()) { delete expr; return NULL; }
		else return expr;
	} else {
		peLastError.peCode = WrongExpr;
		return NULL;
	}
}

char *
Parser::ParseProgramId(void)
{
	char *lpszId;
	if (!(lpszId = ParseId()))
		return NULL;
	if (!FetchNextToken()) {
		free(lpszId);
		return NULL;
	}

	if (szToken[0] != ';') {
		peLastError.peCode = SemicolonRequired;
		free(lpszId);
		return NULL;
	}

	return lpszId;
}

char *
Parser::ParseId(void)
{
	char *lpszId;
	if (!FetchNextToken()) return NULL;
	if (!isName(szToken)) {
		peLastError.peCode = IdentifierRequired;
		return NULL;
	}
	lpszId = (char *)malloc(sizeof(char)*(strlen(szToken)+1));
	memcpy(lpszId, szToken, sizeof(char)*(strlen(szToken)+1));
	return lpszId;
}

bool 
Parser::FetchNextToken(void)
{
	int i;

	while (cNext=='\0' || isspace(cNext)) {
		if (cNext=='\n') peLastError.position++;
		if (!lpfSource) { 
			peLastError.peCode = SourceNotOpened;
			return false;
		}
		if ((cNext = fgetc(lpfSource)) == EOF) {
			cNext = '\0';
			peLastError.peCode = UnexpectedEOF;
			return false;
		}
	}

	if (cNext>='0' && cNext<='9') return FetchNumber();
	if (cNext>='a' && cNext<='z') return FetchSymbol();
	if (cNext>='A' && cNext<='Z') return FetchSymbol();

	switch (cNext) {
	case '(' : case ')' : case '[' : case ']' : case ':' : case ',' : case ';' :
	case '+' : case '-' : case '/' : case '*' : case '%' : case '=' : case '!' :
		szToken[0] = cNext; szToken[1] = '\0'; cNext = '\0';
		return true;
	case '.' :
		if ((cNext = fgetc(lpfSource)) == EOF) cNext = '\0';
		if (cNext<'0' || cNext>'9') {
			szToken[0] = '.'; szToken[1] = '\0'; cNext = '\0';
			return true;
		}
		if (!FetchNumber()) return false;
		i = strlen(szToken);
		if (i > TOKEN_MAXLEN) { 
			peLastError.peCode = TokenTooLong;
			return false;
		}
		for (i = strlen(szToken); i >= 0; i++) szToken[i+1] = szToken[i];
		szToken[0] = '.';
		return true;
	case '<' :
		if ((cNext = fgetc(lpfSource)) == EOF) cNext = '\0';
		if (cNext == '=') {
			szToken[0] = '<'; szToken[1] = '='; szToken[2] = '\0';
		} else if (cNext == '>') {
			szToken[0] = '<'; szToken[1] = '>'; szToken[2] = '\0'; cNext = '\0';
		} else { szToken[0] = '<'; szToken[1] = '\0'; }
		return true;
	case '>' :
		if ((cNext = fgetc(lpfSource)) == EOF) cNext = '\0';
		if (cNext == '=') {
			szToken[0] = '>'; szToken[1] = '='; szToken[2] = '\0'; cNext = '\0'; 
		} else { szToken[0] = '>'; szToken[1] = '\0'; }
		return true;
	default:
		peLastError.peCode = NotAToken;
		return false;
	}	
}

bool
Parser::FetchNumber(void)
{
	int i;

	i = 0;
	while (cNext=='.' || (cNext<='9' && cNext>='0')) {
		if (i > TOKEN_MAXLEN) {
			peLastError.peCode = TokenTooLong;
			return false;
		}
		szToken[i++] = cNext;
		if ((cNext = fgetc(lpfSource)) == EOF) cNext = '\0';
	}
	szToken[i] = '\0';

	return true;
}

bool
Parser::FetchSymbol(void)
{
	int i;

	i = 0;
	while ((cNext<='9' && cNext>='0') ||
			(cNext<='z' && cNext>='a') || (cNext<='Z' && cNext>='A')) {
		if (i > TOKEN_MAXLEN) {
			peLastError.peCode = TokenTooLong;
			return false;
		}
		szToken[i++] = cNext;
		if ((cNext = fgetc(lpfSource)) == EOF) cNext = '\0';
	}
	szToken[i] = '\0';

	return true;
}

bool isName(char *lpszToken)
{
	int i;

	if (lpszToken[0]<'A' || (lpszToken[0]>'Z' && lpszToken[0]<'A') ||
		lpszToken[0]>'z')
		return false;

	for (i = 0; lpszToken[i]; i++) {
		if (lpszToken[i]>='A' && lpszToken[i]<='Z') continue;
		if (lpszToken[i]>='a' && lpszToken[i]<='z') continue;
		if (lpszToken[i]>='0' && lpszToken[i]<='9') continue;
	}
	
	if (!strcmp(lpszToken, "program") ||
		!strcmp(lpszToken, "module") ||
		!strcmp(lpszToken, "var") ||
		!strcmp(lpszToken, "uses") ||
		!strcmp(lpszToken, "function") ||
		!strcmp(lpszToken, "procedure") ||
		!strcmp(lpszToken, "begin") ||
		!strcmp(lpszToken, "end") ||
		!strcmp(lpszToken, "if") ||
		!strcmp(lpszToken, "then") ||
		!strcmp(lpszToken, "else") ||
		!strcmp(lpszToken, "while") ||
		!strcmp(lpszToken, "do") ||
		!strcmp(lpszToken, "call") ||
		!strcmp(lpszToken, "with") ||
		!strcmp(lpszToken, "assign") ||
		!strcmp(lpszToken, "to") ||
		!strcmp(lpszToken, "true") ||
		!strcmp(lpszToken, "false") ||
		!strcmp(lpszToken, "not") ||
		!strcmp(lpszToken, "and") ||
		!strcmp(lpszToken, "or") ||
		!strcmp(lpszToken, "int") ||
		!strcmp(lpszToken, "real") ||
		!strcmp(lpszToken, "bool"))
		return false;
	
	return true;
}

bool isReal(char *lpszToken)
{
	int i;

	for (i=0; lpszToken[i]; i++)
		if (lpszToken[i]=='.') return true;
	
	return false;
}

bool isNumber(char *lpszToken)
{
	bool dot;
	int i;

	for (i = 0; lpszToken[i]; i++)
		if (lpszToken[i]=='.') {
			if (dot) return false;
			else dot = true;
		} else if (lpszToken[i]<'0' || lpszToken[i]>'9') return false;

	return true;
}

double ator(char *lpszReal)
{
	double r;

	sscanf(lpszReal, "%f", &r);
	
	return r;
}
