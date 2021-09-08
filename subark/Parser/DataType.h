////////////////////////////////////////////////////////////////////////////////
//
// "DataType.h"
//		Jacqueline에서 사용하는 데이터의 형식을 정의
//												작성자 : asura
//												Last Update : 2000. 8. 20.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _DATATYPE_H_ASURA_BECD_
#define _DATATYPE_H_ASURA_BECD_

/// Includes ///////////////////////////////////////////////////////////////////

/// Public macros & Constants //////////////////////////////////////////////////

#ifndef NULL
#define NULL (0)
#endif

/// Class or functions /////////////////////////////////////////////////////////

typedef enum { 
	TC_VOID, TC_INT, TC_REAL, TC_BOOL, TC_ARRAY, TC_OBJECT 
} TypeCode;
	// Type = VOID | INT | REAL | BOOL | ARRAY of Type | OBJECT

////////////////////////////////////////////////////////////////////////////////
//
// class DataType
//		Jacqueline에서 사용되는 데이터 형식을 나타내는 클래스. ArrayType과 
//		ObjectType의 부모 클래스로 대부분의 경우에 데이터 형식은 DataType *의 형
//		식으로 사용되며, 소멸자에서 스스로ArrayType인지 ObjectType인지 판단하여 
//		멤버 변수도 delete 해 준다.
//												작성자 : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

class DataType {
	public:
		~DataType();								// 소멸자

		TypeCode tcType;							// 데이터 타입 종류
		bool operator==(const DataType &dt);		// == operator
};

////////////////////////////////////////////////////////////////////////////////
//
// class ArrayType
//		ARRAY of Type을 나타내는 클래스
//												작성자 : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

class ArrayType : public DataType {
	public:
		int GetElementSize(void);					// 원소 하나의 크기를 계산
		ArrayType *CopyType(void);

		int nLength;								// 배열의 크기
		DataType *lpdtElementType;					// 원소의 데이터형
};

////////////////////////////////////////////////////////////////////////////////
//
// class ObjectType
//		데이터 중 Part형을 나타내는 클래스
//												작성자 : asura
//												Last Update : 2000. 7. 18.
//
////////////////////////////////////////////////////////////////////////////////

class ObjectType : public DataType {
	public:
		ObjectType(char *lpszType = NULL);			// 생성자
	
		char *lpszObject;							// Part ID
};

#endif // _DATATYPE_H_ASURA_BECD_
