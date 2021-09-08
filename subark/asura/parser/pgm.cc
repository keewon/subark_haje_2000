#include <malloc.h>
#include "parser.h"

/*
 * Program class
 */

Program::Program()
{
	lpszName = NULL;
	slPgmModule = new Scope();
	slDtGlobal = NULL;
	slFunction = new Scope();
	stmtBody = NULL;
}

Program::~Program()
{
	ScopeElement *i;

	if (lpszName) free(lpszName);
	if (slPgmModule) delete slPgmModule;
	if (slDtGlobal) {
		for (i = slDtGlobal->seHead; i; i = i->next)
			delete (DataType*)i->element;
		delete slDtGlobal;
	}
	if (slFunction) {
		for (i = slFunction->seHead; i; i = i->next)
			delete (Function*)i->element;
		delete slFunction;
	}
	if (stmtBody) delete stmtBody;
}
