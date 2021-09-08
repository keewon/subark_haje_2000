#include <malloc.h>
#include "parser.h"

/*
 * Value classes
 */

Value::~Value()
{
	if (dt->type == ARRAY)
		free(((ArrayValue*)this)->value);
	delete dt;
}

IntValue::IntValue()
{
	dt = new DataType();
	dt->type = INTEGER;
}

RealValue::RealValue()
{
	dt = new DataType();
	dt->type = REALNUM;
}

BoolValue::BoolValue()
{
	dt = new DataType();
	dt->type = BOOLEAN;
}

ArrayValue::ArrayValue(ArrayType *dtArray)
{
	dt = dtArray;
	value = (byte *)malloc(dtArray->length * dtArray->GetElementSize());
}
