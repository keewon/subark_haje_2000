#include "Func.h"

/*
 * Function class
 */

Function::Function()
{
	lpdtReturn = NULL;
	lpslDtParam = lpslDtLocal = NULL;
	stmtBody = NULL;
}

Function::~Function()
{
	ScopeElement *i;
	if (lpdtReturn) delete lpdtReturn;
	if (lpslDtParam) {
		for (i = lpslDtParam->lpseHead; i; i = i->lpseNext)
			delete ((DataType*)i->lpElement);
		delete lpslDtParam;
	}
	if (lpslDtLocal) {
		for (i = lpslDtLocal->lpseHead; i; i = i->lpseNext)
			delete ((DataType*)i->lpElement);
		delete lpslDtLocal;
	}
	if (stmtBody) delete stmtBody;
}
