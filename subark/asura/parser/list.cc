#include <malloc.h>
#include "parser.h"

/*
 * List and Scope class
 */

VoidElement::VoidElement()
{
	next = NULL;
	element = NULL;
}

VoidList::VoidList()
{
	veHead = veTail = NULL;
}

VoidList::~VoidList()
{
	VoidElement *ve;

	for (ve = veHead; ve; ve = veHead) {
		veHead = veHead->next;
		delete ve;
	}
}

void
VoidList::Add(void *newElement)
{
	if (!veHead) {
		veHead = veTail = new VoidElement();
		veHead->element = newElement;
	} else {
		veTail->next = new VoidElement();
		veTail = veTail->next;
		veTail->element = newElement;
	}
}

ScopeElement::ScopeElement()
{
	lpszId = NULL;
	element = NULL;
	next = NULL;
}

ScopeElement::~ScopeElement()
{
	if (lpszId) free(lpszId);
}

Scope::Scope()
{
	seHead = seTail = NULL;
}

Scope::~Scope()
{
	ScopeElement *seTemp;

	while (seHead) {
		seTemp = seHead;
		seHead = seHead->next;
		delete seTemp;
	}
}

void
Scope::Add(ScopeElement *seNew)
{
	seNew->next = seHead;
	seHead = seNew;
}


