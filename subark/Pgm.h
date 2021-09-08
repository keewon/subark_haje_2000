/*
 * Program or module data structure
 */

#ifndef _Program_
#define _Program_

#include "Types.h"
#include "Stmt.h"

class Program {
	public:
		Program();
		~Program();

		char *lpszName;
		Scope *lpslPgmModule;
		Scope *lpslDtGlobal;
		Scope *lpslFunction;
		Statement *stmtBody;
};

#endif