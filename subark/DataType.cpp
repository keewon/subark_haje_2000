////////////////////////////////////////////////////////////////////////////////
//
// "DataType.cpp"
//		Jacqueline에서 사용하는 데이터의 형식을 정의
//												작성자 : asura
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
//		class DataType의 소멸자
//												작성자 : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

DataType::~DataType()
{
	switch (tcType) {
	case TC_ARRAY:
		delete ((ArrayType*)this)->lpdtElementType;	// 배열일 경우
		break;
	case TC_OBJECT:
		free(((ObjectType*)this)->lpszObject);		// Object Type일 경우
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// bool DataType::operator==(const DataType &dt)
//		두 데이터형이 같은가 비교
//		IN:
//			dt - 비교할 데이터형
//		RETURN:
//			자기 자신과 같은 데이터형일 때 true, 아니면 false
//												작성자 : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

bool
DataType::operator==(const DataType &dt)
{
	if (this->tcType != dt.tcType) return false;	// Type이 다를 경우
	if (this->tcType == TC_ARRAY && 
		((ArrayType*)this)->nLength != ((ArrayType*)&dt)->nLength ||
		!(((ArrayType*)this)->lpdtElementType != 
		((ArrayType*)&dt)->lpdtElementType))
		return false;								// 둘 다 배열일 경우
	return true;
};

////////////////////////////////////////////////////////////////////////////////
//
// int ArrayType::GetElementSize(void)
//		배열의 원소의 크기를 구한다
//		RETURN:
//			배열의 원소 하나의 데이터 크기
//												작성자 : asura
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
	case TC_INT:				// 원소가 정수
		return sizeof(int);
	case TC_REAL:				// 원소가 실수
		return sizeof(double);
	case TC_BOOL:				// 원소가 boolean
		return sizeof(bool);
	case TC_ARRAY:				// 원소가 배열일 경우
		temp = ((ArrayType*)lpdtElementType)->GetElementSize();
		return temp*((ArrayType*)lpdtElementType)->nLength;
	case TC_OBJECT:
		return 4;
	}

	return -1;					// Warning을 없애기 위한 코드
}

////////////////////////////////////////////////////////////////////////////////
//
// ArrayType *ArrayType::CopyType(void)
//		배열 타입을 복사하여 똑같은 타입을 만든다
//		RETURN:
//			복사된 타입
//												작성자 : asura
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
//		ObjectType 클래스의 생성자
//		IN:
//			lpszType - Object의 이름
//												작성자 : asura
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
