#include "parser.h"

/*
 * DataType class
 */

DataType::~DataType()
{
	if (this->type == ARRAY)
		delete ((ArrayType*)this)->dtElementType;
}

bool
DataType::operator==(const DataType &dt)
{
	if (this->type != dt.type || (this->type == ARRAY && (
		((ArrayType*)this)->length != ((ArrayType*)&dt)->length ||
		!(((ArrayType*)this)->dtElementType == ((ArrayType*)&dt)->dtElementType)
		)))
		return false;
	else return true;
};

int
ArrayType::GetElementSize(void)
{
	int temp;

	switch (dtElementType->type) {
	case VOID:
		return 0;
	case INTEGER:
		return sizeof(int);
	case REALNUM:
		return sizeof(double);
	case BOOLEAN:
		return sizeof(bool);
	case ARRAY:
		temp = ((ArrayType*)dtElementType)->GetElementSize();
		return temp*((ArrayType*)dtElementType)->length;
	}

	return -1;
}
