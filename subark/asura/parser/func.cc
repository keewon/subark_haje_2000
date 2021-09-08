#include "parser.h"

/*
 * Function class
 */

Function::Function()
{
	dtReturn = NULL;
	slDtParam = slDtLocal = NULL;
	stmtBody = NULL;
}

Function::~Function()
{
	ScopeElement *i;
	if (dtReturn) delete dtReturn;
	if (slDtParam) {
		for (i = slDtParam->seHead; i; i = i->next)
			delete ((DataType*)i->element);
		delete slDtParam;
	}
	if (slDtLocal) {
		for (i = slDtLocal->seHead; i; i = i->next)
			delete ((DataType*)i->element);
		delete slDtLocal;
	}
	if (stmtBody) delete stmtBody;
}
