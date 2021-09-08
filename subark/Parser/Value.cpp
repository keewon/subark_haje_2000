#include <malloc.h>
#include "Parser.h"

/*
 * Value classes
 */

Value::~Value()
{
	if (lpdt->tcType == TC_ARRAY)
		free(((ArrayValue*)this)->value);
	delete lpdt;
}

IntValue::IntValue()
{
	lpdt = new DataType();
	lpdt->tcType = TC_INT;
}

RealValue::RealValue()
{
	lpdt = new DataType();
	lpdt->tcType = TC_REAL;
}

BoolValue::BoolValue()
{
	lpdt = new DataType();
	lpdt->tcType = TC_BOOL;
}

ArrayValue::ArrayValue(ArrayType *lpdtArray)
{
	lpdt = lpdtArray;
	value = (byte *)malloc(lpdtArray->nLength * lpdtArray->GetElementSize());
}

ObjectValue::ObjectValue(char *lpszPartType, Part *part)
{
	lpdt = new ObjectType(lpszPartType);

	partObject = part;
}
