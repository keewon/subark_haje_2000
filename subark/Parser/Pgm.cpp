#include <malloc.h>
#include "Parser.h"

/*
 * Program class
 */

Program::Program()
{
	lpszName = NULL;
	lpslPgmModule = new Scope();
	lpslDtGlobal = NULL;
	lpslFunction = new Scope();
	stmtBody = NULL;
}

Program::~Program()
{
	ScopeElement *i;

	if (lpszName) free(lpszName);
	if (lpslPgmModule) delete lpslPgmModule;
	if (lpslDtGlobal) {
		for (i = lpslDtGlobal->lpseHead; i; i = i->lpseNext)
			delete (DataType*)i->lpElement;
		delete lpslDtGlobal;
	}
	if (lpslFunction) {
		for (i = lpslFunction->lpseHead; i; i = i->lpseNext)
			delete (Function*)i->lpElement;
		delete lpslFunction;
	}
	if (stmtBody) delete stmtBody;
}
