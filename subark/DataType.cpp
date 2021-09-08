////////////////////////////////////////////////////////////////////////////////
//
// "DataType.cpp"
//		Jacqueline���� ����ϴ� �������� ������ ����
//												�ۼ��� : asura
//												Last Update : 2000. 8. 20.
//
////////////////////////////////////////////////////////////////////////////////

/// Includes ///////////////////////////////////////////////////////////////////

#include <malloc.h>
#include <string.h>
#include "DataType.h"

/// Public macros & Constants //////////////////////////////////////////////////

/// Global variables ///////////////////////////////////////////////////////////

/// Local functinos ////////////////////////////////////////////////////////////

/// Implementations ////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// DataType::~DataType()
//		class DataType�� �Ҹ���
//												�ۼ��� : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

DataType::~DataType()
{
	switch (tcType) {
	case TC_ARRAY:
		delete ((ArrayType*)this)->lpdtElementType;	// �迭�� ���
		break;
	case TC_OBJECT:
		free(((ObjectType*)this)->lpszObject);		// Object Type�� ���
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// bool DataType::operator==(const DataType &dt)
//		�� ���������� ������ ��
//		IN:
//			dt - ���� ��������
//		RETURN:
//			�ڱ� �ڽŰ� ���� ���������� �� true, �ƴϸ� false
//												�ۼ��� : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

bool
DataType::operator==(const DataType &dt)
{
	if (this->tcType != dt.tcType) return false;	// Type�� �ٸ� ���
	if (this->tcType == TC_ARRAY && 
		((ArrayType*)this)->nLength != ((ArrayType*)&dt)->nLength ||
		!(((ArrayType*)this)->lpdtElementType != 
		((ArrayType*)&dt)->lpdtElementType))
		return false;								// �� �� �迭�� ���
	return true;
};

////////////////////////////////////////////////////////////////////////////////
//
// int ArrayType::GetElementSize(void)
//		�迭�� ������ ũ�⸦ ���Ѵ�
//		RETURN:
//			�迭�� ���� �ϳ��� ������ ũ��
//												�ۼ��� : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

int
ArrayType::GetElementSize(void)
{
	int temp;

	switch (lpdtElementType->tcType) {
	case TC_VOID:
		return 0;
	case TC_INT:				// ���Ұ� ����
		return sizeof(int);
	case TC_REAL:				// ���Ұ� �Ǽ�
		return sizeof(double);
	case TC_BOOL:				// ���Ұ� boolean
		return sizeof(bool);
	case TC_ARRAY:				// ���Ұ� �迭�� ���
		temp = ((ArrayType*)lpdtElementType)->GetElementSize();
		return temp*((ArrayType*)lpdtElementType)->nLength;
	case TC_OBJECT:
		return 4;
	}

	return -1;					// Warning�� ���ֱ� ���� �ڵ�
}

////////////////////////////////////////////////////////////////////////////////
//
// ArrayType *ArrayType::CopyType(void)
//		�迭 Ÿ���� �����Ͽ� �Ȱ��� Ÿ���� �����
//		RETURN:
//			����� Ÿ��
//												�ۼ��� : asura
//												Last Update : 2000. 8. 20.
//
////////////////////////////////////////////////////////////////////////////////

ArrayType *
ArrayType::CopyType(void)
{
	ArrayType *lpdtReturn;

	lpdtReturn = new ArrayType();
	lpdtReturn->nLength = nLength;

	switch (lpdtElementType->tcType) {
	case TC_VOID:
	case TC_INT:
	case TC_REAL:
	case TC_BOOL:
		lpdtReturn->lpdtElementType = new DataType();
		lpdtReturn->lpdtElementType->tcType = lpdtElementType->tcType;
		break;
	case TC_ARRAY:
		lpdtReturn->lpdtElementType = ((ArrayType*)lpdtElementType)->CopyType();
		break;
	case TC_OBJECT:
		lpdtReturn->lpdtElementType = 
			new ObjectType(((ObjectType*)lpdtElementType)->lpszObject);
	}

	return lpdtReturn;
}

////////////////////////////////////////////////////////////////////////////////
//
// ObjectType::ObjectType(char *lpszType)
//		ObjectType Ŭ������ ������
//		IN:
//			lpszType - Object�� �̸�
//												�ۼ��� : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

ObjectType::ObjectType(char *lpszType)
{
	if (lpszType) {
		lpszObject = (char*)malloc(sizeof(char)*(strlen(lpszType)+1));
		memcpy(lpszObject, lpszType, sizeof(char)*(strlen(lpszType)+1));
	}
};
